/**
 * WhistleSwitch.cpp
 *
 * Analyzes a microphone signal and toggles an output pin, if the main frequency is for a specified duration in a specified range.
 * For Tiny85 with 1 MHz
 *
 *  Copyright (C) 2014  Armin Joachimsmeyer
 *  Email: armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-FrequencyDetector https://github.com/ArminJo/Arduino-FrequencyDetector.
 *
 *  Arduino-FrequencyDetector is free software: you can redistribute it and/or modify
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
 *  It uses FrequencyDetector to recognize a whistle pitch which in turn operates a mains relay.
 *  By using different pitches it is possible to control multiple relays in a single room.
 *  If the pitch is lower than the specified frequency the feedback LED blinks slowly, if the pitch is higher it blinks fast.
 *  If the (low pass filtered) match from the FrequencyDetector library holds for MATCH_TO_LONG_MILLIS (1.0 second) after switching output,
 *  the output switches again to go back to the former state.
 *  This can be useful if a machine generated signal (e.g. from a vacuum cleaner) matches the range.
 *
 *  BUTTON OPERATION / RESET
 *  On button release, the relay state is toggled. If the press was in RELAY_DEAD_MILLIS (1) seconds after the last press, the relay is NOT toggled.
 *  This relay dead time was introduced, to avoid relay switching while trying to perform a reset by double press, see below.
 *  A reset can be performed by power off/on or by pressing the button two times with each time shorter than RESET_ENTER_BUTTON_PUSH_MILLIS (0.12 seconds)
 *  within a RESET_WAIT_TIMEOUT_MILLIS (0.3 seconds) interval.
 *  A button press longer than BUTTON_PUSH_ENTER_PROGRAM_SIMPLE_MILLIS (1.5 seconds) will enter the programming mode, which is indicated by a LED blink.
 *
 *  INFO
 *  After power up or reset, the feedback LED echoes the range number. Range number 10 indicates an individual range, programmed by advanced programming.
 *  The timeout state is signaled by short LED pulses after the range number feedback (no short pulse -> no timeout enabled).
 *
 *  TIMEOUT
 *  After a timeout of TIMEOUT_RELAY_ON_SIGNAL_MINUTES_(1 to 3) (2, 4 or 8 hours) the relay goes OFF for 1 second.
 *  In the next TIMEOUT_RELAY_SIGNAL_TO_OFF_MINUTES (3) minutes you must then press the button or whistle the pitch to cancel the timeout,
 *  otherwise the relay will switch OFF.
 *  Cancellation of timeout is acknowledged by the LED blinking 5 times for 1 second on and off.
 *  Timeout can be switched on by selecting the dummy ranges 11 to 13 and off by selecting the dummy range 10.
 *  Default is TIMEOUT_RELAY_ON_SIGNAL_MINUTES_3 (8 hours).
 *
 *  PROGRAMMING
 *  Programming is done by a long press of the button.
 *  After BUTTON_PUSH_ENTER_PROGRAM_SIMPLE_MILLIS (1.5 seconds), the feedback LED blinks once for signaling simple programming mode.
 *  After BUTTON_PUSH_ENTER_PROGRAM_ADVANCED_MILLIS (4 seconds), the feedback LED blinks twice for signaling advanced programming mode.
 *  After releasing the button the corresponding programming mode is entered.
 *
 *  SIMPLE PROGRAMMING
 *  Press the button once for range 1, twice for range 2 etc. Each button press is echoed by the feedback LED.
 *  Inactivity for PROGRAM_MODE_SIMPLE_END_DETECT_MILLIS (1.5 seconds) ends the programming mode
 *  and the feedback LED echoes the number of button presses recognized.
 *  The required duration of signal match to toggle the relay is fixed at MATCH_MILLIS_NEEDED_DEFAULT (1.2 seconds).
 *
 *  ADVANCED PROGRAMMING
 *  After entering the advanced programming state, whistle the pitch you want to detect, then press the button again.
 *  While you press the button the pitch range is measured. i.e. the minimum and maximum of the pitch you are whistling is stored.
 *  No timeout here!
 *
 *  After button release, you may press the button again before the PROGRAM_MODE_ADVANCED_END_DETECT_MILLIS (3 seconds) timeout.
 *  The duration of this second press is taken as the required duration for the signal match to toggle the relay.
 *  Otherwise the  MATCH_MILLIS_NEEDED_DEFAULT (1.2 seconds) are taken.
 *  After timeout of PROGRAM_MODE_TIMEOUT_MILLIS (5 seconds) the advanced programming mode is ended
 *  and the effective duration is echoed by the feedback LED.
 *
 *  Since the internal oscillator is not very stable, use gaps of 20/10 Hz in order to avoid overlapping of ranges of 2 different devices
 *  PREDEFINED RANGES
 1.   1700 - 2050 Hz  -> 350 Hz A6-C6
 2.   1500 - 1680 Hz  -> 180 Hz FS6-GS6
 3.   1300 - 1480 Hz  -> 180 Hz E6-FS6
 4.   1150 - 1280 Hz  -> 130 Hz D6-DS6
 5.   1000 - 1130 Hz  -> 130 Hz C6-CS6
 6.    900 -  990 Hz  ->  90 Hz A5-B5

 7.   1550 - 1900 Hz  -> 350 Hz G6-AS6
 8.   1250 - 1530 Hz  -> 380 Hz DS6-G6
 9.   1000 - 1230 Hz  -> 230 Hz C6-DS6

 10  dummy range, if chosen disable relay on timeout handling.
 11  dummy range, if chosen set relay on timeout to TIMEOUT_RELAY_ON_SIGNAL_MINUTES_1 (2 hours).
 12  dummy range, if chosen set relay on timeout to TIMEOUT_RELAY_ON_SIGNAL_MINUTES_2 (4 hours).
 13  dummy range, if chosen set relay on timeout to TIMEOUT_RELAY_ON_SIGNAL_MINUTES_3 (8 hours).
 *
 *  BUTTON
 *  Button state change is handled by an InterruptServiceRoutine
 *
 * FUSE VALUES for Tiny85 -> Enable BOD, run with 1 MHz
 * Low=0X62 (default) Int RC Osc. 8 MHz divided by 8. 14 Clk + 64 ms startup.
 * High=0XDC BrowOut at VCC=4.3Volt
 * Extended=0XFF
 *
 * Version 7.3 - 1/2020 3 timeouts available. Refactored timeout handling and timeout index interpretation changed.
 * Version 7.2 - 2/2019 timeout feedback after boot now blinking slower. Major refactoring of loop.
 * Version 7.1 - 5/2018 multiple timeouts possible.
 * Version 7.0 - 5/2018 introduced timeout for on-time duration. The setting is stored in EEPROM.
 * Version 6.1 - 3/2018 inserted gaps between ranges, added match Debug LED for 328, improved EEPROM addressing,
 *                      output version number, changed MIN_NO_DROPOUT_COUNT_BEFORE_ANY_MATCH_DEFAULT from 80 to 160 ms.
 * Version 6.0 Extracted as example and adapted to FrequencyDetector library
 * Version 5.1 Adjusted highest range + Debug for ATtiny
 * Version 5. Programming mode feedback while button pressing + fix for advanced programming
 * Version 4. Introduced MIN_NO_DROPOUT_COUNT_BEFORE_ANY_MATCH_DEFAULT to avoid short flashes on random input
 * Version 3. MATCH_TO_LONG_MILLIS 1000 instead of 600
 *
 */

#include <Arduino.h>
#include "FrequencyDetector.h"

#define VERSION_EXAMPLE "7.3"

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__)
#error "Code size of this example is too large to fit in an ATtiny 25 or 45."
#endif

#if defined(__AVR_ATtiny85__)
//#define MEASURE_TIMING // not activated yet since there is no timing pin left

//#define TRACE
//#define DEBUG
#define INFO
#include "DebugLevel.h" // to propagate above debug levels

#  if defined(INFO)
#include "ATtinySerialOut.h" // Available as Arduino library and contained in WhistleSwitch example.
#  endif

#else
//#define ARDUINO_PLOTTER
//#define MEASURE_TIMING

//#define TRACE
//#define DEBUG
#define INFO
#include "DebugLevel.h" // to propagate above debug levels

#endif // defined(__AVR_ATtiny85__)

/*
 * I can whistle from 550 to 1900 Hz (and do it easy from 950 - 1800)
 */
uint16_t predefinedRangesStart[] = { 1700, 1500, 1300, 1150, 1000, 900, 1550, 1250, 1000 };
uint16_t predefinedRangesEnd[] = { 2050, 1680, 1480, 1280, 1130, 990, 1900, 1530, 1230 };
#define PREDEFINED_RANGES_START_ARRAY_SIZE  (sizeof(predefinedRangesStart)/sizeof(predefinedRangesStart[0]))

#if defined(INFO)
#include "AVRUtils.h" // for getFreeRam()
#endif

#include "digitalWriteFast.h"

#include <avr/eeprom.h>
#include <avr/wdt.h>

// ATMEL ATTINY85 - LEGACY LAYOUT - for my old PCBs
//
//                              +-\/-+
//    RESET    Ain0 (D 5) PB5  1|    |8  Vcc
//    BUTTON - Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1 - SIGNAL_IN
// RELAY_OUT - Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1 - DEBUG TX
//                        GND  4|    |5  PB0 (D 0) pwm0 - LED_FEEDBACK
//                              +----+
//
// ATMEL ATTINY85 -  STANDARD LAYOUT - compatible with Digispark boards
//
//                                                          +-\/-+
//  RESET                  PCINT5/!RESET/ADC0/dW (D5) PB5  1|    |8  Vcc
//  BUTTON   USB+ - PCINT3/XTAL1/CLKI/!OC1B/ADC3 (D3) PB3  2|    |7  PB2 (D2) SCK/USCK/SCL/ADC1/T0/INT0/PCINT2 - TX Debug output
//  SIGNAL_IN USB- - PCINT4/XTAL2/CLKO/OC1B/ADC2 (D4) PB4  3|    |6  PB1 (D1) MISO/DO/AIN1/OC0B/OC1A/PCINT1 - LED_FEEDBACK
//                                                    GND  4|    |5  PB0 (D0) MOSI/DI/SDA/AIN0/OC0A/!OC1A/AREF/PCINT0 - RELAY_OUT
//                                                          +----+
// ATMEL ATMEGA328 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)
//      (D 0) PD0  2|    |27  PC4 (AI 4)
//      (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1) SIGNAL_IN
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13) LED_FEEDBACK
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) RELAY_OUT
//      (D 7) PD7 13|    |16  PB2 (D 10) LED_HIGHER
//      (D 8) PB0 14|    |15  PB1 (D 9)  LED_MATCH
//                  +----+

/*
 * Discrete microphone amplifier with LM308.
 *      + 5V                             _____
 *      |                             o-|_____|--o
 *      _                             |   1M     |
 *     | |                            |          |
 *     | | 4k7       ____             |  2|\     |
 *     |_| ---------|____|------------o---| \____o______o SIGNAL_IN (ADC1)
 *      | /  ____    10k      ____    |   | /6
 *      o---|____|-----o-----|____|-------|/
 *      |     4k7      |      4k7     |  3
 *     ---            |O MICROPHONE   _    LM308
 *     --- 1 uF        |             | |
 *      |              |             | | 1k
 *     ___            ___            |_|
 *                                    |
 *                                    |
 *                                   ---
 *                                   ---  100 nF
 *                                    |
 *                                   ___
 *
 *
 *
 */

#if defined(__AVR_ATtiny85__)
/*
 * Attiny85
 */
#define BUTTON_PIN 3  // 3 is compatible with 20x layout

#ifdef LEGACY_LAYOUT
// for existing Whistle Switches
#define ADC_CHANNEL ADC_CHANNEL_DEFAULT // Channel ADC1 / PB2
#define RELAY_OUT 4
#define LED_FEEDBACK 0
#define DEBUG_PIN 1
#  if (defined(INFO) || defined(DEBUG) || defined(TRACE)) && (TX_PIN != DEBUG_PIN)
#error "Change TX_PIN definition in TinySerialOut.h to match DEBUG_PIN."
#  endif

#else // LEGACY_LAYOUT
// Standard layout Digispark compatible - LED at D1 - But button and signal in clamped by 3V3 zener diode!!!
#define ADC_CHANNEL 2 // Channel ADC2 / PB4
#define RELAY_OUT 0
#define LED_FEEDBACK 1
#define DEBUG_PIN 2
#  if (defined(INFO) || defined(DEBUG) || defined(TRACE)) && (TX_PIN != DEBUG_PIN)
#error "Change TX_PIN definition in TinySerialOut.h to match DEBUG_PIN."
# endif

#endif // LEGACY_LAYOUT

#ifdef LAYOUT_FOR_20X_AMPLIFICATION
// Here button pin is also used as differential input, therefore need inverse logic -> active is HIGH
// !!! Value from digitalReadFast() can only be compared with LOW not with HIGH,
// because active from digitalReadFast() is one bit set in a byte and not 0x01!
#define IS_BUTTON_ACTIVE (digitalReadFast(BUTTON_PIN) != LOW)
#undef ADC_CHANNEL
#define ADC_CHANNEL 7 // Differential input (ADC2/PB4 - ADC3/PB3(Button)) * 20
#define ADC_REFERENCE INTERNAL

#else
#define IS_BUTTON_ACTIVE (digitalReadFast(BUTTON_PIN) == LOW)
#define ADC_REFERENCE DEFAULT

#endif // LAYOUT_FOR_20X_AMPLIFICATION

#define TIMING_PIN LED_FEEDBACK
#define TIMING_PORT PORTB
#endif // (__AVR_ATtiny85__)

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
/*
 * NANO
 */
// Pin D2
#define TIMING_PIN 2
#define TIMING_PORT PORTD

#define LED_SIGNAL_STRENGTH  5
#define LED_PLAUSI_FIRST  6
#define LED_PLAUSI_DISTRIBUTION  7
#define LED_LOWER  8
#define LED_MATCH 9
#define LED_HIGHER 10

#define RELAY_OUT  11
#define LED_FEEDBACK  LED_BUILTIN
#define BUTTON_PIN 4
#define IS_BUTTON_ACTIVE (digitalReadFast(BUTTON_PIN) == LOW)

#define ADC_CHANNEL ADC_CHANNEL_DEFAULT
#define ADC_REFERENCE INTERNAL // 1.1V
#endif // (__AVR_ATmega328P__)

// plausibility for frequency in advanced programming mode
#define MAX_ACCEPTABLE_DELTA_FREQ 100 // max delta Freq for frequency change between two consecutive measurement in advanced programming mode. Used to detect dropouts.

/*
 * Timing
 */
// Milliseconds (converted to number of readings) of required valid readings (FrequencyRaw > SIGNAL_MAX_ERROR_CODE) before any (lower, match, higher) match
// to avoid short flashes at random signal input
#define MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH 400
#define MATCH_MILLIS_NEEDED_DEFAULT (1200 - MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH) // Milliseconds of frequency detector indicating successful match before relay toggle
#define MATCH_TO_LONG_MILLIS        1000    // max milliseconds for match condition true after relay toggled, otherwise switch back to relay state before
#define RELAY_DEAD_MILLIS           800    // min milliseconds between 2 changes of relay state -> to avoid to fast relay switching
#define BUTTON_DEBOUNCE_MILLIS      40      // must be smaller than 65 since delay micros has its limitations at 64k!

// Timeout for relay ON
#define TIMEOUT_RELAY_ON_SIGNAL_MINUTES_MAX (1193 * 60) // -> 49.7 days
// after this time, the relay is switched OFF and ON to signal timeout
#define TIMEOUT_RELAY_ON_SIGNAL_MINUTES_1     120       // 2 hours timeout for state 1
#define TIMEOUT_RELAY_ON_SIGNAL_MINUTES_2     (2*120)   // 4 hours timeout for state 2
#define TIMEOUT_RELAY_ON_SIGNAL_MINUTES_3     (4*120)   // 8 hours timeout for state 2
uint16_t sTimeoutRelayOnMinutesArray[] = { 0, TIMEOUT_RELAY_ON_SIGNAL_MINUTES_1, TIMEOUT_RELAY_ON_SIGNAL_MINUTES_2,
TIMEOUT_RELAY_ON_SIGNAL_MINUTES_3 };
#define TIMEOUT_RELAY_ON_MINUTES_ARRAY_SIZE  (sizeof(sTimeoutRelayOnMinutesArray)/sizeof(sTimeoutRelayOnMinutesArray[0]))

#define TIMEOUT_RELAY_ON_INDEX_DISABLED 0
#define TIMEOUT_RELAY_ON_INDEX_DEFAULT 3 // 8 hours
#define TIMEOUT_RELAY_ON_INDEX_MAX  (TIMEOUT_RELAY_ON_MINUTES_ARRAY_SIZE - 1)

#define TIMEOUT_RELAY_SIGNAL_TO_OFF_MINUTES 3   // after signaling wait this time for feedback otherwise switch the relay OFF

// LED blink timing
#define TIMING_FREQUENCY_LOWER_MILLIS     150
#define TIMING_FREQUENCY_HIGHER_MILLIS    50
#define TIMING_FREQUENCY_HIGHER_MILLIS_MINIMUM    10
/*
 * Timing for reset
 */
#define RESET_ENTER_BUTTON_PUSH_MILLIS 120  // milliseconds for first push of double push to perform reset
#define RESET_WAIT_TIMEOUT_MILLIS 300  // milliseconds to push and release button the second time in order to perform reset command
/*
 * Timing for range programming
 */
#define BUTTON_PUSH_ENTER_PROGRAM_SIMPLE_MILLIS 1500  // milliseconds to enter simple program mode
#define BUTTON_PUSH_ENTER_PROGRAM_ADVANCED_MILLIS 4000  // milliseconds to enter advanced program mode
#define PROGRAM_MODE_TIMEOUT_MILLIS 5000  // milliseconds to enter regular detect mode if in program mode and no button press happens
#define PROGRAM_MODE_SIMPLE_END_DETECT_MILLIS 1500  // milliseconds to enter regular detect mode if in simple program mode and a range has been chosen and no button press happens
#define PROGRAM_MODE_ADVANCED_END_DETECT_MILLIS 3000  // milliseconds to enter regular detect mode if in advanced program mode and a range has been entered and no button press happens
//

struct EepromParameterStruct {
	uint16_t MillisNeededForValidMatch; // ms required for accepting match
	uint16_t FrequencyMin;
	uint16_t FrequencyMax;
	uint8_t RelayOnTimeoutIndex;
};
EepromParameterStruct sPersistentParameters;
EEMEM EepromParameterStruct sPersistentParametersEEPROM;

/*
 * States for main loop
 */
enum MainStateEnum {
	DETECT_FREQUENCY,
	WAIT_FOR_SECOND_PRESS_FOR_RESET,
	PROGRAM_SIMPLE,
	PROGRAM_ADVANCED_FREQUENCY_RANGE,
	PROGRAM_ADVANCED_FREQUENCY_DURATION,
	PROGRAM_WAIT_FOR_FEEDBACK_END
};

struct WhistleSwitchControlStruct {

	uint16_t FrequencyLast; // for advanced programming mode

	// status for main loop
	MainStateEnum MainState;
	MainStateEnum ButtonPressTempState; // Temporary MainState while button pressed, to handle feedback for long button press

	uint32_t MillisAtLastRelayChange;
	//
	bool RelayJustToggled; // do only one toggle per match
	//
	bool TimeoutSignaledOnce;  // to signal timeout reaching only once -> see TIMEOUT_RELAY_ON_SIGNAL_MINUTES
	uint8_t RelayOnTimeoutIndex; // index into sTimeoutRelayOnMinutesArray. 0 = disabled
	uint32_t RelayOnTimeoutMillis; // holds the current relay timeout in millis

	uint8_t ButtonPressCounter;

	int16_t MatchValidCount; // count for valid matches after last STATE_LED_OFF
	int16_t MatchValidNeeded; // valid matches detected required for accepting match, i.e. for toggling relay := MillisNeededForValidMatch/timeOfReading
	uint16_t MillisNeededForValidMatch;

} WhistleSwitchControl;

struct LedControlStruct {
	uint16_t LedBlinkMillis;
	int8_t LedBlinkCount; // >0 => blink n times, 0 => stop blinking, -1 => blink forever
	uint32_t MillisAtLastLEDChange;
} LedControl;

struct ButtonControlStruct {
	volatile bool ButtonStateIsActive;          // negative logic: 1 / true / active means button pin is LOW
	volatile bool ButtonStateHasJustChanged;    // Flag to enable action only once
	volatile long ButtonLastChangeMillis;       // for debouncing
	volatile uint32_t ButtonReleaseMillis;      // for double press recognition for reset
	/*
	 * Duration is set at button release or from an outside loop which polls the button state in order to check for button press timeouts,
	 * since we get no interrupt until button is released.
	 */
	volatile uint16_t ButtonPressDurationMillis; // Duration of active state.
} ButtonControl;

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/*******************************************************************************************
 * Function declaration section
 *******************************************************************************************/
void handleLongButtonPress();
void handleSimpleProgrammingState();
void handleButtonRelease();
void detectFrequency();
void checkForRelayOnTimeout();
void checkSecondPressForResetRequest();
void getAdvancedProgrammingFrequencyRange();
void handleGetDurationForAdvancedProgramming();

/*
 * aLedBlinkCount = -1 -> blink forever
 */
void setFeedbackLedBlinkState(uint16_t aLedBlinkMillis, int8_t aLedBlinkCount) {
	LedControl.LedBlinkMillis = aLedBlinkMillis;
	LedControl.LedBlinkCount = aLedBlinkCount;
}

/*
 * manage LED blinking
 */
void handleLedBlinkState() {
	if (LedControl.LedBlinkCount != 0) {
		if ((millis() - LedControl.MillisAtLastLEDChange) > LedControl.LedBlinkMillis) {
			digitalToggleFast(LED_FEEDBACK);
			LedControl.MillisAtLastLEDChange = millis();
			if (digitalReadFast(LED_FEEDBACK) == LOW) {
				if (LedControl.LedBlinkCount >= 0) {
					LedControl.LedBlinkCount--;
				}
			}
		}
	}
#if defined (TRACE) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
	Serial.print(" LedCount=");
	Serial.print(LedControl.LedBlinkCount);
	Serial.print(" ButtonDuration=");
	Serial.print(ButtonControl.ButtonPressDurationMillis);
	Serial.print(" Last=");
	Serial.print(ButtonControl.ButtonLastChangeMillis);
	Serial.print(" State=");
	Serial.println(ButtonControl.ButtonStateIsActive);
#endif // TRACE
}

void backToStateDetect() {
	WhistleSwitchControl.MainState = DETECT_FREQUENCY;
	WhistleSwitchControl.ButtonPressTempState = DETECT_FREQUENCY;
	FrequencyDetectorControl.FrequencyMatchDirect = FREQUENCY_MATCH_INVALID;
	LedControl.LedBlinkCount = 0;
}

void setMillisNeededForValidMatch(uint16_t aPeriodValidNeededMillis) {
	WhistleSwitchControl.MillisNeededForValidMatch = aPeriodValidNeededMillis;
	WhistleSwitchControl.MatchValidNeeded = aPeriodValidNeededMillis / FrequencyDetectorControl.PeriodOfOneReadingMillis;

#ifdef TRACE
	Serial.print("MatchValidNeeded=");
	Serial.print(WhistleSwitchControl.MatchValidNeeded);
	Serial.print(F(" MillisNeededForValidMatch="));
	Serial.println(WhistleSwitchControl.MillisNeededForValidMatch);
#endif
}

void eepromWriteParameter() {
	sPersistentParameters.FrequencyMin = FrequencyDetectorControl.FrequencyMatchLow;
	sPersistentParameters.FrequencyMax = FrequencyDetectorControl.FrequencyMatchHigh;
	sPersistentParameters.MillisNeededForValidMatch = WhistleSwitchControl.MillisNeededForValidMatch;
	sPersistentParameters.RelayOnTimeoutIndex = WhistleSwitchControl.RelayOnTimeoutIndex;
	eeprom_write_block((void*) &sPersistentParameters, &sPersistentParametersEEPROM, sizeof(EepromParameterStruct));

#ifdef INFO
	Serial.print(F("FrequencyMin="));
	Serial.print(sPersistentParameters.FrequencyMin);
	Serial.print(F(" FrequencyMax="));
	Serial.print(sPersistentParameters.FrequencyMax);
	Serial.print(F(" PeriodValidNeededMillis="));
	Serial.print(sPersistentParameters.MillisNeededForValidMatch);
	Serial.print(F(" RelayOnTimeoutIndex="));
	Serial.println(WhistleSwitchControl.RelayOnTimeoutIndex);
#endif

	WhistleSwitchControl.RelayOnTimeoutMillis = sTimeoutRelayOnMinutesArray[WhistleSwitchControl.RelayOnTimeoutIndex] * 60000L;
}

void eepromReadParameter() {
	// read parameter structure except timeout
#ifdef DEBUG
	Serial.print(F("&sPersistentParametersEEPROMs="));
	Serial.println((uint16_t)&sPersistentParametersEEPROM, HEX);
#endif
	eeprom_read_block((void*) &sPersistentParameters, &sPersistentParametersEEPROM, sizeof(EepromParameterStruct));

	// set variables
	WhistleSwitchControl.MillisNeededForValidMatch = sPersistentParameters.MillisNeededForValidMatch;
	FrequencyDetectorControl.FrequencyMatchLow = sPersistentParameters.FrequencyMin;
	FrequencyDetectorControl.FrequencyMatchHigh = sPersistentParameters.FrequencyMax;
	WhistleSwitchControl.RelayOnTimeoutIndex = sPersistentParameters.RelayOnTimeoutIndex;

	if (FrequencyDetectorControl.FrequencyMatchHigh
			< FrequencyDetectorControl.FrequencyMatchLow|| FrequencyDetectorControl.FrequencyMatchLow < 300 || FrequencyDetectorControl.FrequencyMatchLow > 3000
			|| FrequencyDetectorControl.FrequencyMatchHigh < 300 || FrequencyDetectorControl.FrequencyMatchHigh > 3000
			|| WhistleSwitchControl.RelayOnTimeoutIndex > TIMEOUT_RELAY_ON_INDEX_MAX) {
		/*
		 * eeprom not filled -> start with reasonable values
		 */
		FrequencyDetectorControl.FrequencyMatchLow = predefinedRangesStart[1];
		FrequencyDetectorControl.FrequencyMatchHigh = predefinedRangesEnd[1];
		WhistleSwitchControl.MillisNeededForValidMatch = MATCH_MILLIS_NEEDED_DEFAULT;
		WhistleSwitchControl.RelayOnTimeoutIndex = TIMEOUT_RELAY_ON_INDEX_DEFAULT; // set to 8 hours
#ifdef INFO
		Serial.println(F("EEPROM values were wrong, store default values to EEPROM"));
#endif
		eepromWriteParameter();
	}

	setMillisNeededForValidMatch(WhistleSwitchControl.MillisNeededForValidMatch);
	WhistleSwitchControl.RelayOnTimeoutMillis = sTimeoutRelayOnMinutesArray[WhistleSwitchControl.RelayOnTimeoutIndex] * 60000L;
}

/*
 * echo range index
 */
void signalRangeIndexByLed() {
// search range index
	uint8_t i;
	for (i = 0; i < (PREDEFINED_RANGES_START_ARRAY_SIZE); ++i) {
		if (FrequencyDetectorControl.FrequencyMatchLow == predefinedRangesStart[i]
				&& FrequencyDetectorControl.FrequencyMatchHigh == predefinedRangesEnd[i]) {
			break;
		}
	}

#ifdef INFO
	Serial.print(F("Frequency match range index="));
	Serial.println(i + 1);
#endif

// display range index
	for (uint8_t j = 0; j <= i; ++j) {
		digitalWriteFast(LED_FEEDBACK, HIGH);
		delay(TIMING_FREQUENCY_LOWER_MILLIS * 4);
		digitalWriteFast(LED_FEEDBACK, LOW);
		delay(TIMING_FREQUENCY_LOWER_MILLIS * 4);
	}
}

void signalTimeoutByLed() {
#ifdef INFO
	Serial.print(F("RelayOnTimeoutIndex="));
	Serial.println(WhistleSwitchControl.RelayOnTimeoutIndex);
#endif

	/*
	 * signal timeout state with short pulse
	 */
	for (uint8_t i = 0; i < WhistleSwitchControl.RelayOnTimeoutIndex; ++i) {
		digitalWriteFast(LED_FEEDBACK, HIGH);
		delay(TIMING_FREQUENCY_LOWER_MILLIS);
		digitalWriteFast(LED_FEEDBACK, LOW);
		delay(TIMING_FREQUENCY_LOWER_MILLIS);
	}
}

/*
 * Must be called as long as match is present to detect long matches, which will then reset relay to state before
 * toggles relay only once per match
 * handles timeout feedback
 * enables relay dead time TIMING_RELAY_DEAD_MILLIS
 */
void toggleRelay() {
	static bool sMatchTooLongDetected;

#if defined (DEBUG)
	Serial.print(F("In toggleRelay() RelayJustToggled="));
	Serial.print(WhistleSwitchControl.RelayJustToggled);
	Serial.print(' ');
#endif

	if (WhistleSwitchControl.TimeoutSignaledOnce) {
#if defined (INFO)
		Serial.print(F("Reset timeout"));
#endif
		/*
		 * Reset timeout
		 * Here we take the next match after signaling timeout as cancellation of the timeout.
		 */
		// Signal cancellation by LED.
		for (int i = 0; i < 5; ++i) {
			digitalWriteFast(LED_FEEDBACK, HIGH);
			delay(1000);
			digitalWriteFast(LED_FEEDBACK, LOW);
			delay(1000);
		}
		// Reset state
		WhistleSwitchControl.MatchValidCount = 0; // since we do a blocking wait above
		WhistleSwitchControl.TimeoutSignaledOnce = false;
		WhistleSwitchControl.MillisAtLastRelayChange = millis();

	} else {
		uint32_t tMillisSinceLastRelayChange = millis() - WhistleSwitchControl.MillisAtLastRelayChange;
		if (!WhistleSwitchControl.RelayJustToggled) {
			if (tMillisSinceLastRelayChange > RELAY_DEAD_MILLIS) {
				/*
				 * set output relay once
				 */
				sMatchTooLongDetected = false;
				digitalToggleFast(RELAY_OUT);
#if defined (INFO)
				Serial.print(F("Toggle relay now"));
#endif
				WhistleSwitchControl.MillisAtLastRelayChange = millis();
			} else {
#if defined (INFO)
				Serial.print(F("In relay dead time -> do not toggle"));
#endif
			}
		} else if (!sMatchTooLongDetected && tMillisSinceLastRelayChange > MATCH_TO_LONG_MILLIS) {
			/*
			 * match lasted too long, reset relay to previous state only once
			 */
#if defined (INFO)
			Serial.print(F("Match too long, switch to previous state"));
#endif
			digitalToggleFast(RELAY_OUT);
			sMatchTooLongDetected = true; // switch back only once
		}

	}
#if defined (INFO)
	Serial.println();
#endif
	WhistleSwitchControl.RelayJustToggled = true;
}

/*
 * process FrequencyMatchFiltered
 * set led blinking and count valid matches until toggling relay
 */
void processMatchState() {
	if (FrequencyDetectorControl.FrequencyMatchFiltered == FREQUENCY_MATCH_INVALID) {
		WhistleSwitchControl.MatchValidCount = 0;
	} else if (FrequencyDetectorControl.FrequencyMatchFiltered == FREQUENCY_MATCH_HIGHER) {
		// HIGHER -> set blink frequency according to gap between real and maximum-match pitch
		int16_t tLedBlinkMillis = TIMING_FREQUENCY_HIGHER_MILLIS
				- ((FrequencyDetectorControl.FrequencyFiltered - FrequencyDetectorControl.FrequencyMatchHigh) / 16);
		if (tLedBlinkMillis < TIMING_FREQUENCY_HIGHER_MILLIS_MINIMUM) {
			tLedBlinkMillis = TIMING_FREQUENCY_HIGHER_MILLIS_MINIMUM;
		}
#if defined (DEBUG) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
		Serial.print(F("tLedBlinkMillis="));
		Serial.println(tLedBlinkMillis);
#endif
		setFeedbackLedBlinkState(tLedBlinkMillis, -1);
		WhistleSwitchControl.MatchValidCount--;
	} else if (FrequencyDetectorControl.FrequencyMatchFiltered == FREQUENCY_MATCH_LOWER) {
		// LOWER -> set blink frequency according to gap between real and minimal-match pitch
		uint16_t tLedBlinkMillis = TIMING_FREQUENCY_LOWER_MILLIS
				+ ((FrequencyDetectorControl.FrequencyMatchLow - FrequencyDetectorControl.FrequencyFiltered) / 2);
#if defined (DEBUG) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
		Serial.print(F("tLedBlinkMillis="));
		Serial.println(tLedBlinkMillis);
#endif
		setFeedbackLedBlinkState(tLedBlinkMillis, -1);
		WhistleSwitchControl.MatchValidCount--;
	} else {
		/*
		 * successful match here
		 */
		LedControl.LedBlinkCount = 0;
		WhistleSwitchControl.MatchValidCount++;
		digitalWriteFast(LED_FEEDBACK, HIGH);
	}

	/*
	 * housekeeping
	 */
	if (WhistleSwitchControl.MatchValidCount < 0) {
		WhistleSwitchControl.MatchValidCount = 0;
	}
	if (WhistleSwitchControl.MatchValidCount >= WhistleSwitchControl.MatchValidNeeded) {
		/*
		 * valid match here  - "RelayJustToggled = true" is be set in toggleRelay()
		 */
		toggleRelay();
	} else {
		WhistleSwitchControl.RelayJustToggled = false;
	}
}

#ifdef DEBUG
void printInfos() {
	static uint16_t sFrequencyFilteredPrinted;
	static uint16_t sFrequencyPrinted;
	static int16_t sTriggerLevelPrinted;
	static int16_t sAverageLevelPrinted;
	static int16_t sSignalDeltaPrinted;
	static uint8_t sMatchLowPassFilteredPrinted;

	if (sFrequencyFilteredPrinted != FrequencyDetectorControl.FrequencyFiltered
			|| sFrequencyPrinted != FrequencyDetectorControl.FrequencyRaw
			|| sMatchLowPassFilteredPrinted != FrequencyDetectorControl.MatchLowPassFiltered
			|| abs(sTriggerLevelPrinted - (int16_t)FrequencyDetectorControl.TriggerLevel) > 10
			|| abs(sAverageLevelPrinted - (int16_t)FrequencyDetectorControl.AverageLevel) > 10
			|| abs(sSignalDeltaPrinted - (int16_t)FrequencyDetectorControl.SignalDelta) > 15) {
		sFrequencyFilteredPrinted = FrequencyDetectorControl.FrequencyFiltered;
		sFrequencyPrinted = FrequencyDetectorControl.FrequencyRaw;
		sMatchLowPassFilteredPrinted = FrequencyDetectorControl.MatchLowPassFiltered;
		sTriggerLevelPrinted = FrequencyDetectorControl.AverageLevel;
		sAverageLevelPrinted = FrequencyDetectorControl.TriggerLevel;
		sSignalDeltaPrinted = FrequencyDetectorControl.SignalDelta;

#ifdef TRACE
#if defined(__AVR_ATtiny85__)
		writeString(F("FF="));
		writeUnsignedInt(FrequencyDetectorControl.FrequencyFiltered);
		writeString(F("Hz F="));
		writeUnsignedInt(FrequencyDetectorControl.FrequencyRaw);
		writeString(F("Hz M="));
		writeUnsignedByte(FrequencyDetectorControl.MatchLowPassFiltered);
		writeString(F(" TL="));
		writeUnsignedInt(FrequencyDetectorControl.TriggerLevel);
		writeString(F(" AL="));
		writeUnsignedInt(FrequencyDetectorControl.AverageLevel);
		writeString(F(" D="));
		writeUnsignedInt(FrequencyDetectorControl.SignalDelta);
		writeChar('\n');
#else
		Serial.print(F("Filtered="));
		Serial.print(FrequencyDetectorControl.FrequencyFiltered);
		Serial.print(F("Hz "));
		if (FrequencyDetectorControl.FrequencyRaw <= SIGNAL_MAX_ERROR_CODE) {
			Serial.print(reinterpret_cast<const __FlashStringHelper *>(ErrorStringsShort[FrequencyDetectorControl.FrequencyRaw]));
		} else {
			Serial.print(F("F="));
			Serial.print(FrequencyDetectorControl.FrequencyRaw);
			Serial.print(F("Hz"));
		}
		Serial.print(F(" MatchLP="));
		Serial.print(FrequencyDetectorControl.MatchLowPassFiltered);
		Serial.print(F(" TriggerLevel="));
		Serial.print(FrequencyDetectorControl.TriggerLevel);
		Serial.print(F(" AverageLevel="));
		Serial.print(FrequencyDetectorControl.AverageLevel);
		Serial.print(F(" Delta="));
		Serial.print(FrequencyDetectorControl.SignalDelta);
		Serial.println();
#endif
#endif
	}
}
#endif

// Example for placing code at init sections see: http://www.nongnu.org/avr-libc/user-manual/mem_sections.html
void MyInit(void) __attribute__ ((naked)) __attribute__ ((section (".init8")));
void MyInit(void) {
}

/*******************************************************************************************
 * Program code starts here
 * Setup section
 *******************************************************************************************/
void setup() {
#ifdef INFO
#  if defined(__AVR_ATtiny85__)
    uint8_t tMCUSRStored = 0;
    if(MCUSR != 0){
        tMCUSRStored = MCUSR; // content of MCUSR register at startup
    } else {
        tMCUSRStored = OCR1C; // Micronucleus puts a copy here
    }
#  else
    uint8_t tMCUSRStored = MCUSR; // content of MCUSR register at startup
#  endif
#endif
	MCUSR = 0; // to prepare for next reset or power on

	/*
	 * For Arduinos with other than optiboot bootloader wdt_disable() comes too late here, since after reset the watchdog is still enabled
	 * and uses fastest prescaler value (approximately 15 ms)
	 */
	wdt_disable();
#if defined(__AVR_ATtiny85__)
#  if defined(INFO) || defined(DEBUG) || defined(TRACE)
	initTXPin();
//    useCliSeiForStrings(true); // true is default
//    delay(2); // to wait for serial line to settle / stop bit
# endif
#else // defined(__AVR_ATtiny85__)
	Serial.begin(115200);
#if defined(__AVR_ATmega32U4__)
	while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
#endif

	pinMode(LED_LOWER, OUTPUT);
	pinMode(LED_MATCH, OUTPUT);
	pinMode(LED_HIGHER, OUTPUT);
	pinMode(LED_PLAUSI_FIRST, OUTPUT);
	pinMode(LED_PLAUSI_DISTRIBUTION, OUTPUT);
	pinMode(LED_SIGNAL_STRENGTH, OUTPUT);
	pinMode(TIMING_PIN, OUTPUT);
#endif // defined(__AVR_ATtiny85__)

	pinMode(LED_FEEDBACK, OUTPUT);
	pinMode(RELAY_OUT, OUTPUT);

#ifdef LAYOUT_FOR_20X_AMPLIFICATION
// Here button pin is also used as differential input, therefore need inverse logic
	pinMode(BUTTON_PIN, INPUT);
#else
	pinMode(BUTTON_PIN, INPUT_PULLUP);  // 100kOhm to VCC
#endif

#ifdef INFO
	// Just to know which program is running on my Arduino
	Serial.print(F("\r\nSTART WhistleSwitch.cpp\r\nVersion " VERSION_EXAMPLE " from " __DATE__"\r\nMCUSR=0x"));
	Serial.println(tMCUSRStored, HEX);
#endif

// initial state of whistle switch
	backToStateDetect();
	ButtonControl.ButtonStateHasJustChanged = false;
	WhistleSwitchControl.TimeoutSignaledOnce = false;

	/*
	 * Set channel, reference, sample rate and threshold for low signal detection.
	 */
	setFrequencyDetectorReadingValues(ADC_CHANNEL, ADC_REFERENCE, PRESCALE_VALUE_DEFAULT, RAW_VOLTAGE_MIN_DELTA_DEFAULT);

	// must be called after setFrequencyDetectorReadingValues()
	setFrequencyDetectorDropoutTimes(MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH, MAX_DROPOUT_MILLIS_BEFORE_NO_FILTERED_MATCH_DEFAULT);

// get frequency parameter from eeprom
	eepromReadParameter();

#ifdef INFO
	Serial.print(F("Free Ram/Stack[bytes]="));
	Serial.println(getFreeRam());

	Serial.println(
			F(
					"Delay initial=" STR(MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH) "ms total=" STR(MATCH_MILLIS_NEEDED_DEFAULT + MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH) "ms"));

	Serial.print(F("Frequency min="));
	Serial.print(FrequencyDetectorControl.FrequencyMatchLow);
	Serial.print(F("Hz max="));
	Serial.print(FrequencyDetectorControl.FrequencyMatchHigh);
	Serial.println(F("Hz"));
#endif
	signalRangeIndexByLed();

	delay(1000);

	/*
	 * signal timeout state with short pulse
	 */
	signalTimeoutByLed();

//initPinChangeInterrupt
#if defined(__AVR_ATtiny85__)
	GIFR = _BV(PCIF); // Must clear interrupt flag in order to avoid to call this ISR, when enabling interrupts below.
	GIMSK = _BV(PCIE); //INT0 disable, PCINT enable
	PCMSK = _BV(BUTTON_PIN);
#else
	PCICR = _BV(PCIE2); //PCINT2 enable
	PCMSK2 = digitalPinToBitMask(BUTTON_PIN);// 0x20 - Pin 5 enable
#endif
#if defined(ARDUINO_PLOTTER)
	printLegendForArduinoPlotter(&Serial);
#endif
}

/************************************************************************
 * main loop
 ************************************************************************/
// noreturn saves program space!
void __attribute__((noreturn)) loop(void) {
	for (;;) {
#ifdef INFO
		static MainStateEnum sLastPrintedMainState;

		if (WhistleSwitchControl.MainState != sLastPrintedMainState) {
			sLastPrintedMainState = WhistleSwitchControl.MainState;

			Serial.print(F("MainState="));
			Serial.println(WhistleSwitchControl.MainState);
		}
#endif // INFO

		handleLedBlinkState();

		// maintain ButtonPressDurationMillis
		if (IS_BUTTON_ACTIVE) {
			ButtonControl.ButtonPressDurationMillis = millis() - ButtonControl.ButtonLastChangeMillis;
		}

		if (WhistleSwitchControl.MainState == DETECT_FREQUENCY) {
			// Frequency processing only when button is inactive
			if (IS_BUTTON_ACTIVE) {
				handleLongButtonPress();
			} else {
				handleButtonRelease(); // must be called before detectFrequency since detectFrequency introduces a big delay and the button state may have changed
				detectFrequency();
			}
			checkForRelayOnTimeout();

		} else if (WhistleSwitchControl.MainState == WAIT_FOR_SECOND_PRESS_FOR_RESET) {
			checkSecondPressForResetRequest();
		} else if (WhistleSwitchControl.MainState == PROGRAM_WAIT_FOR_FEEDBACK_END) {
			/*********************************************
			 * Wait for feedback to end
			 *********************************************/
			if (LedControl.LedBlinkCount <= 0) {
				backToStateDetect();
			}
		} else {
			/*********************************************************************
			 * PROGRAMMING starts here. State:
			 *     2 PROGRAM_SIMPLE
			 *     3 PROGRAM_ADVANCED_FREQUENCY_RANGE
			 *     4 PROGRAM_ADVANCED_FREQUENCY_DURATION,
			 *********************************************************************/
			// get new values, since the ISR can have changed it
			// check for programming timeout
			if (millis() - ButtonControl.ButtonReleaseMillis > PROGRAM_MODE_TIMEOUT_MILLIS) {

				if (WhistleSwitchControl.MainState == PROGRAM_ADVANCED_FREQUENCY_DURATION) {
					// write parameter for range to eeprom here since values are valid and programming ends here
					eepromWriteParameter();
					// echo duration
					setFeedbackLedBlinkState(WhistleSwitchControl.MillisNeededForValidMatch, 1);
				} else {
					setFeedbackLedBlinkState(TIMING_FREQUENCY_LOWER_MILLIS, 1);
				}
				WhistleSwitchControl.MainState = PROGRAM_WAIT_FOR_FEEDBACK_END;

#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
				Serial.println(F("Programming timeout"));
#endif
#if defined (DEBUG) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
				Serial.print(F("millis()="));
				Serial.print(millis());
				Serial.print(F(" ButtonReleaseMillis="));
				Serial.println(ButtonControl.ButtonReleaseMillis);
#endif
			} else if (WhistleSwitchControl.MainState == PROGRAM_SIMPLE) {
				handleSimpleProgrammingState();
			} else if (WhistleSwitchControl.MainState == PROGRAM_ADVANCED_FREQUENCY_RANGE) {
				getAdvancedProgrammingFrequencyRange();
			} else if (WhistleSwitchControl.MainState == PROGRAM_ADVANCED_FREQUENCY_DURATION) {
				handleGetDurationForAdvancedProgramming();
			}
		}
	}
// for(;;)
}

/************************************************************************
 * Functions used in main loop
 ************************************************************************/
void checkForRelayOnTimeout() {
	if (WhistleSwitchControl.RelayOnTimeoutIndex > TIMEOUT_RELAY_ON_INDEX_DISABLED) {
		/*
		 * TIMEOUT enabled - Check for relay to be ON for more than RelayOnTimeoutMillis
		 */
		bool tRelayState = digitalReadFast(RELAY_OUT);
		if (tRelayState) {
			uint32_t tMillisSinceLastRelayChange = millis() - WhistleSwitchControl.MillisAtLastRelayChange;
			if (tMillisSinceLastRelayChange > WhistleSwitchControl.RelayOnTimeoutMillis) {
				/*
				 * Timeout happened, check if additional 3 minutes are also gone without receiving cancel signal
				 */
				if (tMillisSinceLastRelayChange
						> WhistleSwitchControl.RelayOnTimeoutMillis + (TIMEOUT_RELAY_SIGNAL_TO_OFF_MINUTES * 60000L)) {
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
					Serial.println(F("Timeout detected -> switch off"));
					Serial.print(F("MillisAtLastRelayChange="));
					Serial.println(WhistleSwitchControl.MillisAtLastRelayChange);
#endif
					/*
					 * No cancellation signal received -> switch off relay
					 */
					digitalWriteFast(RELAY_OUT, LOW);
					WhistleSwitchControl.TimeoutSignaledOnce = false;
				} else if (!WhistleSwitchControl.TimeoutSignaledOnce) {
					WhistleSwitchControl.TimeoutSignaledOnce = true;
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
					Serial.println(F("Timeout detected. -> signal it"));
#endif
					digitalWriteFast(RELAY_OUT, LOW);
					delay(1500);
					digitalWriteFast(RELAY_OUT, HIGH);
				}
			}
		}
	}
}

void detectFrequency() {
	/*
	 * Read signal and get frequency
	 *
	 * readSignal() needs 26,6 ms for one loop at attiny85 1 MHz
	 * Remaining of loop needs 260 cycles, but with debug output at 115200Baud it needs 7500 cycles.
	 */
#ifdef MEASURE_TIMING
//                BIT_SET(TIMING_PORT, TIMING_PIN);
#endif
	uint16_t tFrequency = readSignal(); // needs 26.6 millis
#ifdef MEASURE_TIMING
//                BIT_CLEAR(TIMING_PORT, TIMING_PIN);
#endif

	/*
	 * plausibility check
	 */
	tFrequency = doPlausi();

	/*
	 * compute match
	 */
	computeDirectAndFilteredMatch(tFrequency);

	static uint16_t sLastTriggerLevel;
	if (FrequencyDetectorControl.FrequencyMatchDirect == FREQUENCY_MATCH_INVALID) {
		LedControl.LedBlinkCount = 0;
		if ((FrequencyDetectorControl.TriggerLevel < 0x1C0 || FrequencyDetectorControl.TriggerLevel > 0x240)
				&& abs(FrequencyDetectorControl.TriggerLevel - sLastTriggerLevel) > 0x08) {
			sLastTriggerLevel = FrequencyDetectorControl.TriggerLevel;
			digitalWriteFast(LED_FEEDBACK, LOW);
			Serial.print(F("Trigger="));
			Serial.print(FrequencyDetectorControl.TriggerLevel);
			Serial.print(F(" Average="));
			Serial.print(FrequencyDetectorControl.AverageLevel);
			Serial.print(F(" Delta="));
#if !( defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
			Serial.printHex(FrequencyDetectorControl.SignalDelta);
			Serial.print(" ");
#endif
			Serial.println(FrequencyDetectorControl.SignalDelta);
		}
	}

#ifdef DEBUG
	printInfos();
#endif

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
	/*
	 * Show state on the LEDS
	 */
	digitalWriteFast(LED_SIGNAL_STRENGTH, LOW);
	digitalWriteFast(LED_LOWER, LOW);
	digitalWriteFast(LED_MATCH, LOW);
	digitalWriteFast(LED_HIGHER, LOW);
	digitalWriteFast(LED_PLAUSI_FIRST, LOW);
	digitalWriteFast(LED_PLAUSI_DISTRIBUTION, LOW);
	if (tFrequency <= SIGNAL_STRENGTH_LOW) {
		digitalWriteFast(LED_SIGNAL_STRENGTH, HIGH);
	}
	if (tFrequency == SIGNAL_FIRST_LAST_PLAUSI_FAILED) {
		digitalWriteFast(LED_PLAUSI_FIRST, HIGH);
	}
	if (tFrequency == SIGNAL_DISTRIBUTION_PLAUSI_FAILED) {
		digitalWriteFast(LED_PLAUSI_DISTRIBUTION, HIGH);
	}
	if (FrequencyDetectorControl.FrequencyMatchDirect == FREQUENCY_MATCH_LOWER) {
		digitalWriteFast(LED_LOWER, HIGH);
	} else if (FrequencyDetectorControl.FrequencyMatchDirect == FREQUENCY_MATCH_HIGHER) {
		digitalWriteFast(LED_HIGHER, HIGH);
	} else if (FrequencyDetectorControl.FrequencyMatchDirect == FREQUENCY_MATCH) {
		digitalWriteFast(LED_MATCH, HIGH);
	}
#  ifdef ARDUINO_PLOTTER
	printDataForArduinoPlotter(&Serial);
#  endif
#endif

	/*
	 * process match state
	 * set led blinking and count valid matches until toggling relay
	 */
	processMatchState();
}

/*
 * We know we are only called if button is released / inactive
 */
void handleButtonRelease() {

	if (ButtonControl.ButtonStateIsActive) {
		// The ISR missed the last active to inactive transition because of fast bouncing
		ButtonControl.ButtonStateIsActive = false;
		uint32_t tMillis = millis();
		ButtonControl.ButtonPressDurationMillis = tMillis - ButtonControl.ButtonLastChangeMillis;
		ButtonControl.ButtonLastChangeMillis = tMillis;
		ButtonControl.ButtonReleaseMillis = tMillis;
#ifdef INFO
		Serial.println(F("Button going inactive not detected by ISR"));
#endif
	}

	if (ButtonControl.ButtonStateHasJustChanged) {
		ButtonControl.ButtonStateHasJustChanged = false;

		/*
		 * set next state / toggle relay
		 */
		if (ButtonControl.ButtonPressDurationMillis < RESET_ENTER_BUTTON_PUSH_MILLIS) {
			// wait for next button press for reset
			WhistleSwitchControl.MainState = WAIT_FOR_SECOND_PRESS_FOR_RESET;
		} else if (WhistleSwitchControl.ButtonPressTempState == DETECT_FREQUENCY) {
			/*
			 * and action ...
			 */
			toggleRelay();
		} else {
			// set programming state from button temp state
			WhistleSwitchControl.MainState = WhistleSwitchControl.ButtonPressTempState;
			WhistleSwitchControl.ButtonPressTempState = DETECT_FREQUENCY;
			WhistleSwitchControl.ButtonPressCounter = 0;
		}

#if defined (INFO)
		Serial.print(F("ButtonPressDurationMillis="));
		Serial.print(ButtonControl.ButtonPressDurationMillis);
		Serial.print(F(" MainState="));
		Serial.println(WhistleSwitchControl.MainState);
#endif
	}
}

void checkSecondPressForResetRequest() {
	/*
	 * If second press happens before timeout, then perform reset, otherwise just switch relay
	 */
	if (millis() - ButtonControl.ButtonReleaseMillis > RESET_WAIT_TIMEOUT_MILLIS) {
		// Reset timeout reached -> reset state and toggle relay
#if defined (DEBUG) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
		Serial.print(F("Timeout for reset request. Millis since last button release="));
		Serial.println(millis() - ButtonControl.ButtonReleaseMillis);
#endif
		WhistleSwitchControl.MainState = DETECT_FREQUENCY;
		WhistleSwitchControl.RelayJustToggled = false;
		toggleRelay();

	} else if (!ButtonControl.ButtonStateIsActive && ButtonControl.ButtonStateHasJustChanged) {
		/*************************************************************************************
		 * reset here. This in turn shows the programmed state
		 *************************************************************************************/
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#if defined (INFO)
		Serial.println("Simulate reset");
		Serial.flush();
#endif
		// Jump to 0x0000
		void (*ptrToReset)() = 0;// pointer to reset
		(*ptrToReset)();// reset!
#else
		// second push happened before timeout -> perform reset (this does not work with arduino or digispark bootloader)
		wdt_enable(WDTO_500MS);
		while (1) {
		};
#endif
	}
}

void handleSimpleProgrammingState() {
	if (!ButtonControl.ButtonStateIsActive && ButtonControl.ButtonStateHasJustChanged) {
		// increment range count
		ButtonControl.ButtonStateHasJustChanged = false;
		WhistleSwitchControl.ButtonPressCounter++;

#ifdef INFO
		Serial.print("Count=");
		Serial.println(WhistleSwitchControl.ButtonPressCounter);
#endif
		// echo button press
		setFeedbackLedBlinkState(TIMING_FREQUENCY_LOWER_MILLIS, 1);

	} else if ((WhistleSwitchControl.ButtonPressCounter > 0)
			&& (millis() - ButtonControl.ButtonReleaseMillis > PROGRAM_MODE_SIMPLE_END_DETECT_MILLIS)) {
		/*
		 * Programming timeout detected -> set new frequency or timeout
		 * Index is always (ButtonPressCounter - 1)
		 */
		if (WhistleSwitchControl.ButtonPressCounter <= PREDEFINED_RANGES_START_ARRAY_SIZE) {
			/*
			 * Set new frequency range here
			 */
			FrequencyDetectorControl.FrequencyMatchLow = predefinedRangesStart[WhistleSwitchControl.ButtonPressCounter - 1];
			FrequencyDetectorControl.FrequencyMatchHigh = predefinedRangesEnd[WhistleSwitchControl.ButtonPressCounter - 1];
			setMillisNeededForValidMatch(MATCH_MILLIS_NEEDED_DEFAULT);
		} else {
			/*
			 * Set/Reset "relay on" timeout
			 */
			if (WhistleSwitchControl.ButtonPressCounter > PREDEFINED_RANGES_START_ARRAY_SIZE + TIMEOUT_RELAY_ON_MINUTES_ARRAY_SIZE) {
				// clip ButtonPressCounter
				WhistleSwitchControl.ButtonPressCounter = PREDEFINED_RANGES_START_ARRAY_SIZE + TIMEOUT_RELAY_ON_MINUTES_ARRAY_SIZE;
				WhistleSwitchControl.RelayOnTimeoutIndex = TIMEOUT_RELAY_ON_MINUTES_ARRAY_SIZE - 1;
			} else {
				WhistleSwitchControl.RelayOnTimeoutIndex = WhistleSwitchControl.ButtonPressCounter - 1
						- PREDEFINED_RANGES_START_ARRAY_SIZE;
			}
		}
		eepromWriteParameter();

		// echo recognized button presses
		setFeedbackLedBlinkState(TIMING_FREQUENCY_LOWER_MILLIS * 3, WhistleSwitchControl.ButtonPressCounter);
		WhistleSwitchControl.MainState = PROGRAM_WAIT_FOR_FEEDBACK_END;
	}
}

/*
 * As long as button is pressed, the frequency range is acquired without a timeout
 */
void getAdvancedProgrammingFrequencyRange() {
	// first check if button is pressed otherwise return to enable programming timeout
	if (ButtonControl.ButtonStateIsActive && ButtonControl.ButtonStateHasJustChanged) {
		digitalWriteFast(LED_FEEDBACK, HIGH);

		while (IS_BUTTON_ACTIVE) {
			//get range values as long as button is pressed
			WhistleSwitchControl.ButtonPressCounter = 1;
			readSignal();                         // 27.6 millis
			uint16_t tFrequency = doPlausi();
			if (tFrequency > SIGNAL_MAX_ERROR_CODE) {
				// if frequency changes to fast, we assume a dropout
				if (((WhistleSwitchControl.FrequencyLast + MAX_ACCEPTABLE_DELTA_FREQ) - tFrequency)
						< (2 * MAX_ACCEPTABLE_DELTA_FREQ) || FrequencyDetectorControl.FrequencyMatchHigh == 0) {
					WhistleSwitchControl.FrequencyLast = tFrequency;
					if (tFrequency > FrequencyDetectorControl.FrequencyMatchHigh) {
						FrequencyDetectorControl.FrequencyMatchHigh = tFrequency;
					}
					if (tFrequency < FrequencyDetectorControl.FrequencyMatchLow) {
						FrequencyDetectorControl.FrequencyMatchLow = tFrequency;
					}
				}
			}

#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
			Serial.print(F("Advanced: last="));
			Serial.print(WhistleSwitchControl.FrequencyLast);
			Serial.print(F(" act="));
			Serial.print(tFrequency);
			Serial.print(F(" min="));
			Serial.print(FrequencyDetectorControl.FrequencyMatchLow);
			Serial.print(F("Hz max="));
			Serial.print(FrequencyDetectorControl.FrequencyMatchHigh);
			Serial.println(F("Hz"));

#endif
		}
		// end of acquisition, prepare for getting duration
		ButtonControl.ButtonStateHasJustChanged = false;
		digitalWriteFast(LED_FEEDBACK, LOW);
		setMillisNeededForValidMatch(MATCH_MILLIS_NEEDED_DEFAULT);
		WhistleSwitchControl.MainState = PROGRAM_ADVANCED_FREQUENCY_DURATION;
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
		Serial.println(F("Before the 5 seconds timeout, you may press the button again."));
		Serial.println(
				F("The duration of this second press is taken as the required duration for the signal match to toggle the relay."));
		Serial.println(F("If timeout happens, then 1.2 seconds are taken for duration."));
#endif
	}
}

void handleGetDurationForAdvancedProgramming() {
	// first check if button is pressed otherwise return to enable programming timeout
	if (ButtonControl.ButtonStateIsActive && ButtonControl.ButtonStateHasJustChanged) {
		ButtonControl.ButtonStateHasJustChanged = false; // reset flag
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
				Serial.println(F("Start getting duration"));
#endif
		digitalWriteFast(LED_FEEDBACK, HIGH);

		while (IS_BUTTON_ACTIVE) {
		}

		ButtonControl.ButtonStateHasJustChanged = false;
		setMillisNeededForValidMatch(ButtonControl.ButtonPressDurationMillis);
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
		Serial.print(F("Duration got[ms]="));
		Serial.println(WhistleSwitchControl.MillisNeededForValidMatch);
#endif

// write parameter with duration to eeprom
		eepromWriteParameter();

		digitalWriteFast(LED_FEEDBACK, LOW);

		// echo duration
		setFeedbackLedBlinkState(WhistleSwitchControl.MillisNeededForValidMatch, 1);
		// forces delay until led on
		LedControl.MillisAtLastLEDChange = millis();
		WhistleSwitchControl.MainState = PROGRAM_WAIT_FOR_FEEDBACK_END;
	}
}

/*
 * Check for long button press if button is still pressed in order to signal and prepare state changes
 */
void handleLongButtonPress() {
	/*
	 * prepare for state change on "ButtonReleaseJustDetected"
	 * signal programming state while button is still pressed (and not after button release)
	 */
	if (ButtonControl.ButtonPressDurationMillis > BUTTON_PUSH_ENTER_PROGRAM_SIMPLE_MILLIS) {
		if (WhistleSwitchControl.ButtonPressTempState == DETECT_FREQUENCY) {
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
			Serial.println(F("Entered simple programming state."));
			Serial.println(
					F(
							"Press the button once for range 1, twice for range 2 etc. Each button press is echoed by the feedback LED."));
			Serial.println(F("Inactivity for 1.5 seconds ends the programming mode.\r\n"));
#endif
			/*
			 * Prepare for PROGRAM_SIMPLE but do not change mainState here!
			 * Changing state is done in main loop upon button release.
			 */
			WhistleSwitchControl.ButtonPressTempState = PROGRAM_SIMPLE;
			setFeedbackLedBlinkState(TIMING_FREQUENCY_LOWER_MILLIS * 3, 1);
		} else if (ButtonControl.ButtonPressDurationMillis > BUTTON_PUSH_ENTER_PROGRAM_ADVANCED_MILLIS
				&& WhistleSwitchControl.ButtonPressTempState == PROGRAM_SIMPLE) {
#if defined (INFO) && (defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__))
			Serial.println(F("Entered advanced programming state."));
			Serial.println(
					F(
							"Before the 5 seconds timeout, whistle the pitch you want to detect, then press the button again to record."));
			Serial.println(F("While you press the button the pitch range is measured."));
			Serial.println(F("I.e. the minimum and maximum of the pitch you are whistling is stored.\r\n"));
#endif
			// prepare for PROGRAM_ADVANCED_FREQUENCY_RANGE
			WhistleSwitchControl.ButtonPressTempState = PROGRAM_ADVANCED_FREQUENCY_RANGE;
			FrequencyDetectorControl.FrequencyMatchLow = 1000;
			FrequencyDetectorControl.FrequencyMatchHigh = 0;
			setFeedbackLedBlinkState(TIMING_FREQUENCY_LOWER_MILLIS * 3, 2);
		}
	}
}

/*
 * Blocking button pin change handler
 * Problem: we are not sure that the level we read, is the level which triggers the interrupt, therefore do debouncing here and then read value again.
 * compute active period duration
 */
//
#if defined(__AVR_ATtiny85__)
ISR(PCINT0_vect) {
#else
	ISR(PCINT2_vect) {
#endif
	/*
	 * Debouncing: disable Pin Change interrupt, clear pending interrupt flag
	 * and enable timer0 interrupt for millis(), since it might be disabled now by readSignal()
	 */
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#  ifdef MEASURE_TIMING
	BIT_SET(TIMING_PORT, TIMING_PIN);
#  endif
	PCICR = 0; // disable new PCINT's, since we allow nested interrupts
	PCIFR = _BV(PCIF2);// Must clear interrupt flag in order to avoid to call this ISR again, when enabling interrupts below.
#elif defined(__AVR_ATtiny85__)
	GIMSK &= ~_BV(PCIE); // disable new PCINT's, since we allow nested interrupts
	GIFR = _BV(PCIF); // Must clear interrupt flag in order to avoid to call this ISR again, when enabling interrupts below.
#endif

#if defined(ARDUINO_AVR_DIGISPARK)
	// Digispark uses timer1 for millis()
	TIMSK |= _BV(TOIE1); // enable timer1 interrupt for millis()
#else
#  if defined(TIMSK) && defined(TOIE0)
			TIMSK |= _BV(TOIE0); // enable timer0 interrupt for millis()
#  elif defined(TIMSK0) && defined(TOIE0)
			TIMSK0 |= _BV(TOIE0);
#  else
#error  Timer 0 overflow interrupt not set correctly
#  endif
#endif
	/*
	 * Allow nested interrupts in order for timer0 to keep millis up to date while blocking wait for debouncing.
	 */
	interrupts();
	uint32_t tMillis = millis();
#if defined (TRACE)
	Serial.println("S"); // Start
#endif
	/*
	 * Blocking wait for debouncing. Can use delay, since timer0 interrupts are enabled.
	 */
	delay(BUTTON_DEBOUNCE_MILLIS);

	bool tCurrentButtonStateIsActive = IS_BUTTON_ACTIVE; // =(digitalReadFast(BUTTON_PIN) == LOW)
	if (ButtonControl.ButtonStateIsActive != tCurrentButtonStateIsActive) {
		ButtonControl.ButtonStateIsActive = tCurrentButtonStateIsActive;
		/*
		 * Valid change detected
		 */
#if defined (TRACE)
		Serial.print("L="); // Level
		Serial.println(tCurrentButtonStateIsActive);
#endif
		if (!tCurrentButtonStateIsActive) {
			/*
			 * Button release here
			 */
			ButtonControl.ButtonPressDurationMillis = tMillis - ButtonControl.ButtonLastChangeMillis;
			ButtonControl.ButtonReleaseMillis = tMillis;
		}
		ButtonControl.ButtonLastChangeMillis = tMillis; // must be set after setting ButtonPressDurationMillis
		ButtonControl.ButtonStateHasJustChanged = true;
	}
#if defined (TRACE)
	else {
		Serial.println("Spike");
	}
#endif
	/*
	 * Enable Pin Change interrupt again
	 */
#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
	if (IS_BUTTON_ACTIVE == ButtonControl.ButtonStateIsActive) {
		PCIFR = _BV(PCIF2); // Clear interrupt flag if no state change in order to cancel all interrupts generated by button bouncing
	}
	PCICR = _BV(PCIE2); //PCINT2 enable
#ifdef MEASURE_TIMING
	BIT_CLEAR(TIMING_PORT, TIMING_PIN);
#endif
#elif defined(__AVR_ATtiny85__)
	if (IS_BUTTON_ACTIVE == ButtonControl.ButtonStateIsActive) {
		GIFR = _BV(PCIF); // Clear interrupt flag if no state change in order to cancel all interrupts generated by button bouncing
	}
	GIMSK |= _BV(PCIE); //PCINT enable
#endif
}

