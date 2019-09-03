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
#define RFS_USART_B2400             2400
#define RFS_USART_B4800             4800
#define RFS_USART_B9600             9600
#define RFS_USART_B14400            14400
#define RFS_USART_B19200            19200
#define RFS_USART_B28800            28800
#define RFS_USART_B38400            38400
#define RFS_USART_B57600            57600
#define RFS_USART_B76800            76800
#define RFS_USART_B115200           115200
#define RFS_USART_B230400           230400
#define RFS_USART_B250000           250000
#define RFS_USART_B500000           500000
#define RFS_USART_B1000000          1000000

// Flags

// Activate multiprocessor mode
#define RFS_USART_MULTIPROCESSOR    0x00000001

// Configure USART in interrupt mode
#define RFS_USART_INT               0x0000a000

// Activate data reception
#define RFS_USART_RX                0x00001000

// Activate data transmission
#define RFS_USART_TX                0x00000800

// Activate reception and transmission
#define RFS_USART_RXTX              (RFS_USART_RX | RFS_USART_TX)

// Character size
#define RFS_USART_5BITS             0x00000000
#define RFS_USART_6BITS             0x00020000
#define RFS_USART_7BITS             0x00040000
#define RFS_USART_8BITS             0x00060000
#define RFS_USART_9BITS             0x00060400

// Parity mode
#define RFS_USART_PARITY_ODD        0x00200000
#define RFS_USART_PARITY_EVEN       0x00300000

// 2 Stop bits
#define RFS_USART_2STOPBITS         0x00080000

// Select LSB first for SPI mode
#define RFS_USART_LSBFIRST          0x00040000

// Sampling of data in SPI mode
#define RFS_USART_TRAILINGSAMPLE    0x00020000

// Edge sampling of data
#define RFS_USART_SAMPLERISING      0x00010000

// Use USART in non-blocking mode
#define RFS_USART_NOBLOCK           0x01000000


// Modes

#define RFS_USART_MODE_ASYNC        0x00
#define RFS_USART_MODE_SYNCMASTER   0x01
#define RFS_USART_MODE_SYNCSLAVE    0x02
#define RFS_USART_MODE_SPIMASTER    0xc0


// Status flags

#define RFS_USART_STATUS_FRAMEERROR     0x1000
#define RFS_USART_STATUS_DATAOVERRUN    0x0800
#define RFS_USART_STATUS_PARITYERROR    0x0400
#define RFS_USART_STATUS_9BIT           0x0002


// Declaration of status flags
extern int8_t usart_statush;
extern int8_t usart_statusl;


/* Initialize the usart.
     * mode: USART mode (async, sync master, sync slave or SPI).
     * flags: initialization options.
*/
void
rfs_usart_init (int8_t mode, int32_t flags);

/* Set the baudrate speed.
    * baudrate: USART baudrate constant.
*/
void
rfs_usart_setspeed (uint32_t baudrate);

/* Read some bytes from the RX buffer.
     * buf: where to put the read bytes.
     * count: number of bytes to read.
   In blocking mode, return count. In non-blocking mode, return the number of
   bytes read.
*/
uint8_t
rfs_usart_read (char *buf, uint8_t count);

/* Write some bytes to the TX buffer.
     * buf: buffer that contains the bytes to write.
     * count: number of bytes to write.
   In blocking mode, return count. In non-blocking mode, return the number of
   bytes written.
*/
uint8_t
rfs_usart_write (const char *buf, uint8_t count);

// Get the last status flags
#define rfs_usart_status     (((int16_t)usart_statush << 8) | usart_statusl)

// Stop the usart.
void
rfs_usart_close ();

#endif

