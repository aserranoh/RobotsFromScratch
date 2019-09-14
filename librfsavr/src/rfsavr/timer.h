/*
timer.h - Timer subsystems.

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

#ifndef RFSAVR_TIMER_H
#define RFSAVR_TIMER_H

// Timer1 source constants
#define RFS_TIMER1_PRESCALER64  3

// Timer1 macros
#define rfs_timer1_counter      TCNT1

// Timer1 possible mode of operation
enum rfs_timer1_mode {
    RFS_TIMER1_MODE_NORMAL,             // Normal mode
    RFS_TIMER1_MODE_PWM8,               // PWM phase correct, 8 bits
    RFS_TIMER1_MODE_PWM9,               // PWM phase correct, 9 bits
    RFS_TIMER1_MODE_PWM10,              // PWM phase correct, 10 bits
    RFS_TIMER1_MODE_CTCOCR,             // Clear on compare, top = OCR1A
    RFS_TIMER1_MODE_FASTPWM8,           // Fast PWM, 8 bits
    RFS_TIMER1_MODE_FASTPWM9,           // Fast PWM, 9 bits
    RFS_TIMER1_MODE_FASTPWM10,          // Fast PWM, 10 bits
    RFS_TIMER1_MODE_PWMFREQCORRECTICR,  // PWM phase and frequency correct,
                                        // top = ICR1
    RFS_TIMER1_MODE_PWMFREQCORRECTOCR,  // PWM phase and frequency correct,
                                        // top = OCR1A
    RFS_TIMER1_MODE_PWMICR,             // PWM phase correct, top = ICR1
    RFS_TIMER1_MODE_PWMOCR,             // PWM phase correct, top = OCR1A
    RFS_TIMER1_MODE_CTCICR,             // Clear on compare, top = ICR1
    RFS_TIMER1_MODE_FASTPWMICR = 0xe,   // Fast PWM, top = ICR1
    RFS_TIMER1_MODE_FASTPWMOCR          // Fast PWM, top = OCR1A
};

// Timer1 possible clock sources
enum rfs_timer1_clocksrc {
    RFS_TIMER1_CLOCK_NONE,              // No clock source, timer1 stopped
    RFS_TIMER1_CLOCK_NOPRESCALER,       // No prescaling, src = clkio
    RFS_TIMER1_CLOCK_PRESCALER8,        // src = clkio/8
    RFS_TIMER1_CLOCK_PRESCALER64,       // src = clkio/64
    RFS_TIMER1_CLOCK_PRESCALER256,      // src = clkio/256
    RFS_TIMER1_CLOCK_PRESCALER1024,     // src = clkio/1024
    RFS_TIMER1_CLOCK_EXTFALLING,        // src = T1 pin, falling edge
    RFS_TIMER1_CLOCK_EXTRAISING         // src = T1 pin, raising edge
};

/* Initialize timer1.
    * mode: timer1 mode of operation.
*/
void
rfs_timer1_init (enum rfs_timer1_mode mode);

/* Set the clock source.
    * src: clock source.
*/
void
rfs_timer1_setclocksrc (enum rfs_timer1_clocksrc src);

#endif

