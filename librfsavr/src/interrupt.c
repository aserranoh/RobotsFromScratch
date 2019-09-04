/*
interrupt.c - Routines to manage interrupts and ISRs.

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

#include <avr/interrupt.h>

#include "rfsavr/interrupt.h"

#define INT_SOURCES (RFS_INT_USARTIDLE + 1)
#define INT_MAX     2

// Information of an interrupt routine
struct int_info {

    // Routine
    rfs_int_t isr;

    // Instance of parameter
    void *param;

    // Priority
    int8_t prio;

};

// Table or routines by source
static struct int_info int_tab[INT_SOURCES][INT_MAX];

// List with the number of registered routines by source
static uint8_t int_size[] = {0, 0, 0};

// USART interrupts

#define RFS_INT_ISR(src) \
    for (int i = 0; i < int_size[src]; i++) { \
        int_tab[src][i].isr (int_tab[src][i].param); \
    }

ISR(USART_RX_vect)
{
    RFS_INT_ISR (RFS_INT_USARTRX)
}

ISR(USART_UDRE_vect)
{
    RFS_INT_ISR (RFS_INT_USARTIDLE)
}

// Public functions

int8_t
rfs_int_register (
    enum rfs_int_src src, rfs_int_t isr, void *param, int8_t prio)
{
    int i;

    if (int_size[src] == INT_MAX) {
        // No more routines can be registered for the given inerrupt
        return 1;
    } else {
        // Keep the list ordered by priority
        for (i = int_size[src]; i > 0
            && prio < int_tab[src][i - 1].prio; i--)
        {
            int_tab[src][i] = int_tab[src][i - 1];
        }
        int_tab[src][i].isr = isr;
        int_tab[src][i].param = param;
        int_tab[src][i].prio = prio;
        int_size[src]++;
    }
    return 0;
}

