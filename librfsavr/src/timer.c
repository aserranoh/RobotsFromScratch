/*
timer.c - Timer subsystems.

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

#include "rfsavr/timer.h"

void
rfs_timer1_init (enum rfs_timer1_mode mode)
{
    TCCR1A = (TCCR1A & 0xfc) | (mode & 0x03);
    TCCR1B = (TCCR1B & 0xe7) | ((mode & 0x0c) << 1);
}

void
rfs_timer1_setclocksrc (enum rfs_timer1_clocksrc src)
{
    TCCR1B = (TCCR1B & 0xf8) | src;
}

