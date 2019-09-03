/*
pin.c - Operations with i/o ports and pins.

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

#include "rfsavr/pin.h"

void
rfs_pin_initb (rfs_pin_t *pin, uint8_t num)
{
    pin->port_ptr = &PORTB;
    pin->ddr_ptr = &DDRB;
    pin->n = num;
}

void
rfs_pin_initc (rfs_pin_t *pin, uint8_t num)
{
    pin->port_ptr = &PORTC;
    pin->ddr_ptr = &DDRC;
    pin->n = num;
}

void
rfs_pin_initd (rfs_pin_t *pin, uint8_t num)
{
    pin->port_ptr = &PORTD;
    pin->ddr_ptr = &DDRD;
    pin->n = num;
}

