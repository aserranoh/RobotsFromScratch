/*
capture.h - Interface with the Input Capture Unit module of the AVR processors.

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

#ifndef RFSAVR_CAPTURE_H
#define RFSAVR_CAPTURE_H

// Flags

// Configure the clock source
#define RFSAVR_CAPTURE_CLK1     0x01
#define RFSAVR_CAPTURE_CLK8     0x02
#define RFSAVR_CAPTURE_CLK64    0x03
#define RFSAVR_CAPTURE_CLK256   0x04
#define RFSAVR_CAPTURE_CLK1024  0x05

// Configure the Input Capture Unit in interrupt mode
#define RFSAVR_CAPTURE_INT      0x08

// Use the Input Capture Unit in non-blocking mode
#define RFSAVR_CAPTURE_NOBLOCK  0x10

// Options

// Set or reset the noise canceller
#define RFSAVR_CAPTURE_NOISEC   0x1

// Capture edge
#define RFSAVR_CAPTURE_FALLING  0x0
#define RFSAVR_CAPTURE_RISING   0x2

/* Initialize the usart.
     * flags: initialization options.
*/
void
rfsavr_capture_init (int8_t flags);

/* Set Input Capture Unit options. */
void
rfsavr_capture_setopts (int8_t flags);

/* Return the timestamp of the last captured event.
   In blocking mode, blocks until the new event occurs. In non blocking mode,
   return immediately and if there has not been a new event since the last one,
   return -1.
*/
int32_t
rfsavr_capture_read ();

#endif

