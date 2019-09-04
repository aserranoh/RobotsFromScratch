/*
pin.h - Operations with i/o ports and pins.

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

#ifndef RFSAVR_PIN_H
#define RFSAVR_PIN_H

#include <avr/io.h>
#include <stdint.h>

// Structure with pin information
typedef struct {

    // Pointer to the PORTX register
    volatile uint8_t *port_ptr;

    // Pointer to the DDRX register
    volatile uint8_t *ddr_ptr;

    // Pin number (must be from 0 to 7)
    uint8_t n;

} rfs_pin_t;

// Macros to initialise a pin_t instance

// Initialise a pin in the different ports
void
rfs_pin_initb (rfs_pin_t *pin, uint8_t num);
void
rfs_pin_initc (rfs_pin_t *pin, uint8_t num);
void
rfs_pin_initd (rfs_pin_t *pin, uint8_t num);

// Macros to change the direction or the value of a pin

/* Configure a pin as input.
     * pin: the descriptor of the pin.
*/
#define rfs_pin_input(pin)  *((pin).ddr_ptr) &= ~_BV ((pin).n)

/* Configure a pin as output.
     * pin: the descriptor of the pin.
*/
#define rfs_pin_output(pin)	*((pin).ddr_ptr) |= _BV ((pin).n)

/* Set a pin to 1.
     * pin: the descriptor of the pin.
*/
#define rfs_pin_set(pin)	*((pin).port_ptr) |= _BV ((pin).n)

/* Set a pin to 0.
     * pin: the descriptor of the pin.
*/
#define rfs_pin_reset(pin)	*((pin).port_ptr) &= ~_BV ((pin).n)

#endif

