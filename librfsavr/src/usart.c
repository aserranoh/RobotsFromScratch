/*
usart.h - Interface with the USART module of the AVR processors.

This file is part of RobotsFromScratch.

Copyright 2019 Antonio Serrano Hernandez

RobotsFromScratch is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RobotsFromScratch is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RobotsFromScratch; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.
*/

#include <avr/io.h>
#include <util/atomic.h>

#include "rfsavr/usart.h"
#include "rfsavr/usart_common.h"

#define USART_NORMAL_SPEED_DIVISOR  16
#define USART_DOUBLE_SPEED_DIVISOR  8

// Usart flags
static int usart_flags;

// Next byte to read from the RX buffer
static uint8_t usart_rx_r = 0;

// Next byte to write to the TX buffer
static uint8_t usart_tx_w = 0;

// Circular RX and TX buffers
// To implement the circular buffers, they must have 2 power lenght
volatile char usart_rx_buffer[USART_RX_BUFFER_SIZE];
volatile char usart_tx_buffer[USART_TX_BUFFER_SIZE];

// Number of bytes in the TX and RX buffer
volatile uint8_t usart_tx_c = 0;
volatile uint8_t usart_rx_c = 0;

/* Compute the UBRR register value given a baudrate, a frequency and the
   divisor (16 for normal and 8 for double speed).
   * baudrate: the desired baudrate.
   * frequency: the CPU frequency.
   * divisor: speed factor (16 for normal and 8 for double speed).
   * err: output parameter that gives the difference between the desired
          baudrate and the real one.
*/
static uint16_t
rfsavr_usart_getubrr (uint32_t baudrate,
                      uint32_t frequency,
                      uint8_t divisor,
                      uint32_t *err)
{
    uint16_t ubrr = 0;
    uint32_t acc = 0;
    uint32_t i = baudrate * divisor;
    
    while (1) {
        acc += i;
        ubrr += 1;
        if (acc > frequency) {
            if (acc - frequency < (i >> 1)) {
                ubrr -= 1;
                *err = acc - frequency;
            } else {
                ubrr -= 2;
                *err = frequency - (acc - i);
            }
            break;
        }
    }
    if (ubrr < 0) {
        ubrr = 0;
    }
    return ubrr;
}

/* Read bytes using interrupts. It reads them from an intermediate buffer.
   * buf: where to put the read bytes.
   * count: number of bytes to read.
   In blocking mode, return count. In non-blocking mode, return the number of
   read bytes.
*/
static uint8_t
rfsavr_usart_read_int (char *buf, uint8_t count)
{
    uint8_t read = 0;

    while (read < count) {
        if (!usart_rx_c) {
            // No bytes to read
            if (usart_flags & RFSAVR_USART_NOBLOCK) {
                // In non-blocking mode, exit the function
                break;
            } else {
                // In blocking mode, block until there are bytes to read
                while (!usart_rx_c);
            }
        }
        // Copy the next byte in the RX buffer to the return buffer
        buf[read++] = usart_rx_buffer[usart_rx_r];
        // Rotate the RX read index and decrement the RX bytes counter
        usart_rx_r = (usart_rx_r + 1) & USART_RX_MASK;
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            usart_rx_c--;
        }
    }
    return read;
}

/* Write bytes using interrupts. It writes them to an intermediate buffer.
   * buf: contains the bytes to transmit.
   * count: number of bytes to write.
   In blocking mode, return count. In non-blocking mode, return the number of
   written bytes.
*/
static uint8_t
rfsavr_usart_write_int (const char *buf, uint8_t count)
{
    uint8_t written = 0;

    while (written < count) {
        if (usart_tx_c == USART_TX_BUFFER_SIZE) {
            // No space to write more bytes
            if (usart_flags & RFSAVR_USART_NOBLOCK) {
                // In non-blocking mode, exit the function
                break;
            } else {
                // In blocking mode, block until there are bytes to read
                while (usart_tx_c == USART_TX_BUFFER_SIZE);
            }
        }
        // Copy the next byte from the input buffer to the TX buffer
        usart_tx_buffer[usart_tx_w] = buf[written++];
        // Rotate the TX write index and increment the TX bytes counter
        usart_tx_w = (usart_tx_w + 1) & USART_TX_MASK;
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            usart_tx_c++;
        }
        // Activate the TX interrupts (now there's some bytes to transmit)
        UCSR0B |= _BV(UDRIE0);
    }
    return written;
}

/* Read bytes without using interrupts.
   * buf: where to put the read bytes.
   * count: number of bytes to read.
   In blocking mode, return count. In non-blocking mode, return the number of
   read bytes.
*/
static uint8_t
rfsavr_usart_read_noint (char *buf, uint8_t count)
{
    uint8_t read = 0;

    while (read < count) {
        if (!(UCSR0A & _BV(RXC0))) {
            if (usart_flags & RFSAVR_USART_NOBLOCK) {
                // In non-blocking mode, exit the function
                break;
            } else {
                // Wait for data to be received
                while (!(UCSR0A & _BV(RXC0)));
            }
        }
        // Get and return received data from buffer
        buf[read++] = UDR0;
    }
    return read;
}

/* Write bytes without using interrupts.
   * buf: contains the bytes to transmit.
   * count: number of bytes to write.
   In blocking mode, return count. In non-blocking mode, return the number of
   written bytes.
*/
static uint8_t
rfsavr_usart_write_noint (const char *buf, uint8_t count)
{
    uint8_t written = 0;

    while (written < count) {
        if (!(UCSR0A & _BV(UDRE0))) {
            if (usart_flags & RFSAVR_USART_NOBLOCK) {
                // In non-blocking mode, exit the function
                break;
            } else {
                // Wait for empty transmit buffer
                while (!(UCSR0A & _BV(UDRE0)));
            }
        }
        // Put data into buffer, sends the data
        UDR0 = buf[written++];
    }
    return written;
}

void
rfsavr_usart_init (uint32_t baudrate, int8_t flags, uint32_t frequency)
{
    // Save the flags
    usart_flags = flags;

    // Compute the UBRR register value and the speed factor
    uint32_t err_normal, err_double;
    uint16_t ubrr_normal, ubrr_double;

    ubrr_normal = rfsavr_usart_getubrr (
        baudrate, frequency, USART_NORMAL_SPEED_DIVISOR, &err_normal);
    ubrr_double = rfsavr_usart_getubrr (
        baudrate, frequency, USART_DOUBLE_SPEED_DIVISOR, &err_double);
    if (err_normal <= err_double) {
        UBRR0 = ubrr_normal;
        UCSR0A &= ~_BV(U2X0);
    } else {
        UBRR0 = ubrr_double;
        UCSR0A |= _BV(U2X0);
    }

    // Set configuration registers
    // Configure reception
    if (flags & RFSAVR_USART_RX) {
        UCSR0B |= _BV(RXEN0);
        if (flags & RFSAVR_USART_INT) {
            UCSR0B |= _BV(RXCIE0);
        } else {
            UCSR0B &= ~_BV(RXCIE0);
        }
    } else {
        UCSR0B &= ~_BV(RXEN0);
    }
    // Configure transmission
    if (flags & RFSAVR_USART_TX) {
        UCSR0B |= _BV(TXEN0);
        UCSR0B &= ~_BV(UDRIE0);
    } else {
        UCSR0B &= ~_BV(TXEN0);
    }
    // Configure 8 data bits
    UCSR0B &= ~_BV(UCSZ02);
    UCSR0C |= (_BV(UCSZ01) | _BV(UCSZ00));
}

uint8_t
rfsavr_usart_read (char *buf, uint8_t count)
{
    if (usart_flags & RFSAVR_USART_INT) {
        return rfsavr_usart_read_int (buf, count);
    } else {
        return rfsavr_usart_read_noint (buf, count);
    }
}

uint8_t
rfsavr_usart_write (const char *buf, uint8_t count)
{
    if (usart_flags & RFSAVR_USART_INT) {
        return rfsavr_usart_write_int (buf, count);
    } else {
        return rfsavr_usart_write_noint (buf, count);
    }
}

// Stop the usart.
void
rfsavr_usart_close()
{
    UCSR0B = 0;
}

