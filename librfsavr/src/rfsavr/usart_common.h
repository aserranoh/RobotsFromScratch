/*
usart_common.h - USART common vars in interrupt and non-interrupt space.

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

#ifndef RFSAVR_USART_COMMON_H
#define RFSAVR_USART_COMMON_H

#define USART_RX_BUFFER_SIZE        32
#define USART_TX_BUFFER_SIZE        32
#define USART_RX_MASK               (USART_RX_BUFFER_SIZE - 1)
#define USART_TX_MASK               (USART_TX_BUFFER_SIZE - 1)

#endif

