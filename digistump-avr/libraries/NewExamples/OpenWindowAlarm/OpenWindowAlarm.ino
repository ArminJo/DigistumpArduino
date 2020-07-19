/*
 * OpenWindowAlarm.cpp
 *
 * Overview:
 * Every 24 seconds a sample is taken of the ATtiny internal temperature sensor which has a resolution of 1 degree.
 * If temperature is lower than "old" temperature value, then an alarm is issued 5 minutes later, if "the condition still holds".
 * Detection of an open window is indicated by a longer 20 ms blink and a short click every 24 seconds.
 * A low battery (below 3.55 volt for LiPo) is indicated by beeping and flashing LED every 24 seconds. Only the beep (not the flash) is significantly longer than at open window detection.
 *
 * Internal operation:
 * An open window is detected after `TEMPERATURE_COMPARE_AMOUNT * TEMPERATURE_SAMPLE_SECONDS` (48) seconds of reading a temperature with a value of `TEMPERATURE_DELTA_THRESHOLD_DEGREE` (2) lower
 than the temperature `TEMPERATURE_COMPARE_DISTANCE * TEMPERATURE_SAMPLE_SECONDS` (192 seconds-> 3 minutes and 12 seconds) before.
 * The delay is implemented by sleeping 3 times at `SLEEP_MODE_PWR_DOWN` for a period of 8 seconds -the maximum hardware sleep time- to reduce power consumption.
 * If an **open window is detected**, this is indicated by a longer **20 ms blink** and a **short click** every 24 seconds.
 Therefore, the internal sensor has a time of 3 minutes to adjust to the outer temperature in order to capture even small changes in temperature.
 The greater the temperature change the earlier the sensor value will change and detect an open window.
 * `OPEN_WINDOW_ALARM_DELAY_MINUTES` (5) minutes after open window detection the **alarm is activated**.<br/>
 The alarm will not start or an activated alarm will stop if the current temperature is greater than the minimum measured temperature (+ 1) i.e. the window has been closed already.
 * The **initial alarm** lasts for 10 minutes. After this, it is activated for a period of 10 seconds with a increasing break from 24 seconds up to 5 minutes.
 * At **power-on** the VCC voltage is measured used to **determine the type of battery**  using `VCC_VOLTAGE_LIPO_DETECTION` (3.6 volt).
 * Every `VCC_MONITORING_DELAY_MIN` (60) minutes the battery voltage is measured. Depending on the detected battery type, **low battery voltage** is indicated by **beeping and flashing the LED every 24 seconds**.
 Only the beep (not the flash) is significantly longer than the beep for an open window detection.<br/>
 Low battery voltage is defined by `VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_LIPO` (3550 Millivolt) or `VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_STANDARD` (2350 Millivolt).
 * After power-on, the **inactive settling time** is 5 minutes. If the board is getting colder during the settling time, 4:15 (or 8:30) minutes are added to avoid false alarms after power-on.

 * If you enable `DEBUG` by commenting out line 60, you can monitor the serial output with 115200 baud at P2 to see what is happening.
 *
 * Power consumption:
 * Power consumption is 26 uA at sleep and 2.8 mA at at 1 MHz active.
 * The software loop needs 2.1 ms and with DEBUG 6.5 ms (plus 3 times 1 ms startup time) => active time is around 1/5000 or 1/2500 of total time.
 * During the loop the power consumption is 100 times more than sleep => Loop adds only 2% to 4% to total power consumption.
 * If you reprogram the fuses, you can get 6 µA power consumption.
 * For the 6 uA scenario, loop current is 500 times and startup time is negligible => loop adds 5% to 12% to total (lower) power consumption.
 *
 *
 *  Copyright (C) 2018-19  Armin Joachimsmeyer
 *  armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-OpenWindowAlarm https://github.com/ArminJo/Arduino-OpenWindowAlarm.
 *
 *  Arduino-OpenWindowAlarm is free software: you can redistribute it and/or modify
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

#include <Arduino.h>

/*
 * To see serial output, you must select "Digispark (1mhz – No USB)" as Board in the Arduino IDE!
 * And you need TinySerialOut.h + TinySerialOut.cpp in your sketch folder.
 */
//#define DEBUG // To see serial output with 115200 baud at P2 -
//#define TRACE // To see more serial output at startup with 115200 baud at P2
#define ALARM_TEST // start alarm immediately if PB0 / P0 is connected to ground

#ifdef TRACE
#define DEBUG
#endif
#ifdef DEBUG
#include "ATtinySerialOut.h"
#endif

#include <avr/boot.h>  // needed for boot_signature_byte_get()
#include <avr/power.h> // needed for clock_prescale_set()
#include <avr/sleep.h> // needed for sleep_enable()
#include <avr/wdt.h>   // needed for WDTO_8S

#define VERSION "1.3.1"
/*
 * Version 1.3.1
 * - Check for closed window happens only the first 10 minutes of alarm.
 * Version 1.3.0
 * - Changed voltage low detection.
 * - Improved DEBUG output.
 * Version 1.2.2
 * - Converted to Serial.print.
 * - New PWMTone() without tone().
 * Version 1.2.1
 * - Fixed bug in check for temperature rising after each alarm.
 * Version 1.2
 * - Improved sleep, detecting closed window also after start of alarm, reset behavior.
 * - Changed LIPO detection threshold.
 * - Fixed analog reference bug.
 */

#ifdef ALARM_TEST
#define ALARM_TEST_PIN PB0
#endif

const uint8_t OPEN_WINDOW_ALARM_DELAY_MINUTES = 5; // Wait time between window open detection and activation of alarm
const int OPEN_WINDOW_ALARM_FREQUENCY_HIGH = 2200; // Should be the resonance frequency of speaker/buzzer
const int OPEN_WINDOW_ALARM_FREQUENCY_LOW = 1100;
const int OPEN_WINDOW_ALARM_FREQUENCY_VCC_TOO_LOW = 1600; // Use a different frequency to distinguish the this alert from others

/*
 * Temperature timing
 */
const uint16_t TEMPERATURE_SAMPLE_SECONDS = 24;  // Use multiple of 8 here
const uint8_t OPEN_WINDOW_SAMPLES = (OPEN_WINDOW_ALARM_DELAY_MINUTES * 60) / TEMPERATURE_SAMPLE_SECONDS;
const uint8_t TEMPERATURE_COMPARE_AMOUNT = 2;   // compare 2 values
const uint8_t TEMPERATURE_COMPARE_DISTANCE = 8; // 3 minutes and 12 seconds
// 2. compare for slower decreasing temperatures
const uint8_t TEMPERATURE_COMPARE_2_DISTANCE = (4 * TEMPERATURE_COMPARE_DISTANCE); // 12 minutes and 48 seconds

// Array to hold enough values to compare TEMPERATURE_COMPARE_AMOUNT values with the same amount of values TEMPERATURE_COMPARE_DISTANCE positions before
const uint8_t TEMPERATURE_ARRAY_SIZE = TEMPERATURE_COMPARE_AMOUNT + TEMPERATURE_COMPARE_DISTANCE + TEMPERATURE_COMPARE_AMOUNT;
uint16_t sTemperatureArray[TEMPERATURE_ARRAY_SIZE]; // value at 0 is newest one

/*
 * Temperature values
 */
const uint16_t TEMPERATURE_DELTA_THRESHOLD_DEGREE = 2; // 1 LSB  = 1 Degree Celsius
const uint16_t TEMPERATURE_DELTA_2_THRESHOLD_DEGREE = (2 * TEMPERATURE_DELTA_THRESHOLD_DEGREE); // 1 LSB  = 1 Degree Celsius
uint16_t sTemperatureNewSum = 0;
uint16_t sTemperatureOldSum = 0;

uint16_t sTemperatureMinimumAfterWindowOpen; // for window close detection
uint16_t sTemperatureAtWindowOpen;

/*
 * Detection flags
 */
bool sOpenWindowDetected = false;
bool sOpenWindowDetectedOld = false;
uint8_t sOpenWindowSampleDelayCounter;

/*
 * VCC monitoring
 */
const uint16_t VCC_VOLTAGE_USB_DETECTION = 4300; // Above 4.3 volt we assume that USB is attached.
const uint16_t VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_LIPO = 3550; // 3.7 volt is the normal operating voltage if powered by a LiPo battery
const uint16_t VCC_VOLTAGE_LIPO_DETECTION = 3450; // Above 3.45 volt we assume that a LIPO battery is attached, below we assume a CR2032 or two AA or AAA batteries are attached.
const uint16_t VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_STANDARD = 2600; // 3.0 volt is normal operating voltage if powered by a CR2032 or two AA or AAA batteries.
const uint16_t VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_STANDARD_BOD2_7 = 2800; // BOD is at 2.7 volt typically, so we cannot get values below that

uint16_t sVCCVoltageMillivolt;
bool sVCCVoltageTooLow;
bool sLIPOSupplyDetected;
bool sBODLevelIsBelow2_7;
uint8_t getBODLevelFuses();
bool isBODSFlagExistent();
void checkVCCPeriodically();

const uint8_t VCC_MONITORING_DELAY_MIN = 60; // Check VCC every hour, because this costs extra power.
uint16_t sVCCMonitoringDelayCounter; // Counter for VCC monitoring.

//
// ATMEL ATTINY85
//
//                                +-\/-+
//          RESET/ADC0 (D5) PB5  1|    |8  Vcc
// Tone      USB+ ADC3 (D3) PB3  2|    |7  PB2 (D2) INT0/ADC1 - TX Debug output
// Tone inv. USB- ADC2 (D4) PB4  3|    |6  PB1 (D1) MISO/DO/AIN1/OC0B/OC1A/PCINT1 - (Digispark) LED
//                          GND  4|    |5  PB0 (D0) OC0A/AIN0 - Alarm Test if connected to ground
//                                +----+

#define LED_PIN  PB1
#define TONE_PIN PB4
#define TONE_PIN_INVERTED PB3

#define ADC_TEMPERATURE_CHANNEL_MUX 15
#define ADC_1_1_VOLT_CHANNEL_MUX 12
// 0 1 0 Internal 1.1 volt voltage Reference.
#define INTERNAL (2)
#define INTERNAL1V1 INTERNAL
#define SHIFT_VALUE_FOR_REFERENCE REFS0

#if (LED_PIN == TX_PIN)
#error "LED pin must not be equal TX pin."
#endif

#define LED_PULSE_LENGTH 200 // 500 is well visible, 200 is OK
#if (LED_PULSE_LENGTH < 150)
#error "LED_PULSE_LENGTH must at least be 150, since the code after digitalWrite(LED_PIN, 1) needs 150 us."
#endif

uint8_t sMCUSRStored; // content of MCUSR register at startup

void PWMtone(unsigned int aFrequency, unsigned int aDurationMillis = 0);
void delayAndSignalOpenWindowDetectionAndLowVCC();
void alarm();
void playDoubleClick();
void readTempAndManageHistory();
void resetHistory();
void initPeriodicSleepWithWatchdog(uint8_t tSleepMode, uint8_t aWatchdogPrescaler);
void sleepDelay(uint16_t aSecondsToSleep);
void delayMilliseconds(unsigned int aMillis);
uint16_t readADCChannelWithReferenceOversample(uint8_t aChannelNumber, uint8_t aReference, uint8_t aOversampleExponent);
uint16_t getVCCVoltageMillivolt(void);
void changeDigisparkClock();

#ifdef DEBUG
void printFuses(void);
void printBODSFlagExistence();
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/***********************************************************************************
 * Code starts here
 ***********************************************************************************/

void setup() {

    /*
     * store MCUSR early for later use
     */
    if (MCUSR != 0) {
        sMCUSRStored = MCUSR; // content of MCUSR register at startup
        MCUSR = 0; // to prepare for next boot.
    } else {
        sMCUSRStored = GPIOR0; // Micronucleus puts a copy here if bootloader is in ENTRY_EXT_RESET mode
        GPIOR0 = 0; // Clear it to detect a jmp 0
    }

#ifdef DEBUG
    /*
     * Initialize the serial pin as an output for Serial.print like debugging
     */
    initTXPin();
#endif

    /*
     * initialize the pins
     */
    pinMode(LED_PIN, OUTPUT);
    pinMode(TONE_PIN_INVERTED, OUTPUT);
    pinMode(TONE_PIN, OUTPUT);
#ifdef ALARM_TEST
    pinMode(ALARM_TEST_PIN, INPUT_PULLUP);
#endif

//    changeDigisparkClock();

    sBODLevelIsBelow2_7 = (getBODLevelFuses() >= 6);

#ifdef DEBUG
    Serial.println(F("START " __FILE__ "\nVersion " VERSION " from " __DATE__ "\nAlarm delay = ") STR(OPEN_WINDOW_ALARM_DELAY_MINUTES) " minutes");

    Serial.print(F("Brown Out Detection is "));
    if (getBODLevelFuses() == 7) {
        Serial.print(F("disabled => 6"));
    } else {
        Serial.print(F("enabled => "));
        if (isBODSFlagExistent()) {
            // Can disable BOD for sleep
            Serial.print(F("6"));
        } else {
            Serial.print(F("25"));
        }
    }
    Serial.println(F(" micro Ampere sleep current"));
#endif

#ifdef TRACE
    Serial.print(F("MCUSR=0x"));
    Serial.println(sMCUSRStored, HEX);
    Serial.print(F("WDTCR=0x"));
    Serial.println(WDTCR, HEX);
    Serial.print(F("OSCCAL=0x"));
    Serial.println(OSCCAL, HEX);
    printBODSFlagExistence();
    printFuses();
#endif

    /*
     * init sleep mode and wakeup period
     */
    initPeriodicSleepWithWatchdog(SLEEP_MODE_PWR_DOWN, WDTO_8S);

    /*
     * Initialize ADC channel and reference
     */
    readADCChannelWithReferenceOversample(ADC_TEMPERATURE_CHANNEL_MUX, INTERNAL1V1, 0);

    /*
     * Signal power on with a single tone or signal reset with a double click.
     */
#ifdef DEBUG
    Serial.print(F("Booting from "));
#endif
    if (sMCUSRStored & _BV(PORF)) {
        PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_HIGH, 100);
#ifdef DEBUG
        Serial.println(F("power up"));
#endif
    } else {
        playDoubleClick();
#ifdef DEBUG
        Serial.println(F("reset"));
#endif
    }

    /*
     * Blink LED at startup to show OPEN_WINDOW_MINUTES
     */
    for (int i = 0; i < OPEN_WINDOW_ALARM_DELAY_MINUTES; ++i) {
        // activate LED
        digitalWrite(LED_PIN, 1);
        delayMilliseconds(200);  // delay() is disabled, so use delayMicroseconds()
        // deactivate LED
        digitalWrite(LED_PIN, 0);
        delayMilliseconds(200);
    }

#ifdef ALARM_TEST
    if (!digitalRead(ALARM_TEST_PIN)) {
#ifdef DEBUG
        Serial.println(F("Test signal out"));
#endif
        alarm();
    }
#endif

    /*
     * Check VCC and decide if LIPO or 2 standard batteries / 1 button cell attached
     */
    sVCCVoltageMillivolt = getVCCVoltageMillivolt();
    if (sVCCVoltageMillivolt > VCC_VOLTAGE_LIPO_DETECTION) {
        sLIPOSupplyDetected = true;
    } else {
        sLIPOSupplyDetected = false;
    }

    sVCCMonitoringDelayCounter = 1; // 1 -> check directly now
    checkVCCPeriodically();

// disable digital input buffer to save power
// do not disable buffer for outputs whose values are read back
    DIDR0 = _BV(ADC1D) | _BV(ADC2D) | _BV(ADC3D) | _BV(AIN1D) | _BV(AIN0D);

    // This disables Arduino delay() and millis() timer 0 and also its interrupts which kills the deep sleep.
    PRR = _BV(PRTIM0) | _BV(PRUSI); // Disable timer 0 and USI - has no effect on Power Down current

    /*
     * wait 8 seconds, since ATtinys temperature is increased after the micronucleus boot process
     */
    sleep_cpu()
    ;
}

/*
 * Shift temperature history values ad insert new value.
 * Check if temperature decreases after power on.
 * Check if window was just opened.
 * If window was opened check if window still open -> ALARM
 * Loop needs 2.1 ms and with DEBUG 6.5 ms => active time is ca. 1/10k or 1/4k of total time and power consumption is 500 times more than sleep.
 * The sleep wakeup time for PLL clock
 * 2 ms for temperature reading
 * 0.25 ms for processing
 * 0.05 ms for LED flashing
 *  + 4.4 ms for DEBUG
 */
void loop() {

    readTempAndManageHistory(); // needs 2 milliseconds

    // activate LED after reading to signal it. Do it here to reduce delay below.
    digitalWrite(LED_PIN, 1);

    /*
     * Check if we are just after boot and temperature is decreasing
     */
    if ((sTemperatureArray[TEMPERATURE_ARRAY_SIZE - 1] == 0) && (sTemperatureArray[TEMPERATURE_ARRAY_SIZE - 2] > 0)
    /*
     * array is almost full, so check if temperature is lower than at boot time which means,
     * we ported the sensor from a warm place to its final one
     * or the window is still open and the user has pushed the reset button to avoid an alarm.
     */
    && (sTemperatureArray[0] < sTemperatureArray[TEMPERATURE_ARRAY_SIZE - 2])) {
        // Start from beginning, clear temperature array
#ifdef DEBUG
        Serial.println(F("Detected porting to a colder place -> reset"));
#endif
        resetHistory();
    } else {

        if (!sOpenWindowDetected) {
            /*
             * Check if window just opened
             */
            // tTemperatureOldSum can be 0 -> do not use tTemperatureNewSum < tTemperatureOldSum - (TEMPERATURE_DELTA_THRESHOLD_DEGREE * TEMPERATURE_COMPARE_AMOUNT)
            if (sTemperatureNewSum + (TEMPERATURE_DELTA_THRESHOLD_DEGREE * TEMPERATURE_COMPARE_AMOUNT) < sTemperatureOldSum) {
#ifdef DEBUG
                Serial.println(F("Detected window just opened -> check again in ") STR(OPEN_WINDOW_ALARM_DELAY_MINUTES) " minutes");
#endif
                sTemperatureMinimumAfterWindowOpen = sTemperatureNewSum;
                sTemperatureAtWindowOpen = sTemperatureNewSum;
                sOpenWindowDetected = true;
                sOpenWindowSampleDelayCounter = 0;
            }
        } else {
            /*
             * Here open window is detected
             * First check if window already closed -> start a new detection
             */
            if (sTemperatureNewSum > (sTemperatureMinimumAfterWindowOpen + TEMPERATURE_COMPARE_AMOUNT)) {
                sOpenWindowDetected = false;
#ifdef DEBUG
                Serial.println(F("Detected window already closed -> start again"));
#endif
                // reset history in order to avoid a new detection at next sample, since tTemperatureNewSum may still be lower than tTemperatureOldSum
                resetHistory();
            } else {
                if (sTemperatureNewSum < sTemperatureMinimumAfterWindowOpen) {
                    // set new minimum temperature
                    sTemperatureMinimumAfterWindowOpen = sTemperatureNewSum;
                }

                /*
                 * Check if alarm delay was reached
                 */
                sOpenWindowSampleDelayCounter++;
                if (sOpenWindowSampleDelayCounter >= OPEN_WINDOW_SAMPLES) {
                    /*
                     * Here delay is reached
                     * Check if still open - current temperature must be 1 degree lower than temperature at time of open detection
                     * "- TEMPERATURE_COMPARE_AMOUNT": this reduces the sensibility, but helps to detect already closed windows.
                     * You may remove this to increase sensibility.
                     */
                    if (sTemperatureNewSum <= sTemperatureAtWindowOpen - TEMPERATURE_COMPARE_AMOUNT) {
                        /*
                         * Window is still open -> ALARM
                         */
#ifdef DEBUG
                        Serial.println(F("Detected window still open -> alarm"));
#endif
                        alarm();
                    } else {
                        // Temperature not 1 degree lower than temperature at time of open detection
                        sOpenWindowDetected = false;
#ifdef DEBUG
                        Serial.println(F("Assume wrong window open detection -> start again"));
#endif
                    }
                } // delay
            } // already closed
        } // !sOpenWindowDetected
    }  // after power on and temperature is decreasing

    /*
     * VCC check every hour
     */
    checkVCCPeriodically(); // needs 4.5 ms

    delayAndSignalOpenWindowDetectionAndLowVCC(); // Introduce a delay of 22 ms if open window is detected to let the LED light longer
    // deactivate LED before sleeping
    digitalWrite(LED_PIN, 0);

    sleepDelay(TEMPERATURE_SAMPLE_SECONDS);
}

/*
 * Code to change Digispark Bootloader clock settings to get the right CPU frequency
 * and to reset Digispark OCCAL tweak.
 * Call it if you want to use the standard ATtiny85 library, BUT do not call it, if you need Digispark USB functions available for 16 MHz.
 */
void changeDigisparkClock() {
    uint8_t tLowFuse = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    if ((tLowFuse & 0x0F) == 0x01) {
        /*
         * Here we have High Frequency PLL Clock (16 or 16.5 MHz)
         */
#if (F_CPU == 1000000)
        // Divide 16 MHz Pll clock by 16 for Digispark Boards to get the requested 1 MHz
        clock_prescale_set(clock_div_16);
//        CLKPR = (1 << CLKPCE);  // unlock function
//        CLKPR = (1 << CLKPS2); // %16
#endif
#if (F_CPU == 8000000)
        // Divide 16 MHz Pll clock by 2 for Digispark Boards to get the requested 8 MHz
        clock_prescale_set(clock_div_2);
//        CLKPR = (1 << CLKPCE);  // unlock function
//        CLKPR = (1 << CLKPS0);// %2
#endif
    }

    /*
     * Code to reset Digispark OCCAL tweak
     */
#define  SIGRD  5 // needed for boot_signature_byte_get()
    uint8_t tStoredOSCCAL = boot_signature_byte_get(1);
    if (OSCCAL != tStoredOSCCAL) {
#ifdef DEBUG
        uint8_t tOSCCAL = OSCCAL;
        Serial.print(F("Changed OSCCAL from 0x"));
        Serial.print(tOSCCAL);
        Serial.print(F(" to 0x"));
        Serial.println(tStoredOSCCAL);
#endif
        // retrieve the factory-stored oscillator calibration bytes to revert the digispark OSCCAL tweak
        OSCCAL = tStoredOSCCAL;
    }
}

/*
 * Like tone(), but use OC1B (PB4) and (inverted) !OC1B (PB3)
 */
void PWMtone(unsigned int aFrequency, unsigned int aDurationMillis) {

    // Determine which prescaler to use, we are running with 1 MHz now
    uint8_t tPrescaler = 0x01;
    uint16_t tOCR = 1000000 / aFrequency; // cannot use F_CPU since clock is set to 1 MHz at runtime
    while (tOCR > 0x100 && tPrescaler < 0x0F) {
        tPrescaler++;
        tOCR >>= 1;

    }

    OCR1C = tOCR - 1; // The frequency of the PWM will be Timer Clock 1 Frequency divided by (OCR1C value + 1).
    OCR1B = OCR1C / 2; // set PWM to 50%
    GTCCR = _BV(PWM1B) | _BV(COM1B0); // Switch to PWM Mode with OC1B (PB4) + !OC1B (PB3) outputs enabled
    TCCR1 = (tPrescaler << CS10);

    delayMilliseconds(aDurationMillis);
    TCCR1 = 0; // Select no clock
    GTCCR = 0; // Disconnect OC1B + !OC1B
    digitalWrite(TONE_PIN_INVERTED, LOW);
    digitalWrite(TONE_PIN, LOW);
}

/*
 * plays alarm signal for the specified seconds
 */
void playAlarmSignalSeconds(uint16_t aSecondsToPlay) {
#ifdef DEBUG
    Serial.print(F("Play alarm for "));
    Serial.print(aSecondsToPlay);
    Serial.println(F(" seconds"));
#endif
    uint16_t tCounter = (aSecondsToPlay * 10) / 13; // == ... * 1000 (ms per second) / (1300 ms for a loop)
    if (tCounter == 0) {
        tCounter = 1;
    }
    while (tCounter-- != 0) {
        // activate LED
        digitalWrite(LED_PIN, 1);
        PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_LOW, 300);

        // deactivate LED
        digitalWrite(LED_PIN, 0);
        PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_HIGH, 1000);
    }
}

void resetHistory() {
    for (uint8_t i = 0; i < TEMPERATURE_ARRAY_SIZE - 1; ++i) {
        sTemperatureArray[i] = 0;
    }
}

void readTempAndManageHistory() {
    sTemperatureNewSum = 0;
    sTemperatureOldSum = 0;
    uint8_t tIndex = TEMPERATURE_ARRAY_SIZE - 1;
    /*
     * shift values in temperature history array and insert new one at [0]
     */
    while (tIndex >= TEMPERATURE_COMPARE_AMOUNT + TEMPERATURE_COMPARE_DISTANCE) {
        // shift TEMPERATURE_COMPARE_AMOUNT values to end and sum them up
        sTemperatureArray[tIndex] = sTemperatureArray[tIndex - 1];
        sTemperatureOldSum += sTemperatureArray[tIndex - 1];
        tIndex--;
    }
    while (tIndex >= TEMPERATURE_COMPARE_AMOUNT) {
        // shift values to end
        sTemperatureArray[tIndex] = sTemperatureArray[tIndex - 1];
        tIndex--;
    }
    while (tIndex > 0) {
        // shift (TEMPERATURE_COMPARE_AMOUNT - 1) values to end and sum them up
        sTemperatureArray[tIndex] = sTemperatureArray[tIndex - 1];
        sTemperatureNewSum += sTemperatureArray[tIndex - 1];
        tIndex--;
    }
    /*
     * Read new Temperature 16 times (typical 280 - 320 at 25 C) and add to sum
     * needs 2 ms
     */
    sTemperatureArray[0] = readADCChannelWithReferenceOversample(ADC_TEMPERATURE_CHANNEL_MUX, INTERNAL1V1, 4);
    sTemperatureNewSum += sTemperatureArray[0];

#ifdef DEBUG
    // needs 4.4 ms
    Serial.print(F("Temp="));
    Serial.print(sTemperatureArray[0]);
    Serial.print(F(" Old="));
    Serial.print(sTemperatureOldSum);
    Serial.print(F(" New="));
    Serial.println(sTemperatureNewSum);
#endif
}

/*
 * Check if history is completely filled and if temperature is rising
 */
bool checkForTemperatureRising() {
    if (sTemperatureArray[TEMPERATURE_ARRAY_SIZE - 1] != 0
            && sTemperatureNewSum > sTemperatureOldSum + (TEMPERATURE_DELTA_THRESHOLD_DEGREE * TEMPERATURE_COMPARE_AMOUNT)) {
#ifdef DEBUG
    Serial.println(F("Alarm - detected window already closed -> start again"));
#endif
        sOpenWindowDetected = false;
        resetHistory();
        return true;
    }
    return false;
}

/*
 * Generates a 2200 | 1100 Hertz tone signal for 600 seconds / 10 minutes and then play it 10 seconds with intervals starting from 24 seconds up to 5 minutes.
 * After 2 minutes the temperature is checked for the remaining 8 minutes if temperature is increasing in order to detect a closed window.
 * Check temperature at each end of break interval to discover closed window, if window was closed during the silent break, but device was not reset.
 */
void alarm() {

// First 120 seconds - just generate alarm tone
    playAlarmSignalSeconds(120);
// after 80 seconds the new (increased) temperature is stable

// prepare for new temperature check - reset history
#ifdef DEBUG
    Serial.println(F("After 120 seconds prepare for new temperature check -> reset history"));
    Serial.println(F("Play alarm for 480 seconds and check for rising temperature every 30 seconds"));
#endif
    resetHistory();

// remaining 480 seconds - check temperature while generating alarm tone
    for (uint8_t i = 0; i < 16; ++i) {
        readTempAndManageHistory();
        /*
         * Check if history is completely filled and if temperature is rising
         */
        if (checkForTemperatureRising()) {
            return;
        }
        playAlarmSignalSeconds(30);
    }

#ifdef DEBUG
    Serial.println(F("After 10 minutes continuous alarm play it now for 10 seconds with increasing delay starting at 24 seconds"));
#endif

    uint16_t tDelay = 24; // begin with 24 s, end at 600 s (5 minutes)
    /*
     * Do not check for rising temperature here, since it may break a valid alarm.
     * The alarm last for 10 minutes now and no rising temperature could be detected in this time, so it makes no sense here.
     */
    while (true) {
#ifdef DEBUG
        Serial.print(F("Alarm pause for "));
        Serial.print(tDelay);
        Serial.println(F(" seconds"));
#endif
        sleepDelay(tDelay); // Start with 24 seconds
        playAlarmSignalSeconds(10);
        noTone(TONE_PIN);
        if (tDelay < 600) { // up to 5 minutes
            tDelay += tDelay / 16;
        }

    }
}

void playDoubleClick() {
    PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_HIGH, 2);
    delayMilliseconds(100); // delay between clicks
    PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_HIGH, 2);
}

/*
 * Flash LED only for a short period to save power.
 * If open window detected, increase pulse length to give a visual feedback
 */
void delayAndSignalOpenWindowDetectionAndLowVCC() {
    if (sOpenWindowDetected) {
        sOpenWindowDetectedOld = true;
        PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_HIGH, 2); // 2 ms can be heard as a click
        delayMicroseconds(20000); // to let the led light longer

    } else if (sOpenWindowDetectedOld) {
// closing window just detected -> signal it with 2 clicks
        sOpenWindowDetectedOld = false; // do it once
        playDoubleClick();

    } else if (sVCCVoltageTooLow) {
        PWMtone(OPEN_WINDOW_ALARM_FREQUENCY_VCC_TOO_LOW, 40); // Use also a different frequency to distinguish this alert from others
    } else {
        delayMicroseconds(LED_PULSE_LENGTH - 150);  // - 150 for the duration from digitalWrite(LED_PIN, 1) until here
    }
}

/*
 * In Power Down sleep mode we have the watchdog running and ADC disabled, but powered.
 * This needs 5.6 uA.
 * If BOD is enabled by fuses -which is default for Digispark boards- we need additionally 20 uA resulting in 26 uA current.
 */
void sleepDelay(uint16_t aSecondsToSleep) {
    ADCSRA = 0; // disable ADC -> saves 150 - 200 uA
    for (uint16_t i = 0; i < (aSecondsToSleep / 8); ++i) {
        /*
         * Turn off the brown-out detector - but this works only for ATtiny85 revision C, which is hardly seen in the wild :-(.
         * It can save additional 20 uA if BOD is enabled by fuses
         */
        sleep_bod_disable()
        ;
//        uint8_t tMcucrValue = MCUCR | _BV(BODS) | _BV(BODSE);  // set to one
//        MCUCR = tMcucrValue; // set both flags to one
//        MCUCR = tMcucrValue & ~_BV(BODSE); // reset BODSE within 4 clock cycles
        sleep_cpu()
        ;
    }
}

void delayMilliseconds(unsigned int aMillis) {
    for (unsigned int i = 0; i < aMillis; ++i) {
        delayMicroseconds(1000);
    }
}

#define ADC_PRESCALE8    3 // 104 microseconds per ADC conversion at 1 MHz
uint16_t readADCChannelWithReferenceOversample(uint8_t aChannelNumber, uint8_t aReference, uint8_t aOversampleExponent) {
    uint16_t tSumValue = 0;
    ADMUX = aChannelNumber | (aReference << SHIFT_VALUE_FOR_REFERENCE);

// ADCSRB = 0; // free running mode if ADATE is 1 - is default
// ADSC-StartConversion ADATE-AutoTriggerEnable ADIF-Reset Interrupt Flag
    ADCSRA = (_BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIF) | ADC_PRESCALE8);

    for (uint8_t i = 0; i < _BV(aOversampleExponent); i++) {
        /*
         * wait for free running conversion to finish.
         * Do not wait for ADSC here, since ADSC is only low for 1 ADC Clock cycle on free running conversion.
         */
        loop_until_bit_is_set(ADCSRA, ADIF);

        ADCSRA |= _BV(ADIF); // clear bit to recognize conversion has finished
// Add value
        tSumValue += ADCL | (ADCH << 8);
//        tSumValue += (ADCH << 8) | ADCL; // this does NOT work!
    }
    ADCSRA &= ~_BV(ADATE); // Disable auto-triggering (free running mode)
    return (tSumValue >> aOversampleExponent);
}

uint16_t getVCCVoltageMillivolt(void) {
// use AVCC with external capacitor at AREF pin as reference
    uint8_t tOldADMUX = ADMUX;
    /*
     * Must wait >= 200 us if reference has to be switched to VSS
     * Must wait >= 70 us if channel has to be switched to ADC_1_1_VOLT_CHANNEL_MUX
     */
    if ((ADMUX & (INTERNAL << SHIFT_VALUE_FOR_REFERENCE)) || ((ADMUX & 0x0F) != ADC_1_1_VOLT_CHANNEL_MUX)) {
// switch AREF
        ADMUX = ADC_1_1_VOLT_CHANNEL_MUX | (DEFAULT << SHIFT_VALUE_FOR_REFERENCE);
// and wait for settling
        delayMicroseconds(400); // experimental value is > 200 us
    }
    uint16_t tVCC = readADCChannelWithReferenceOversample(ADC_1_1_VOLT_CHANNEL_MUX, DEFAULT, 2);
    ADMUX = tOldADMUX;
    /*
     * Do not wait for reference to settle here, since it may not be necessary
     */
    return ((1024L * 1100) / tVCC);
}

/*
 * called every hour
 * needs 4.5 ms
 */
void checkVCCPeriodically() {
    sVCCMonitoringDelayCounter--;
    if (sVCCMonitoringDelayCounter == 0) {
        sVCCVoltageMillivolt = getVCCVoltageMillivolt();
#ifdef DEBUG
        Serial.print(F("VCC="));
        Serial.print(sVCCVoltageMillivolt);
        Serial.print(F("mV - "));
        if (sVCCVoltageMillivolt > VCC_VOLTAGE_USB_DETECTION) {
            Serial.print(F("USB"));
        } else {
            if (sLIPOSupplyDetected) {
                Serial.print(F("LIPO"));
            } else {
                Serial.print(F("standard or button cell"));
            }
        }
        Serial.println(" detected");
#endif
        if ((sLIPOSupplyDetected && sVCCVoltageMillivolt < VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_LIPO)
                || (!sLIPOSupplyDetected
                        && ((sBODLevelIsBelow2_7 && sVCCVoltageMillivolt < VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_STANDARD)
                                || (!sBODLevelIsBelow2_7 && sVCCVoltageMillivolt < VCC_VOLTAGE_LOWER_LIMIT_MILLIVOLT_STANDARD_BOD2_7)))

                ) {
            sVCCVoltageTooLow = true;
            sVCCMonitoringDelayCounter = 4; // VCC too low -> check every 2 minutes
        } else {
            sVCCVoltageTooLow = false;
            sVCCMonitoringDelayCounter = (VCC_MONITORING_DELAY_MIN * 60) / TEMPERATURE_SAMPLE_SECONDS; // VCC OK -> check every hour
        }
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
    ;
}

uint8_t getBODLevelFuses() {
    return boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS) & (~FUSE_BODLEVEL2 | ~FUSE_BODLEVEL1 | ~FUSE_BODLEVEL0 );
}

/*
 * @return true if BODS flag is existent - should be true for ATtiny85 revision C and later
 */
bool isBODSFlagExistent() {
    sleep_bod_disable()
    ;
    /*
     * Check if flag can be set - this works only for ATtini85 revision C, which is hardly seen in the wild.
     */
    return MCUCR & _BV(BODS);
}

#ifdef DEBUG
/*
 * Output description for all fuses except "DebugWire enabled"
 */
void printFuses(void) {
    uint8_t tLowFuseBits = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    Serial.print(F("\nLowFuses="));
    Serial.printHex(tLowFuseBits);

    Serial.print(F("\nClock divide by 8 "));
    if (tLowFuseBits & ~FUSE_CKDIV8) {
        Serial.print(F("not "));
    }
    Serial.print(F("enabled\n")); // enabled is default

    Serial.print(F("Clock output "));
    if (tLowFuseBits & ~FUSE_CKOUT) {
        Serial.print(F("not "));
    }
    Serial.print(F("enabled\n")); // enabled is default

    Serial.print(F("Clock select="));
    uint8_t tClockSelectBits = tLowFuseBits & (~FUSE_CKSEL3 | ~FUSE_CKSEL2 | ~FUSE_CKSEL1 | ~FUSE_CKSEL0 );
    switch (tClockSelectBits) {
    case 1:
        Serial.print(F("16MHz PLL"));
        break;
    case 2:
        Serial.print(F("8MHz")); // default
        break;
    case 3:
        Serial.print(F("6.4MHz"));
        break;
    case 4:
        Serial.print(F("128kHz"));
        break;
    case 6:
        Serial.print(F("32.768kHz"));
        break;
    default:
        Serial.print(F("External"));
        break;
    }

    Serial.print(F("\nStart-up time="));
    uint8_t tStartUptimeBits = tLowFuseBits & (~FUSE_SUT1 | ~FUSE_SUT0 );
    if (tClockSelectBits == 1) {
        /*
         * PLL Clock has other interpretation of tStartUptimeBits
         */
        Serial.print(F("14 CK (+ 4ms)"));
        if (tLowFuseBits & ~FUSE_SUT0) {
            Serial.print(F("+ 16384 CK")); // -> 1 ms for 16 MHz clock
        } else {
            Serial.print(F(" + 1024 CK"));
        }
        if (tLowFuseBits & ~FUSE_SUT1) {
            Serial.print(F(" + 64ms")); // default
        } else {
            Serial.print(F(" + 4ms"));
        }
    } else {
        /*
         * Internal Calibrated RC Oscillator Clock
         */
        Serial.print(F("6 (+ 14 CK)"));
        switch (tStartUptimeBits) {
        case 0x10:
            Serial.print(F(" + 4ms"));
            break;
        case 0x20:
            Serial.print(F(" + 64ms")); // default
            break;
        default:
            break;
        }
    }

    uint8_t tHighFuseBits = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
    Serial.print(F("\n\nHighFuses="));
    Serial.printHex(tHighFuseBits);

    Serial.print(F("\nReset "));
    if (tHighFuseBits & ~FUSE_RSTDISBL) {
        Serial.print(F("not "));
    }
    Serial.print(F("disabled\n"));

    Serial.print(F("Serial programming "));
    if (tHighFuseBits & ~FUSE_SPIEN) {
        Serial.print(F("not "));
    }
    Serial.print(F("enabled\n"));

    Serial.print(F("Watchdog always on "));
    if (tHighFuseBits & ~FUSE_WDTON) {
        Serial.print(F("not "));
    }
    Serial.print(F("enabled\n"));

    Serial.print(F("Preserve EEPROM "));
    if (tHighFuseBits & ~FUSE_EESAVE) {
        Serial.print(F("not "));
    }
    Serial.print(F("enabled\n"));

    Serial.print(F("Brown-out="));
    uint8_t tBrownOutDetectionBits = tHighFuseBits & (~FUSE_BODLEVEL2 | ~FUSE_BODLEVEL1 | ~FUSE_BODLEVEL0 );
    switch (tBrownOutDetectionBits) {
    // 0-3 are reserved codes (for ATtiny)
    case 4:
        Serial.print(F("4.3V"));
        break;
    case 5:
        Serial.print(F("2.7V"));
        break;
    case 6:
        Serial.print(F("1.8V"));
        break;
    case 7:
        Serial.print(F("disabled"));
        break;
    default:
        break;
    }

    uint8_t tExtFuseBits = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
    Serial.print(F("\n\nExtFuses="));
    Serial.printHex(tExtFuseBits);
    Serial.print(F("\nSelf programming "));
    if (tExtFuseBits & ~FUSE_SELFPRGEN) {
        Serial.print(F("not "));
    }
    Serial.println(F("enabled\n"));
}

void printBODSFlagExistence() {
    Serial.print(F("BODS flag "));
    if (!isBODSFlagExistent()) {
        Serial.print(F("not "));
    }
    Serial.println(F("existent"));
}

#endif
