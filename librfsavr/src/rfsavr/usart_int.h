/*
usart_int.h - Define USART interrupts.

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

#ifndef RFSAVR_USART_INT_H
#define RFSAVR_USART_INT_H

#include <avr/interrupt.h>

#include "rfsavr/usart_common.h"

// Extern variables
extern volatile uint8_t usart_tx_c;
extern volatile uint8_t usart_rx_c;
extern volatile char usart_rx_buffer[];
extern volatile char usart_tx_buffer[];

// Next byte to write to the RX buffer
static uint8_t usart_rx_w = 0;

// Next byte to read from the TX buffer
static uint8_t usart_tx_r = 0;

ISR(USART_RX_vect)
{
    // Write the received byte in the next position into the RX buffer
    usart_rx_buffer[usart_rx_w] = UDR0;
    // Rotate the RX write index
    usart_rx_w = (usart_rx_w + 1) & USART_RX_MASK;
    // Increment the counter of bytes in the RX buffer
    usart_rx_c++;
}

ISR(USART_UDRE_vect)
{
    // Get the next byte to be transmitted from the TX buffer
    UDR0 = usart_tx_buffer[usart_tx_r];
    // Rotate the TX read index
    usart_tx_r = (usart_tx_r + 1) & USART_TX_MASK;
    // Decrement the counter of bytes in the TX buffer
    // If the transmission buffer is empty, disable the transmission interrupts
    if (!(--usart_tx_c)) {
        UCSR0B &= ~(_BV(UDRIE0));
    }
}

#endif

