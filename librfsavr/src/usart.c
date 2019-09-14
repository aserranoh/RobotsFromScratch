/*
usart.c - Interface with the USART module of the AVR processors.

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

#include "rfsavr/core.h"
#include "rfsavr/interrupts.h"
#include "rfsavr/usart.h"

#define USART_NORMAL_SPEED_DIVISOR  16
#define USART_DOUBLE_SPEED_DIVISOR  8

#define USART_REGA_MASK             0x01
#define USART_REGB_MASK             0xfc
#define USART_REGC_MASK             0x3f

#define USART_RX_BUFFER_SIZE        32
#define USART_TX_BUFFER_SIZE        32
#define USART_RX_MASK               (USART_RX_BUFFER_SIZE - 1)
#define USART_TX_MASK               (USART_TX_BUFFER_SIZE - 1)

// Some usart flags
static int8_t usart_int;
static int8_t usart_noblock;

// Status flags when reading
int8_t usart_statush = 0;
int8_t usart_statusl = 0;

// Circular RX and TX buffers
// To implement the circular buffers, they must have 2 power lenght
static volatile char usart_rx_buffer[USART_RX_BUFFER_SIZE];
static volatile char usart_tx_buffer[USART_TX_BUFFER_SIZE];

// Next byte to read from the RX buffer
static uint8_t usart_rx_r = 0;

// Next byte to write to the TX buffer
static uint8_t usart_tx_w = 0;

// Next byte to write to the RX buffer
static uint8_t usart_rx_w = 0;

// Next byte to read from the TX buffer
static uint8_t usart_tx_r = 0;

// Number of bytes in the TX and RX buffer
static volatile uint8_t usart_tx_c = 0;
static volatile uint8_t usart_rx_c = 0;

/* RX Interrupt Service Routine */
static void
rfs_usart_rx ()
{
    // Write the received byte in the next position into the RX buffer
    usart_statush = UCSR0A;
    usart_statusl = UCSR0B;
    usart_rx_buffer[usart_rx_w] = UDR0;
    // Rotate the RX write index
    usart_rx_w = (usart_rx_w + 1) & USART_RX_MASK;
    // Increment the counter of bytes in the RX buffer
    usart_rx_c++;
}

/* TX Interrupt Service Routine */
static void
rfs_usart_tx ()
{
    // Get the next byte to be transmitted from the TX buffer
    UDR0 = usart_tx_buffer[usart_tx_r];
    // Rotate the TX read index
    usart_tx_r = (usart_tx_r + 1) & USART_TX_MASK;
    // Decrement the counter of bytes in the TX buffer
    // If the transmission buffer is empty, disable the transmission interrupts
    if (!(--usart_tx_c)) {
        UCSR0B &= ~(_BV(UDRIE0));
    }
}

/* Compute the UBRR register value given a baudrate, a frequency and the
   divisor (16 for normal and 8 for double speed).
   * baudrate: the desired baudrate.
   * divisor: speed factor (16 for normal and 8 for double speed).
   * err: output parameter that gives the difference between the desired
          baudrate and the real one.
*/
static uint16_t
rfs_usart_getubrr (uint32_t baudrate, uint8_t divisor, uint32_t *err)
{
    uint16_t ubrr = 0;
    uint32_t acc = 0;
    uint32_t i = baudrate * divisor;
    uint32_t frequency = rfs_core_cpufreq;
    
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
rfs_usart_read_int (char *buf, uint8_t count)
{
    uint8_t read = 0;

    while (read < count) {
        if (!usart_rx_c) {
            // No bytes to read
            if (usart_noblock) {
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
rfs_usart_write_int (const char *buf, uint8_t count)
{
    uint8_t written = 0;

    while (written < count) {
        if (usart_tx_c == USART_TX_BUFFER_SIZE) {
            // No space to write more bytes
            if (usart_noblock) {
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
rfs_usart_read_noint (char *buf, uint8_t count)
{
    uint8_t read = 0;

    while (read < count) {
        if (!(UCSR0A & _BV(RXC0))) {
            if (usart_noblock) {
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
rfs_usart_write_noint (const char *buf, uint8_t count)
{
    uint8_t written = 0;

    while (written < count) {
        if (!(UCSR0A & _BV(UDRE0))) {
            if (usart_noblock) {
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
rfs_usart_init (int8_t mode, int32_t flags)
{
    // Save some of the flags
    usart_int = (flags & RFS_USART_INT) ? 1 : 0;
    usart_noblock = (flags & RFS_USART_NOBLOCK) ? 1 : 0;

    // Set USART mode
    if (mode & (RFS_USART_MODE_SYNCMASTER | RFS_USART_MODE_SYNCSLAVE)) {
        if (mode & RFS_USART_MODE_SYNCMASTER) {
            DDRD |= _BV (DDD4);
        } else {
            DDRD &= ~_BV (DDD4);
        }
        UCSR0C = (UCSR0C & 0x3f) | _BV (UMSEL00);
    } else {
        UCSR0C = (UCSR0C & 0x3f) | mode;
    }

    // Set configuration registers
    UCSR0A = (UCSR0A & ~USART_REGA_MASK) | (int8_t)(flags & 0xff);
    UCSR0B = (UCSR0B & ~USART_REGB_MASK) | (int8_t)((flags >> 8) & 0xff);
    UCSR0C = (UCSR0C & ~USART_REGC_MASK) | (int8_t)((flags >> 16) & 0xff);

    // Enable interrupts
    if (flags & RFS_USART_INT) {
        rfs_int_register (RFS_INT_USARTRX, rfs_usart_rx, 0);
        rfs_int_register (RFS_INT_USARTIDLE, rfs_usart_tx, 0);
    }
}

void
rfs_usart_setspeed (uint32_t baudrate)
{
    // Compute the UBRR register value and the speed factor
    uint32_t err_normal, err_double;
    uint16_t ubrr_normal, ubrr_double;

    ubrr_normal = rfs_usart_getubrr (
        baudrate, USART_NORMAL_SPEED_DIVISOR, &err_normal);
    ubrr_double = rfs_usart_getubrr (
        baudrate, USART_DOUBLE_SPEED_DIVISOR, &err_double);
    if (err_normal <= err_double) {
        UBRR0 = ubrr_normal;
        UCSR0A &= ~_BV(U2X0);
    } else {
        UBRR0 = ubrr_double;
        UCSR0A |= _BV(U2X0);
    }
}

uint8_t
rfs_usart_read (char *buf, uint8_t count)
{
    if (usart_int) {
        return rfs_usart_read_int (buf, count);
    } else {
        return rfs_usart_read_noint (buf, count);
    }
}

uint8_t
rfs_usart_write (const char *buf, uint8_t count)
{
    if (usart_int) {
        return rfs_usart_write_int (buf, count);
    } else {
        return rfs_usart_write_noint (buf, count);
    }
}

// Stop the usart.
void
rfs_usart_close()
{
    UCSR0B = 0;
}

