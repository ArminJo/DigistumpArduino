/*
 * AVRUtils.h
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
#ifndef AVRUTILS_H_
#define AVRUTILS_H_

#include <stdint.h>
#if defined(__AVR__)
#include <avr/sleep.h>
#include <avr/wdt.h>

void initSleep(uint8_t tSleepMode);
void sleepWithWatchdog(uint8_t aWatchdogPrescaler, bool aAdjustMillis = false);
extern volatile uint16_t sNumberOfSleeps;
#endif

#include <Print.h>

#define HEAP_STACK_UNTOUCHED_VALUE 0x5A
void initStackFreeMeasurement();
uint16_t getStackFreeMinimumBytes();
void printStackFreeMinimumBytes(Print * aSerial);
uint8_t * getHeapStart();
uint16_t getFreeHeap(void);
void printFreeHeap(Print * aSerial);
uint16_t getFreeRam(void);
void printFreeRam(Print * aSerial);
bool isAddressInRAM(void * aAddressToCheck);
bool isAddressBelowHeap(void * aAddressToCheck);
#endif // AVRUTILS_H_

#pragma once
