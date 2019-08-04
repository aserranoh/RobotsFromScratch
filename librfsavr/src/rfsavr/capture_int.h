/*
capture_int.h - Define Input Capture Unit interrupts.

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

#ifndef RFSAVR_CAPTURE_INT_H
#define RFSAVR_CAPTURE_INT_H

#include <avr/interrupt.h>

// Extern variables
extern volatile int32_t capture_value;

ISR(TIMER1_CAPT_vect)
{
    capture_value = ICR1;
}

#endif

