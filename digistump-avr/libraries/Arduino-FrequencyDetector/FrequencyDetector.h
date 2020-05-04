/*
 * FrequencyDetector.h
 *
 * Analyzes a microphone signal and outputs the detected frequency.
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

#ifndef FREQUENCYDETECTOR_H_
#define FREQUENCYDETECTOR_H_

/*
 * Version 1.1.0 - 1/2020
 * - Corrected formula for compensating millis().
 * - New field PeriodOfOneReadingMillis.
 * - Now accept dropout values in milliseconds.
 * - New functions printLegendForArduinoPlotter() and printDataForArduinoPlotter().
 */

//#define FREQUENCY_RANGE_LOW // use it for frequencies below approximately 400 Hz
#if ! defined(FREQUENCY_RANGE_LOW) && ! defined(FREQUENCY_RANGE_HIGH)
#define FREQUENCY_RANGE_DEFAULT // good for frequencies from 400 to 3000 Hz
#endif
//#define FREQUENCY_RANGE_HIGH // use it for frequencies above approximately 3000 Hz

/*
 * Global settings which are required at compile time
 */
/*
 * Number of samples used for detecting the frequency of the signal.
 * 1024 16 MHz clock with prescaler 128: 106.496 milliseconds /  9.39 Hz. With 13 cycles/sample (=> 104 usec/sample |  9615 Hz sample rate)
 * 1024 16 MHz clock with prescaler  64:  53.248 milliseconds / 18.78 Hz. With 13 cycles/sample (=>  52 usec/sample | 19230 Hz sample rate)
 * 1024 16 MHz clock with prescaler  16:  13.312 milliseconds / 75.12 Hz. With 13 cycles/sample (=>  13 usec/sample | 76923 Hz sample rate)
 * 512   1 MHz clock with prescaler   4:  26.624 milliseconds / 37.56 Hz. With 13 cycles/sample (=>  52 usec/sample | 19230 Hz sample rate)
 */
#define NUMBER_OF_SAMPLES 512
//#define NUMBER_OF_SAMPLES 1024

/*
 * Defaults for plausibility
 */
#define MIN_SAMPLES_PER_PERIOD 8   // => Max frequency is 2403 Hz at 52 usec/sample, 9612 Hz at 13 usec/sample
// Fixed values for plausibility
#define LEADING_TRAILING_TRIGGER_MARGIN (NUMBER_OF_SAMPLES / 8) // Margin for doPlausi() where at least one trigger (eg. TriggerFirstPosition) must be detected
#define SIZE_OF_PERIOD_LENGTH_ARRAY_FOR_PLAUSI (NUMBER_OF_SAMPLES / MIN_SAMPLES_PER_PERIOD)

/*
 * Defaults for reading
 */
#define ADC_CHANNEL_DEFAULT 1 // Channel ADC1 (PB2 on ATtiny85)
#define RAW_VOLTAGE_MIN_DELTA_DEFAULT 0x40 // 1/16 of max amplitude for minimum signal strength

/*
 * Defaults for match
 */
#define FREQUENCY_MIN_DEFAULT 1000
#define FREQUENCY_MAX_DEFAULT 2000

/*
 * Milliseconds (converted to number of readings) of allowed error (FrequencyRaw <= SIGNAL_MAX_ERROR_CODE) conditions, before match = FREQUENCY_MATCH_INVALID
 */
#define MAX_DROPOUT_MILLIS_BEFORE_NO_FILTERED_MATCH_DEFAULT 200

/*
 * Milliseconds (converted to number of readings) of required valid readings (FrequencyRaw > SIGNAL_MAX_ERROR_CODE) before any (lower, match, higher) match - to avoid short flashes at random signal input
 */
#define MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH_DEFAULT 150

// sample time values for Prescaler for 16 MHz 4(13*0,25=3,25 us), 8(6,5 us), 16(13 us), 32(26 us), 64(52 us), 128(104 us)
#define ADC_PRESCALE2    1
#define ADC_PRESCALE4    2
#define ADC_PRESCALE8    3
#define ADC_PRESCALE16   4
#define ADC_PRESCALE32   5
#define ADC_PRESCALE64   6
#define ADC_PRESCALE128  7

/*
 * Default timing for reading is 19,23 kHz sample rate.
 * Formula is F_CPU / (PrescaleFactor * 13)
 * For frequency below 400 Hz it might be good to use FREQUENCY_RANGE_LOW to e.g. increase PRESCALE_VALUE_DEFAULT from PRESCALE64 to PRESCALE128.
 * For frequencies above 3 kHz it might be good to use FREQUENCY_RANGE_HIGH to e.g. decrease PRESCALE_VALUE_DEFAULT from PRESCALE64 to PRESCALE32 or even lower.
 */
#if defined(FREQUENCY_RANGE_DEFAULT)
#  if F_CPU == 16000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE64 // 52 microseconds per ADC sample at 16 Mhz Clock => 19.23 kHz sample rate
#  elif F_CPU == 8000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE32 // 52 microseconds per ADC sample at 8 Mhz Clock => 19.23 kHz sample rate
#  elif F_CPU == 1000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE4 // 52 microseconds per ADC sample at 1 Mhz Clock => 19.23 kHz sample rate
#  endif
#define MICROS_PER_SAMPLE 52
#elif defined(FREQUENCY_RANGE_LOW)
#  if F_CPU == 16000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE128 // 104 microseconds per ADC sample at 16 Mhz Clock => 9.615 kHz sample rate
#  elif F_CPU == 8000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE64 // 104 microseconds per ADC sample at 8 Mhz Clock => 9.615 kHz sample rate
#  elif F_CPU == 1000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE8 // 104 microseconds per ADC sample at 1 Mhz Clock => 9.615 kHz sample rate
#  endif
#define MICROS_PER_SAMPLE 104
#elif defined(FREQUENCY_RANGE_HIGH)
#  if F_CPU == 16000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE16 // 13 microseconds per ADC sample at 16 Mhz Clock => 76.923 kHz sample rate
#define MICROS_PER_SAMPLE 13
#  elif F_CPU == 8000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE8 // 13 microseconds per ADC sample at 8 Mhz Clock => 76.923 kHz sample rate
#define MICROS_PER_SAMPLE 13
#  elif F_CPU == 1000000L
#define PRESCALE_VALUE_DEFAULT ADC_PRESCALE2 // 26 microseconds per ADC sample at 1 Mhz Clock => 38.461 kHz sample rate
#define MICROS_PER_SAMPLE 26
#  endif
#endif
#ifndef PRESCALE_VALUE_DEFAULT
# error "F_CPU is not one of 16000000, 8000000 or 1000000"
#endif

#define CLOCKS_FOR_READING_NO_LOOP 625 // extra clock cycles outside of the loop for one signal reading. Usefd to compensate millis();
#define MICROS_PER_BUFFER_READING ((MICROS_PER_SAMPLE * NUMBER_OF_SAMPLES) + CLOCKS_FOR_READING_NO_LOOP)

// number of allowed error (FrequencyRaw <= SIGNAL_MAX_ERROR_CODE) conditions, before match = FREQUENCY_MATCH_INVALID
#define MAX_DROPOUT_COUNT_BEFORE_NO_FILTERED_MATCH_DEFAULT ((MAX_DROPOUT_MILLIS_BEFORE_NO_FILTERED_MATCH_DEFAULT * 1000L) / MICROS_PER_BUFFER_READING)
// number of required valid readings (FrequencyRaw > SIGNAL_MAX_ERROR_CODE) before any (lower, match, higher) match - to avoid short flashes at random signal input
#define MIN_NO_DROPOUT_COUNT_BEFORE_ANY_MATCH_DEFAULT ((MIN_NO_DROPOUT_MILLIS_BEFORE_ANY_MATCH_DEFAULT * 1000L) / MICROS_PER_BUFFER_READING)

// FrequencyRaw error values
#define SIGNAL_NO_TRIGGER 0
#define SIGNAL_STRENGTH_LOW 1
// You get this error code if no trigger occurs in the first or last 128 samples because signal is noisy or or only a burst
#define SIGNAL_FIRST_LAST_PLAUSI_FAILED 2
// You get this error code if more than 1/8 of the samples are greater than 1.5 or less than 0.75 of the average period
#define SIGNAL_DISTRIBUTION_PLAUSI_FAILED 3
#define SIGNAL_MAX_ERROR_CODE 3 // the highest error value

const char ErrorString_0[] PROGMEM = "No trigger";
const char ErrorString_1[] PROGMEM = "Signal low";
const char ErrorString_2[] PROGMEM = "No signal zero crossing at start or end of sample";
const char ErrorString_3[] PROGMEM = "Periods between signal zero crossing during the sample are too different";
extern const char *ErrorStrings[SIGNAL_MAX_ERROR_CODE + 1];

const char ErrorStringShort_2[] PROGMEM = "No 0 xing at start or end";
const char ErrorStringShort_3[] PROGMEM = "Periods too different";
extern const char *ErrorStringsShort[SIGNAL_MAX_ERROR_CODE + 1];
// Result values for Match*
enum MatchStateEnum {
    FREQUENCY_MATCH_INVALID /*Errors have happened*/, FREQUENCY_MATCH_LOWER, FREQUENCY_MATCH, FREQUENCY_MATCH_HIGHER
};

/*
 * Values for MatchLowPassFiltered
 * Valid values are filtered values from 50 to 150
 */
#define FILTER_VALUE_MAX        200
#define FILTER_VALUE_MIN        0
#define FILTER_VALUE_MIDDLE     ((FILTER_VALUE_MAX + FILTER_VALUE_MIN)/2)
#define FILTER_VALUE_THRESHOLD  (FILTER_VALUE_MIDDLE/2)
#define FILTER_VALUE_MATCH      FILTER_VALUE_MIDDLE
#define FILTER_VALUE_MATCH_HIGHER_THRESHOLD     (FILTER_VALUE_MAX - FILTER_VALUE_THRESHOLD)
#define FILTER_VALUE_MATCH_LOWER_THRESHOLD      (FILTER_VALUE_MIN + FILTER_VALUE_THRESHOLD)

struct FrequencyDetectorControlStruct {

    /**********************************************
     * All values are used or set by readSignal()
     *********************************************/
    // INPUT
    /*
     * 3 Values set by setFrequencyDetectorReadingPrescaleValue()
     */
    uint8_t ADCPrescalerValue;
    uint16_t FrequencyOfOneSample;      // to compute the frequency from the number of samples of one signal wave
    uint16_t PeriodOfOneSampleMicros;   // to compute the matches required from the number of loops
    uint16_t PeriodOfOneReadingMillis;  // to correct the millis() value after each reading

    /*
     * Value set by setFrequencyDetectorReadingValues()
     * Minimum signal strength value to produce valid output and do new trigger level computation. Otherwise return SIGNAL_STRENGTH_LOW
     * Threshold for minimum SignalDelta of raw ADC value for valid signal strength. 0x40=312 mV at 5 millivolt and 68.75 mVolt at 1.1 volt, 0x20=156/34,37 millivolt
     */
    uint16_t RawVoltageMinDelta;

    // INTERNALLY
    /*
     * internally computed values for automatic trigger level adjustment
     */
    uint16_t TriggerLevel; // = MinValue + ((MaxValue - MinValue)/2)
    uint16_t TriggerLevelLower; // = TriggerLevel - (tDelta / 8) - for Hysteresis

    // OUTPUT
    /*
     * Values of sampled signal input
     */
    uint16_t SignalDelta; // MaxValue - MinValue
    uint16_t AverageLevel;  // = SumOfSampleValues / NumberOfSamples

    /*
     * Values computed by readSignal() to be used by doPlausi()
     */
    uint16_t FrequencyRaw;   // Frequency in Hz set by readSignal() or "error code"  SIGNAL_... set by doPlausi()
    uint8_t PeriodCount; // Count of periods in current reading - !!! cannot be greater than SIZE_OF_PERIOD_LEGTH_ARRAY_FOR_PLAUSI - 1)!!!
    uint8_t PeriodLength[SIZE_OF_PERIOD_LENGTH_ARRAY_FOR_PLAUSI]; // Array of period length of the signal for plausi, size is NUMBER_OF_SAMPLES / 8
    uint16_t TriggerFirstPosition; // position of first detection of a trigger in all samples
    uint16_t TriggerLastPosition;  // position of last detection of a trigger in all samples

    /**************************************************
     * 9 Parameters for computeDirectAndFilteredMatch()
     *************************************************/
    // INPUT
    uint16_t FrequencyMatchLow;   // Thresholds for matching
    uint16_t FrequencyMatchHigh;

    uint8_t MaxMatchDropoutCount; // number of allowed error (FrequencyRaw <= SIGNAL_MAX_ERROR_CODE) conditions, before match = FREQUENCY_MATCH_INVALID
    uint8_t MinMatchNODropoutCount; // number of required valid readings (FrequencyRaw > SIGNAL_MAX_ERROR_CODE) before any (lower, match, higher) match - to avoid short flashes at random signal input
    // INTERNALLY
    // Clipped at MaxMatchDropoutCount + MinMatchNODropoutCount, so at least MinMatchNODropoutCount matches must happen to set FrequencyMatchFiltered not to FREQUENCY_MATCH_INVALID
    uint8_t MatchDropoutCount;      // Current dropout count. If value falls below MaxMatchDropoutCount, filtered match is valid.


    // OUTPUT
    uint16_t FrequencyFiltered;   // Low pass filter value for frequency, e.g. to compute stable difference to target frequency.

    MatchStateEnum FrequencyMatchDirect; // Result of match: 0 to 3, FREQUENCY_MATCH_INVALID, FREQUENCY_MATCH_LOWER, FREQUENCY_MATCH, FREQUENCY_MATCH_HIGHER
    MatchStateEnum FrequencyMatchFiltered; // same range asFrequencyMatchDirect. Match state processed by low pass filter
    // INTERNALLY
    uint8_t MatchLowPassFiltered; // internal value 0 to FILTER_VALUE_MAX/200. Low pass filter value for computing FrequencyMatchFiltered
};

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
// defines are from Arduino.h, the can be used without bit reordering
#undef EXTERNAL
#undef INTERNAL1V1
#undef INTERNAL
#undef INTERNAL2V56
#undef INTERNAL2V56_EXTCAP
//  #define DEFAULT 0
  #define EXTERNAL 4
  #define INTERNAL1V1 8
  #define INTERNAL INTERNAL1V1
  #define INTERNAL2V56 9
  #define INTERNAL2V56_EXTCAP 13
#endif

extern FrequencyDetectorControlStruct FrequencyDetectorControl;

void setFrequencyDetectorControlDefaults();
void setFrequencyDetectorReadingDefaults();
void setFrequencyDetectorReadingValues(uint8_t aADCChannel, uint8_t aADCReference, uint8_t aADCPrescalerValue,
        uint16_t aRawVoltageMinDelta);
void setFrequencyDetectorReadingPrescaleValue(uint8_t aADCPrescalerValue);
void setFrequencyDetectorMatchValues(uint16_t aFrequencyMin, uint16_t aFrequencyMax);
void setFrequencyDetectorDropoutCounts(uint8_t aMinMatchNODropoutCount, uint8_t aMaxMatchDropoutCount);
bool setFrequencyDetectorDropoutTimes(uint16_t aMinMatchNODropoutMillis, uint16_t aMaxMatchDropoutMillis);

uint16_t readSignal();
uint16_t doPlausi();
void computeDirectAndFilteredMatch(uint16_t aFrequency);

void printTriggerValues(Print * aSerial);
void printLegendForArduinoPlotter(Print * aSerial);
void printDataForArduinoPlotter(Print * aSerial);

#endif /* FREQUENCYDETECTOR_H_ */
