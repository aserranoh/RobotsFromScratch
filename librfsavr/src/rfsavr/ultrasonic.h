/*
ultrasonic.h - Manages ultrasonic sensors.

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

#ifndef RFSAVR_ULTRASONIC_H
#define RFSAVR_ULTRASONIC_H

#include "pin.h"

// Flags

#define RFS_ULTRASONIC_NOBLOCK  1

// Struct that contain the information to manage the ultrasonic sensor
typedef struct {

    // The trigger pin
    rfs_pin_t trigger_pin;

} rfs_ultrasonic_t;

// Type that describes the callback to be executed in non-blocking mode when
// the echo is received
typedef void (*rfs_ultrasonic_callback_t)(void);

/* Initialize the ultrasonic module.
     * descriptor: ultrasonic descriptor.
     * trigger_pin: the i/o pin connected to the trigger signal. Must be
        configured in advance.
     * prescaler: The timer1 prescaler value to use.
     * flags: Ultrasonic configuration options.
     * callback: When in non blocking mode, the callback that will be executed
        when the echo is received.
*/
void
rfs_ultrasonic_init (rfs_ultrasonic_t *descriptor,
                     rfs_pin_t *trigger_pin,
                     int8_t prescaler,
                     int8_t flags,
                     rfs_ultrasonic_callback_t callback);

/* Trigger the ultrasonic sensor.
   In blocking mode, this function blocks until the echo has been received and
   then returns the measured distance. In non blocking mode, this function
   returns immediately with the result 0. The callback function will be
   invoked to signal the user that the echo has been received. Then the user
   will have to use the rfs_ultrasonic_get function to retrieve the mesaured
   distance.
     * descriptor: ultrasonic descriptor.
*/
uint16_t
rfs_ultrasonic_trigger (rfs_ultrasonic_t *descriptor);

/* Return the measured distance.
     * descriptor: ultrasonic descriptor.
*/
uint16_t
rfs_ultrasonic_get (rfs_ultrasonic_t *descriptor);

#endif

