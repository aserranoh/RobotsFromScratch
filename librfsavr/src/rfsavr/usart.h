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

#ifndef RFSAVR_USART_H
#define RFSAVR_USART_H

#include <stdint.h>

// Baudrate constants
#define RFSAVR_USART_B2400      2400
#define RFSAVR_USART_B4800      4800
#define RFSAVR_USART_B9600      9600
#define RFSAVR_USART_B14400     14400
#define RFSAVR_USART_B19200     19200
#define RFSAVR_USART_B28800     28800
#define RFSAVR_USART_B38400     38400
#define RFSAVR_USART_B57600     57600
#define RFSAVR_USART_B76800     76800
#define RFSAVR_USART_B115200    115200
#define RFSAVR_USART_B230400    230400
#define RFSAVR_USART_B250000    250000
#define RFSAVR_USART_B500000    500000
#define RFSAVR_USART_B1000000   1000000

// Flags

// Activate data reception
#define RFSAVR_USART_RX         0x1

// Activate data transmission
#define RFSAVR_USART_TX         0x2

// Activate reception and transmission
#define RFSAVR_USART_RXTX       (RFSAVR_USART_RX | RFSAVR_USART_TX)

// Configure USART in interrupt mode
#define RFSAVR_USART_INT        0x4

// Use USART in non-blocking mode
#define RFSAVR_USART_NOBLOCK    0x8


/* Initialize the usart.
     * baudrate: baudrate, in bits per second.
     * flags: initialization options.
     * frequency: CPU frequency.
*/
void
rfsavr_usart_init (uint32_t baudrate,
                   int8_t flags,
                   uint32_t frequency);

/* Read some bytes from the RX buffer.
     * buf: where to put the read bytes.
     * count: number of bytes to read.
   In blocking mode, return count. In non-blocking mode, return the number of
   bytes read.
*/
uint8_t
rfsavr_usart_read (char *buf, uint8_t count);

/* Write some bytes to the TX buffer.
     * buf: buffer that contains the bytes to write.
     * count: number of bytes to write.
   In blocking mode, return count. In non-blocking mode, return the number of
   bytes written.
*/
uint8_t
rfsavr_usart_write (const char *buf, uint8_t count);

// Stop the usart.
void
rfsavr_usart_close ();

#endif

