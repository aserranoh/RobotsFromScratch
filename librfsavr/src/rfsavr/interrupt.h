/*
interrupt.h - Routines to manage interrupts and ISRs.

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

#ifndef RFSAVR_INTERRUPT_H
#define RFSAVR_INTERRUPT_H

#include <stdint.h>

// Enumerate the source of interrupts
enum rfs_int_src {
    RFS_INT_T1CAPTURE,
    RFS_INT_USARTRX,
    RFS_INT_USARTIDLE
};

/* Type that represents the interrupt routine.
   It is a function that expect a single void * parameter and returns void.
*/
typedef void (*rfs_int_t) (void *param);

/* Register an interrupt routine.
   An interrupt routine has a priority. The given routine will be executed
   before the registered routine with higher priority vaue but after the
   routines with lower priority value.
   The routine can only be registered if the maximum number of routines for
   a given interrupt source has not been exceeded.

   Parameters:
     * src: source of interrupt that will trigger the interrupt routine
            (see enum rfsavr_inttype).
     * isr: routine to register.
     * param: parameter to pass to the interrupt service routine.
     * prio: routine priority.

   Return 0 if the routine can be registered, 1 otherwise.
*/
int8_t
rfs_int_register (
    enum rfs_int_src src, rfs_int_t isr, void *param, int8_t prio);

#endif

