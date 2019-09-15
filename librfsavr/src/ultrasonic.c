/*
ultrasonic.c - Manages ultrasonic sensors.

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

#include "rfsavr/interrupt.h"
#include "rfsavr/timer.h"
#include "rfsavr/ultrasonic.h"

// Define the trigger pulse in microseconds
#define ULTRASONIC_TRIGGER_PULSE_LENGTH 10

// Interrupt request that manages the edge to capture and the captured value
static void
ultrasonic_int ()
{
    // When raising edge, record the edge timestamp and change the detection
    // edge
    if (rfs_timer1_captureedge == RFS_TIMER1_RAISING) {
        ultrasonic_startecho = rfs_timer1_capture;
        rfs_timer1_setcaptureedge (RFS_TIMER1_FALLING);
        rfs_timer1_resetintflag (RFS_TIMER1_INT_CAPTURE);
    }
    // When falling edge, record the edge timestamp
    else {
        ultrasonic_endecho = rfs_timer1_capture;
    }
}

void
rfs_ultrasonic_init (rfs_ultrasonic_t *descriptor,
                     rfs_pin_t *trigger_pin,
                     int8_t prescaler,
                     int8_t flags,
                     rfs_ultrasonic_callback_t callback)
{
    // Initialise the descriptor attributes
    descriptor->trigger_pin = *trigger_pin;

    // Configure the trigger pin as output
    rfs_pin_output (*trigger_pin);

    // Initialize the Timer1 subsystem
    rfs_timer1_init (RFS_TIMER1_MODE_NORMAL);
    rfs_timer1_setclocksrc (prescaler);

    // If in non-blocking mode, register and enable timer1 input capture
    // interrupts
    if (flags & RFS_ULTRASONIC_NOBLOCK) {
        rfs_int_register (RFS_INT_T1CAPTURE, ultrasonic_int, 0);
        rfs_int_register (RFS_INT_T1CAPTURE, callback, 0);
        rfs_timer1_setintmask (RFS_TIMER1_INT_CAPTURE);
    }
} 

uint16_t
rfs_ultrasonic_trigger (rfs_ultrasonic_t *descriptor)
{
    // Configure the input capture unit to listen to a rising edge
    rfsavr_capture_setopts (RFSAVR_CAPTURE_FALLING);

    // Emit the trigering pulse
    rfsavr_pin_set (&(descriptor->pin));
    _delay_us(ULTRASONIC_TRIGGER_PULSE_LENGTH);
    rfsavr_pin_reset (&(descriptor->pin));
}

int32_t
rfsavr_ultrasonic_read (rfs_ultrasonic_t *descriptor)
{
    int32_t end_pulse_timestamp;

    // Wait for the rising edge
    if (descriptor->start_pulse_timestamp < 0) {
        descriptor->start_pulse_timestamp = rfsavr_capture_read ();
    }
    // If the first pulse is not returned yet, yield
    if (descriptor->start_pulse_timestamp < 0) {
        return -1;
    }

    // Reconfigure the input capture unit to wait for the falling edge
    rfsavr_capture_setopts (RFSAVR_CAPTURE_FALLING);

    // Wait for the falling edge
    end_pulse_timestamp = rfsavr_capture_read ();
    if (end_pulse_timestamp < 0) {
        return -1;
    }

    // Reset the pulse timestamps and return the pulse length
    return end_pulse_timestamp - descriptor->start_pulse_timestamp;
}

