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

#include <util/delay.h>

#include "rfsavr/interrupt.h"
#include "rfsavr/timer.h"
#include "rfsavr/ultrasonic.h"

// Define the trigger pulse in microseconds
#define ULTRASONIC_TRIGGER_PULSE_LENGTH 10

// Interrupt request that manages the edge to capture and the captured value
static void
ultrasonic_int (void *param)
{
    rfs_ultrasonic_t *us = (rfs_ultrasonic_t *)param;

    // When raising edge, record the edge timestamp and change the detection
    // edge
    if (rfs_timer1_captureedge == RFS_TIMER1_RAISING) {
        us->startecho = rfs_timer1_capture;
        // Change the edge to detect (falling)
        rfs_timer1_setcaptureedge (RFS_TIMER1_FALLING);
        rfs_timer1_resetintflag (RFS_TIMER1_INT_CAPTURE);
    }
    // When falling edge, compute the distance and notify the user
    else {
        if (us->callback) {
            us->callback (us, rfs_timer1_capture - us->startecho);
        }
        // Change the edge to detect (raising)
        rfs_timer1_setcaptureedge (RFS_TIMER1_RAISING);
        rfs_timer1_resetintflag (RFS_TIMER1_INT_CAPTURE);
    }
}

void
rfs_ultrasonic_init (rfs_ultrasonic_t *descriptor,
                     rfs_pin_t *trigger_pin,
                     int8_t prescaler,
                     rfs_ultrasonic_callback_t callback)
{
    // Initialise the descriptor attributes
    descriptor->trigger_pin = *trigger_pin;

    // Configure the trigger pin as output
    rfs_pin_output (*trigger_pin);

    // Configure the echo pin as input
    DDRB &= ~_BV (DDB0);

    // Initialize the Timer1 subsystem
    rfs_timer1_init (RFS_TIMER1_MODE_NORMAL);
    rfs_timer1_setclocksrc (prescaler);

    // Configure the input capture unit to listen to a rising edge
    rfs_timer1_setcaptureedge (RFS_TIMER1_RAISING);

    // If in non-blocking mode, register and enable timer1 input capture
    // interrupts
    descriptor->callback = callback;
    if (callback) {
        rfs_int_register (RFS_INT_T1CAPTURE, ultrasonic_int, descriptor, 0);
        rfs_timer1_setintmask (RFS_TIMER1_INT_CAPTURE);
    }
} 

uint16_t
rfs_ultrasonic_trigger (rfs_ultrasonic_t *descriptor)
{
    uint16_t startecho, distance;

    // Emit the trigering pulse
    rfs_pin_set (descriptor->trigger_pin);
    _delay_us(ULTRASONIC_TRIGGER_PULSE_LENGTH);
    rfs_pin_reset (descriptor->trigger_pin);

    // If in non-blocking mode, return 0 immediately
    if (descriptor->callback) {
        distance = 0;
    // If in blocking mode, wait to the echo pulse to finish completely
    } else {
        // Wait for the rising edge of the echo pulse
        while (!rfs_timer1_getintflag (RFS_TIMER1_INT_CAPTURE));
        // Record timestamp and change the edge to detect
        startecho = rfs_timer1_capture;
        rfs_timer1_setcaptureedge (RFS_TIMER1_FALLING);
        rfs_timer1_resetintflag (RFS_TIMER1_INT_CAPTURE);
        // Wait for the falling edge of the echo pulse
        while (!rfs_timer1_getintflag (RFS_TIMER1_INT_CAPTURE));
        // Return the distance value
        distance = rfs_timer1_capture - startecho;
        // Change the edge to detect (raising)
        rfs_timer1_setcaptureedge (RFS_TIMER1_RAISING);
        rfs_timer1_resetintflag (RFS_TIMER1_INT_CAPTURE);
    }
    return distance;
}

