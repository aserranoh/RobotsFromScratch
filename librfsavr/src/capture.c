/*
capture.c - Interface with the Input Capture Unit module of the AVR processors.

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

#include "rfsavr/capture.h"

#define CAPTURE_CLOCK_MASK  0x7

// Stored flags
static int8_t capture_flags;

// The captured value
volatile int32_t capture_value;

int32_t
rfsavr_capture_read_noint ()
{
    uint16_t captured_value;

    // Wait until the interrupt flag is activated
    if (!(TIFR1 & _BV (ICF1))) {
        if (capture_flags & RFSAVR_CAPTURE_NOBLOCK) {
            return -1;
        } else {
            while (!(TIFR1 & _BV (ICF1)));
        }
    }
    // Copy the capture value
    captured_value = ICR1;
    // Reset the interrupt flag
    TIFR1  |= _BV (ICF1);
    return captured_value;
}

int32_t
rfsavr_capture_read_int ()
{
    int32_t c;

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        c = capture_value;
        capture_value = -1;
    }
    return c;
}

void
rfsavr_capture_init (int8_t flags)
{
    capture_flags = flags;
    capture_value = -1;

    // Register TCCR1A
    // COM1A[1:0] | COM1B[1:0] | X | X | WGM1[1:0]
    TCCR1A = 0;

    // Register TCCR1B
    // ICNC1 | ICES1 | X | WGM1[3:2] | CS1[2:0]
    // ICNC1: Input Capture Noise Canceler (1 = activated)
    // ICES1: Input Capture Edge Select (0 = falling, 1 = raising)
    // CS1: Clock select
    // By default, clock source is NO PRESCALER
    if (!(flags & CAPTURE_CLOCK_MASK)) {
        TCCR1B = RFSAVR_CAPTURE_CLK1;
    } else {
        TCCR1B = flags & CAPTURE_CLOCK_MASK;
    }

    // Set interrupts
    if (flags & RFSAVR_CAPTURE_INT) {
        TIMSK1 |= _BV (ICIE1);
    } else {
        TIMSK1 &= ~_BV (ICIE1);
    }
}

void
rfsavr_capture_setopts (int8_t flags)
{
    // Set noise cancelling option
    if (flags & RFSAVR_CAPTURE_NOISEC) {
        TCCR1B |= _BV (ICNC1);
    } else {
        TCCR1B &= ~_BV (ICNC1);
    }

    // Set the edge to detect
    if (flags & RFSAVR_CAPTURE_RISING) {
        TCCR1B |= _BV (ICES1);
    } else {
        TCCR1B &= ~_BV (ICES1);
    }
    TIFR1 |= _BV (ICF1);
}

int32_t
rfsavr_capture_read ()
{
    if (capture_flags & RFSAVR_CAPTURE_INT) {
        return rfsavr_capture_read_int ();
    } else {
        return rfsavr_capture_read_noint ();
    }
}

