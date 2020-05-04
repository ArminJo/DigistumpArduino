/*
 * MillisUtils.h
 *
 *  Copyright (C) 2016-2020  Armin Joachimsmeyer
 *  Email: armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-Utils https://github.com/ArminJo/Arduino-Utils.
 *
 *  Arduino-Utils is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#ifndef MILLIS_UTILS_H_
#define MILLIS_UTILS_H_

#include <stdint.h>

//void speedTestWith1kCalls(void (*aFunctionUnderTest)(void));

/*
 * storage for millis value to enable compensation for interrupt disable at signal acquisition etc.
 */
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)  || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#define timer0_millis millis_timer_millis // The ATTinyCore + Digispark libraries use this variable name in wiring.c
#endif
#if defined(TIMSK0) && !defined(TIMSK) // some ATtinys
#define TIMSK TIMSK0
#endif

#if defined(ARDUINO_AVR_DIGISPARK)
    // Digispark uses timer1 for millis()
#define TOIE TOIE1
#else
#define TOIE TOIE0
#endif

extern volatile unsigned long timer0_millis;

void disableMillisInterrupt();
void addToMillis(uint16_t aMillisToAdd);
void enableMillisInterrupt(uint16_t aMillisToAddForCompensation = 0);
void delayMilliseconds(unsigned int aMillis);
bool areMillisGone(unsigned int aMillis);
bool areMillisGone(unsigned int aMillis, unsigned long * aLastMillisPtr);

#endif // MILLIS_UTILS_H_

#pragma once
