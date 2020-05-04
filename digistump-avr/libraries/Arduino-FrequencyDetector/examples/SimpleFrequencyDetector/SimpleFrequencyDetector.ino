/*
 * SimpleFrequencyDetector.cpp
 *
 * SimpleFrequencyDetector reads an analog signal e.g. from a MAX9814 Module at A1 and computes the frequency.
 * If frequency is in the range of 1400 to 1700 Hz, the Arduino built in LED will light up.
 *
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
 */

/*
 *      + 5 V / 3.3 V         o--O PIN REF
 *      |                     |
 *      |                     _
 *      |                    | |
 * MAX4466 / 9814 MICROPHONE | | 1 M
 *  AMPLIFIER / MODULE       |_|
 *      |                     |
 *     |O ---------||---------o--O PIN A1
 *      |         10 nF       |
 *      |                     _
 *      |                    | |
 *      |                    | | 1 M
 *     ___                   |_|
 *                            |
 *                            |
 *                           ___
 *
 */

#include <Arduino.h>

#define VERSION_EXAMPLE "2.0"

#define LED_NO_TRIGGER  5
#define LED_SIGNAL_STRENGTH  6
#define LED_PLAUSI_FIRST  7
#define LED_PLAUSI_DISTRIBUTION  8

// Enable this to generate output for Arduino Serial Plotter (Ctrl-Shift-L)
//#define PRINT_FOR_SERIAL_PLOTTER
#define INFO
#if ! defined(LED_BUILTIN) && defined(ARDUINO_AVR_DIGISPARK)
#define LED_BUILTIN PB1
#endif

#include "FrequencyDetector.h"

#if defined(INFO)
#include "AVRUtils.h" // for getFreeRam()
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__)
    while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ "\r\nVersion " VERSION_EXAMPLE " from " __DATE__));

    // initialize the digital pin as an output.
    pinMode(LED_PLAUSI_FIRST, OUTPUT);
    pinMode(LED_PLAUSI_DISTRIBUTION, OUTPUT);
    pinMode(LED_SIGNAL_STRENGTH, OUTPUT);
    pinMode(LED_NO_TRIGGER, OUTPUT);

    /*
     * initialize FrequencyDetector
     */
    setFrequencyDetectorControlDefaults();
    /*
     * Set channel, reference, sample rate and threshold for low signal detection.
     * Set reference to 1.1Volt for AC coupled signal.
     * This is equivalent to an additional signal amplification of around 4.
     */
    setFrequencyDetectorReadingValues(ADC_CHANNEL_DEFAULT, INTERNAL, PRESCALE_VALUE_DEFAULT, RAW_VOLTAGE_MIN_DELTA_DEFAULT);

    // set my Frequency range
    setFrequencyDetectorMatchValues(1400, 1700);
#ifdef INFO
    Serial.print(F("Free Ram/Stack[bytes]="));
    Serial.println(getFreeRam());
#endif
}

void loop() {
    /*
     * Read samples and compute and output frequency and do plausi.
     */
    uint16_t tFrequency = readSignal();
    tFrequency = doPlausi();
    computeDirectAndFilteredMatch(tFrequency);

    /*
     * Show errors on LED's
     */
    digitalWrite(LED_SIGNAL_STRENGTH, LOW);
    digitalWrite(LED_PLAUSI_FIRST, LOW);
    digitalWrite(LED_PLAUSI_DISTRIBUTION, LOW);
    digitalWrite(LED_NO_TRIGGER, LOW);

    if (tFrequency == SIGNAL_STRENGTH_LOW) {
        digitalWrite(LED_SIGNAL_STRENGTH, HIGH);
    }
    if (tFrequency == SIGNAL_FIRST_LAST_PLAUSI_FAILED) {
        digitalWrite(LED_PLAUSI_FIRST, HIGH);
    }
    if (tFrequency == SIGNAL_DISTRIBUTION_PLAUSI_FAILED) {
        digitalWrite(LED_PLAUSI_DISTRIBUTION, HIGH);
    }
    if (tFrequency == SIGNAL_NO_TRIGGER) {
        digitalWrite(LED_NO_TRIGGER, HIGH);
    }

#ifdef PRINT_FOR_SERIAL_PLOTTER
    /*
     *  Print values for Arduino Serial Plotter
     */
    Serial.print(FrequencyDetectorControl.MatchDropoutCount * 64);
    Serial.print(" ");
    // FrequencyMatchDirect 0 to 3
    Serial.print(FrequencyDetectorControl.FrequencyMatchDirect * 95);

    Serial.print(" ");
    // MatchLowPassFiltered 0 to 200
    Serial.print(FrequencyDetectorControl.MatchLowPassFiltered * 2);
    Serial.print(" ");
    // FrequencyMatchFiltered 0 to 3
    Serial.print(FrequencyDetectorControl.FrequencyMatchFiltered * 100);

    // print them last to leave the bright colors for the first values
    uint16_t tFrequencyForPlot = tFrequency;
    if (tFrequencyForPlot <= SIGNAL_MAX_ERROR_CODE) {
        tFrequencyForPlot = 600;
    }
    Serial.print(tFrequencyForPlot);
    Serial.print(" ");
    Serial.print(FrequencyDetectorControl.FrequencyFiltered);
    Serial.print(" ");
    Serial.println();
#endif

    //reset match indicator led
    digitalWrite(LED_BUILTIN, LOW);

    if (tFrequency > SIGNAL_MAX_ERROR_CODE) {
        /*
         * No signal errors here -> compute match
         */
        if (FrequencyDetectorControl.FrequencyMatchDirect == FREQUENCY_MATCH) {
            // signal match
            digitalWrite(LED_BUILTIN, HIGH);
        }

    } else {
        // incompatible with Serial Plotter
//            Serial.println(reinterpret_cast<const __FlashStringHelper *>(ErrorStrings[tFrequency]));
    }
}
