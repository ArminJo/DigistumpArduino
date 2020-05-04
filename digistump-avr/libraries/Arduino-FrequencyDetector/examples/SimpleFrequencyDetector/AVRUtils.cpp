/*
 *  AVRUtils.cpp
 *
 *  Stack, Ram and Heap utilities.
 *  Sleep utilities.
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

#if defined(__AVR__)
#include "AVRUtils.h"
#include <avr/interrupt.h>
#include <stdlib.h> // for __malloc_margin

/*
 * initialize RAM between actual stack and actual heap start (__brkval) with pattern 0x5A
 */
void initStackFreeMeasurement() {
    extern unsigned int __heap_start;
    extern void * __brkval;
    uint8_t tDummyVariableOnStack;

    uint8_t * tHeapPtr = (uint8_t *) __brkval;
    if (tHeapPtr == 0) {
        tHeapPtr = (uint8_t *) &__heap_start;
    }

// Fill memory
    do {
        *tHeapPtr++ = HEAP_STACK_UNTOUCHED_VALUE;
    } while (tHeapPtr < &tDummyVariableOnStack);
}

/*
 * Check for untouched patterns
 */
uint16_t getStackFreeMinimumBytes() {
    extern unsigned int __heap_start;
    extern void * __brkval;
    uint8_t tDummyVariableOnStack;

    uint8_t * tHeapPtr = (uint8_t *) __brkval;
    if (tHeapPtr == 0) {
        tHeapPtr = (uint8_t *) &__heap_start;
    }

// first search for first match, because malloc() and free() may be happened in between and overwrite low memory
    while (*tHeapPtr != HEAP_STACK_UNTOUCHED_VALUE && tHeapPtr < &tDummyVariableOnStack) {
        tHeapPtr++;
    }
// then count untouched patterns
    uint16_t tStackFree = 0;
    while (*tHeapPtr == HEAP_STACK_UNTOUCHED_VALUE && tHeapPtr < &tDummyVariableOnStack) {
        tHeapPtr++;
        tStackFree++;
    }
// word -> bytes
    return tStackFree;
}

void printStackFreeMinimumBytes(Print * aSerial) {
    aSerial->print(F("Minimum free Stack[bytes]="));
    aSerial->println(getStackFreeMinimumBytes());
}

/*
 * Returns actual start of free heap
 * Usage for print:
 Serial.print(F("HeapStart=0x"));
 Serial.println((uintptr_t) getHeapStart(), HEX);
 */
uint8_t * getHeapStart(void) {
    extern unsigned int __heap_start;
    extern void * __brkval;

    uint8_t * tHeapPtr = (uint8_t *) __brkval;
    if (tHeapPtr == 0) {
        tHeapPtr = (uint8_t *) &__heap_start;
    }
    return tHeapPtr;
}

/*
 * Get amount of maximum available memory for malloc()
 * FreeRam - __malloc_margin (128 for ATmega328)
 */
uint16_t getFreeHeap(void) {
    return getFreeRam() - __malloc_margin; // (128)
}

void printFreeHeap(Print * aSerial) {
    aSerial->print(F("Free Heap[bytes]="));
    aSerial->println(getFreeHeap());
}

/*
 * Get amount of free RAM = Stack - Heap
 */
uint16_t getFreeRam(void) {
    extern unsigned int __heap_start;
    extern void *__brkval;

    uint16_t tFreeRamBytes;

    if (__brkval == 0) {
        tFreeRamBytes = SP - (int) &__heap_start;
    } else {
        tFreeRamBytes = SP - (int) __brkval;
    }
    return (tFreeRamBytes);
}

void printFreeRam(Print * aSerial) {
    aSerial->print(F("Free Ram/Stack[bytes]="));
    aSerial->println(getFreeRam());
}

bool isAddressInRAM(void * aAddressToCheck) {
    return (aAddressToCheck <= (void *) RAMEND);
}

bool isAddressBelowHeap(void * aAddressToCheck) {
    extern void * __brkval;
    uint8_t * tHeapPtr = (uint8_t *) __brkval;
    return (aAddressToCheck < tHeapPtr);
}

/********************************************
 * SLEEP AND WATCHDOG STUFF
 *
 * For sleep modes see sleep.h
 * SLEEP_MODE_IDLE
 * SLEEP_MODE_ADC
 * SLEEP_MODE_PWR_DOWN
 * SLEEP_MODE_PWR_SAVE
 * SLEEP_MODE_STANDBY
 * SLEEP_MODE_EXT_STANDBY
 ********************************************/
volatile uint16_t sNumberOfSleeps = 0;

#ifndef MILLIS_UTILS_H_
// copied from MillisUtils.h
/*
 * storage for millis value to enable compensation for interrupt disable at signal acquisition etc.
 */
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)  || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#define timer0_millis millis_timer_millis // The ATTinyCore libraries use other variable name in wiring.c
#endif

extern volatile unsigned long timer0_millis;
#endif // MILLIS_UTILS_H_

void initSleep(uint8_t tSleepMode) {
    sleep_enable()
    ;
    set_sleep_mode(tSleepMode);
}

/*
 * aWatchdogPrescaler can be 0 (15 ms) to 3(120 ms), 4 (250 ms) up to 9 (8000 ms)
 */
uint16_t computeSleepMillis(uint8_t aWatchdogPrescaler) {
    uint16_t tResultMillis = 8000;
    for (uint8_t i = 0; i < (9 - aWatchdogPrescaler); ++i) {
        tResultMillis = tResultMillis / 2;
    }
    return tResultMillis;
}
/*
 * aWatchdogPrescaler (see wdt.h) can be one of
 * WDTO_15MS, 30, 60, 120, 250, WDTO_500MS
 * WDTO_1S to WDTO_8S
 */
void sleepWithWatchdog(uint8_t aWatchdogPrescaler, bool aAdjustMillis) {
    MCUSR = ~_BV(WDRF); // Clear WDRF in MCUSR to enable a correct interpretation of MCUSR after reset

    // use wdt_enable() since it handles that the WDP3 bit is in bit 5 of the WDTCSR register
    wdt_enable(aWatchdogPrescaler);

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__)
#define WDTCSR  WDTCR
#endif
    WDTCSR |= _BV(WDIE) | _BV(WDIF); // Watchdog interrupt enable + reset interrupt flag -> needs ISR(WDT_vect)
    sei(); // enable interrupts
    sleep_cpu()
    ;
    wdt_disable(); // Because next interrupt will lead to a reset, since wdt_enable() sets WDE / Watchdog System Reset Enable

    /*
     * Since timer clock may be disabled adjust millis only if not slept in IDLE mode (SM2...0 bits are 000)
     */
#if defined(SM2)
    if (aAdjustMillis && (SMCR & ((_BV(SM2) | _BV(SM1) | _BV(SM0)))) != 0) {
#elif ! defined(SMCR)
        if (aAdjustMillis && (MCUCR & ((_BV(SM1) | _BV(SM0)))) != 0) {
#else
    if (aAdjustMillis && (SMCR & ((_BV(SM1) | _BV(SM0)))) != 0) {
#endif
        timer0_millis += computeSleepMillis(aWatchdogPrescaler);
    }
}

/*
 * Watchdog wakes CPU periodically and all we have to do is call sleep_cpu();
 * aWatchdogPrescaler (see wdt.h) can be one of
 * WDTO_15MS, 30, 60, 120, 250, WDTO_500MS
 * WDTO_1S to WDTO_8S
 */
void initPeriodicSleepWithWatchdog(uint8_t tSleepMode, uint8_t aWatchdogPrescaler) {
    sleep_enable()
    ;
    set_sleep_mode(tSleepMode);
    MCUSR = ~_BV(WDRF); // Clear WDRF in MCUSR

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
#define WDTCSR  WDTCR
#endif
    // Watchdog interrupt enable + reset interrupt flag -> needs ISR(WDT_vect)
    uint8_t tWDTCSR = _BV(WDIE) | _BV(WDIF) | (aWatchdogPrescaler & 0x08 ? _WD_PS3_MASK : 0x00) | (aWatchdogPrescaler & 0x07); // handles that the WDP3 bit is in bit 5 of the WDTCSR register,
    WDTCSR = _BV(WDCE) | _BV(WDE); // clear lock bit for 4 cycles by writing 1 to WDCE AND WDE
    WDTCSR = tWDTCSR; // set final Value
}

/*
 * This interrupt wakes up the cpu from sleep
 */
ISR(WDT_vect) {
    sNumberOfSleeps++;
}

/*
 * 0 -> %1
 * _BV(CLKPS0) -> %2
 * _BV(CLKPS1) -> %4
 * _BV(CLKPS1) | _BV(CLKPS0) -> 8 etc. up to 256
 */
void setclockDivisionFactor(uint8_t aDivisionBits) {
    CLKPR = _BV(CLKPCE);
    CLKPR = aDivisionBits;
}

#endif // defined(__AVR__)
