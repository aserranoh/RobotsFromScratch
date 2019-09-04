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

// Forward declarations
typedef struct rfs_ultrasonic_s rfs_ultrasonic_t;

// Type that describes the callback to be executed in non-blocking mode when
// the echo is received
typedef void
(*rfs_ultrasonic_callback_t)(rfs_ultrasonic_t *us, uint16_t distance);

// Struct that contain the information to manage the ultrasonic sensor
struct rfs_ultrasonic_s {

    // The trigger pin
    rfs_pin_t trigger_pin;

    // Timestamp of the echo pulse's rising edge
    uint16_t startecho;

    // Callback to execute in non-blocking mode to signal the end of the echo
    // pulse
    rfs_ultrasonic_callback_t callback;

};

/* Initialize the ultrasonic module.
     * descriptor: ultrasonic descriptor.
     * trigger_pin: the i/o pin connected to the trigger signal. Must be
        configured in advance.
     * prescaler: The timer1 prescaler value to use.
     * callback: When in non blocking mode, the callback that will be executed
        when the echo is received.
*/
void
rfs_ultrasonic_init (rfs_ultrasonic_t *descriptor,
                     rfs_pin_t *trigger_pin,
                     int8_t prescaler,
                     rfs_ultrasonic_callback_t callback);

/* Trigger the ultrasonic sensor.
   If the parameter callback is given, the ultrasonic module is configured in
   non-blocking mode.
   In blocking mode, this function blocks until the echo has been received and
   then returns the measured distance. In non blocking mode, this function
   returns immediately with the result 0. The callback function will be
   invoked to signal the user that the echo has been received. Then the user
   will have to use the rfs_ultrasonic_get function to retrieve the mesaured
   distance.
     * descriptor: ultrasonic descriptor.
     * trigger_pin: the pin connected to the trigger signal.
     * prescaler: prescaler value to set the Timer1 speed.
     * callback: callback to execute in non-blocking mode.
*/
uint16_t
rfs_ultrasonic_trigger (rfs_ultrasonic_t *descriptor);

/* Return the measured distance.
     * descriptor: ultrasonic descriptor.
*/
uint16_t
rfs_ultrasonic_get (rfs_ultrasonic_t *descriptor);

#endif

