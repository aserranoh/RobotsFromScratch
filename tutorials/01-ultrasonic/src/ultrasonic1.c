/*
ultrasonic1.c - First tutorial with ultrasonic sensors.

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

#include <avr/interrupt.h>  // sei
#include <stdio.h>          // sprintf
#include <string.h>         // strlen

#include "rfsavr/core.h"
#include "rfsavr/pin.h"
#include "rfsavr/timer.h"
#include "rfsavr/ultrasonic.h"
#include "rfsavr/usart.h"

#define PERIOD  12500

int main () {

    rfs_ultrasonic_t us;
    rfs_pin_t trigger_pin;
    uint16_t last_timestamp, current_timestamp;
    int16_t distance;
    char s[8];

    // Global rfs library initialization
    rfs_core_setcpufreq (F_CPU);

    // Create the ultrasonic sensor
    rfs_pin_initb (&trigger_pin, 1);
    rfs_ultrasonic_init (&us, &trigger_pin, RFS_TIMER1_PRESCALER64, 0);

    // Initialize the USART
    rfs_usart_init (RFS_USART_MODE_ASYNC,
        RFS_USART_TX | RFS_USART_8BITS | RFS_USART_INT);
    rfs_usart_setspeed (RFS_USART_B19200);

    // Activate global interrupts
    sei ();

    // Get the first trigger timestamp
    last_timestamp = rfs_timer1_counter;

    // Main loop
    while (1) {
        // Trigger the ultrasonic sensor
        distance = rfs_ultrasonic_trigger (&us);

        // Put the distance in a string
        sprintf (s, "%u\n", distance);

        // Send the string through the serial port
        rfs_usart_write (s, strlen (s));

        // Wait until 50ms have elapsed
        current_timestamp = rfs_timer1_counter;
        while (current_timestamp - last_timestamp < PERIOD) {
            current_timestamp = rfs_timer1_counter;
        }

        // Update the timestamp
        last_timestamp = current_timestamp;
    }
}

