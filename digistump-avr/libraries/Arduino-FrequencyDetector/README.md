# [Frequency Detector](https://github.com/ArminJo/Arduino-FrequencyDetector) Library for Arduino and ATtinys
Available as Arduino library "FrequencyDetector"

### [Version 1.1.1](https://github.com/ArminJo/Arduino-FrequencyDetector/releases)

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Commits since latest](https://img.shields.io/github/commits-since/ArminJo/Arduino-FrequencyDetector/latest)](https://github.com/ArminJo/Arduino-FrequencyDetector/commits/master)
[![Build Status](https://github.com/ArminJo/Arduino-FrequencyDetector/workflows/LibraryBuildWithAction/badge.svg)](https://github.com/ArminJo/Arduino-FrequencyDetector/actions)
[![Build Status](https://github.com/ArminJo/Arduino-FrequencyDetector/workflows/LibraryBuildWithScript/badge.svg)](https://github.com/ArminJo/Arduino-FrequencyDetector/actions)
[![Build Status](https://github.com/ArminJo/Arduino-FrequencyDetector/workflows/LibraryBuildWithSteps/badge.svg)](https://github.com/ArminJo/Arduino-FrequencyDetector/actions)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https%3A%2F%2Fgithub.com%2FArminJo%2FArduino-FrequencyDetector)](https://github.com/brentvollebregt/hit-counter)

YouTube video of whistle switch example in action.

[![Demonstration of 3 whistle switches in one room](https://i.ytimg.com/vi/_e2mElB8zJs/hqdefault.jpg)](https://www.youtube.com/watch?v=_e2mElB8zJs)

# Internal operation
This library analyzes a (microphone) signal and outputs the detected frequency. It simply counts zero crossings and **it does do not use FFT**.
The ADC sample data is **not** stored in RAM, only the period lengths (between triggers) are stored in the `PeriodLength[]` array,
which is a byte array and has the size of `NUMBER_OF_SAMPLES / 8`.<br/>
The **timer 0 interrupt**, which counts the milliseconds, **is disabled during reading** and enabled afterwards!
The value of millis() is adjusted after reading.<br/>
The alternative to disabling the interrupt is getting partially invalid results!

### `readSignal()` is the ADC read routine, which reads 1024/512 samples and computes the following values:
  1. Frequency of signal `uint16_t FrequencyRaw;`
  2. MaxValue - MinValue `uint16_t SignalDelta;`
  3. Average = (SumOfSampleValues / NumberOfSamples) `uint16_t AverageLevel;`
  4. The length of each period (between 2 trigger conditions) in the `PeriodLength[]` array.

### `doPlausi()` checks if the signal in the `PeriodLength[]` array is not noisy and valid. It uses the following plausibility rules:
  1. A trigger must be detected in first and last 1/8 of samples.
  2. Only 1/8 of the samples are allowed to be greater than 1.5 or less than 0.75 of the average period.
  In case of failure, the value of `FrequencyRaw` is overwritten with the error code.

### `computeDirectAndFilteredMatch()` waits for n matches within a given frequency range (FrequencyMatchLow - FrequencyMatchHigh)
and also low pass filters the result for smooth transitions between the 3 match states (lower, match, greater). It computes the following values:
  1. Low pass filtered frequency of signal `uint16_t FrequencyFiltered;`
  2. Match result `MatchStateEnum FrequencyMatchDirect;`
  3. Low pass filtered match result `MatchStateEnum FrequencyMatchFiltered`

# SimpleFrequencyDetector example
This example reads analog signal e.g. from MAX9814 Module at A1 and computes the frequency.
If frequency is in the range of 1400 to 1700 Hz, the Arduino built in LED will light up.
It prints the detected frequency as well as plausibility errors.
For frequency below 400 Hz it might be good to change `PRESCALE_VALUE_DEFAULT` to `PRESCALE128`.

SimpleFrequencyDetector on breadboard with MAX9814 Module
![SimpleFrequencyDetector on breadboard with MAX9814 Module](https://github.com/ArminJo/Arduino-FrequencyDetector/blob/master/extras/SimpleFrequencyDetector_MAX9814.jpg)
YouTube Demonstration of SimpleFrequencyDetector with MAX9812 Module

[![Demonstration of SimpleFrequencyDetector](https://img.youtube.com/vi/tsxfSx0iY5s/0.jpg)](https://www.youtube.com/watch?v=tsxfSx0iY5s)

# WhistleSwitch example
The WhistleSwitch example analyzes a microphone signal (I use a MAX9814 module from Adafruit) and toggles an output pin, if the main frequency is for a specified duration in a specified range.
It works as a frequency detector for a whistle pitch which operates a mains relay. By using different pitches it is possible to control multiple relays in a single room.<br/>
If the pitch is lower than the specified frequency, the feedback LED blinks slowly, if the pitch is higher it blinks fast.<br/>
If the (low pass filtered) match from the FrequencyDetector library holds for `MATCH_TO_LONG_MILLIS` (1 second) after switching output,
the output switches again, to go back to the former state.
This can be useful if a machine generated signal (e.g. from a vacuum cleaner) matches the range.<br/>
**This example is mainly created to run on an ATtiny85 at 1 MHz, but will work also on a plain Arduino.**

### Arduino Plotter output of WhistleSwitch in action
Above you see the `FrequencyRaw` I whistled with all the dropouts and the `FrequencyFiltered` without dropouts but with a slight delay if the `FrequencyRaw` changes.<br/>
The WhistleSwitch example uses the `FrequencyMatchFiltered` value, to decide if a match happens. At 80 and 140 you see 2 short and at 300 you see a long valid match.
![Arduino Plotter output of whistle switch in action](https://github.com/ArminJo/Arduino-FrequencyDetector/blob/master/extras/WhistleSwitchPlotterOutput.png)

## PREDEFINED RANGES
After power up or reset, the feedback LED echoes the range number. Range number 10 indicates an individual range, programmed by advanced selecting.
The timeout state is signaled by short LED pulses after the range number feedback (no short pulse -> no timeout enabled).

the following pitch ranges are predefined for easy selection:
1.   1700 - 2050 Hz  -> 350 Hz A6-C6
2.   1500 - 1680 Hz  -> 180 Hz FS6-GS6
3.   1300 - 1480 Hz  -> 180 Hz E6-FS6
4.   1150 - 1280 Hz  -> 130 Hz D6-DS6
5.   1000 - 1130 Hz  -> 130 Hz C6-CS6
6.    900 -  990 Hz  ->  90 Hz A5-B5

7.   1550 - 1900 Hz  -> 350 Hz G6-AS6
8.   1250 - 1530 Hz  -> 380 Hz DS6-G6
9.   1000 - 1230 Hz  -> 230 Hz C6-DS6

10.  Dummy range, if chosen, disables relay on timeout handling.
11.  Dummy range, if chosen, sets relay on timeout to `TIMEOUT_RELAY_ON_SIGNAL_MINUTES_1` (2 hours).
12.  Dummy range, if chosen, sets relay on timeout to `TIMEOUT_RELAY_ON_SIGNAL_MINUTES_2` (4 hours).
13.  Dummy range, if chosen, sets relay on timeout to `TIMEOUT_RELAY_ON_SIGNAL_MINUTES_3` (8 hours).

## SELECTING the RANGE
Selecting is started by a long press of the button.
After `BUTTON_PUSH_ENTER_PROGRAM_SIMPLE_MILLIS` (1.5 seconds), the feedback LED blinks once for signaling simple programming mode.
After `BUTTON_PUSH_ENTER_PROGRAM_ADVANCED_MILLIS` (4 seconds), the feedback LED blinks twice for signaling advanced programming mode.
After releasing the button, the selected programming mode is entered.

### SIMPLE PROGRAMMING MODE
Press the button once for range 1, twice for range 2 etc. Each button press is echoed by the feedback LED.
Waiting for `PROGRAM_MODE_SIMPLE_END_DETECT_MILLIS` (1.5 seconds) ends the programming mode
and the feedback LED echoes the number of button presses recognized.
The duration of signal match to toggle the relay is fixed at `MATCH_MILLIS_NEEDED_DEFAULT` (1.2 seconds).

### ADVANCED PROGRAMMING MODE
Whistle the pitch you want to detect, then press the button again.
While you press the button, the pitch range is measured. i.e. the minimum and maximum of the pitch you are whistling is stored.

If you press the button again before the `PROGRAM_MODE_ADVANCED_END_DETECT_MILLIS` (3 seconds) timeout
the duration of this second press is taken as the required duration for the signal match to toggle the relay.
Otherwise the `MATCH_MILLIS_NEEDED_DEFAULT` (1.2 seconds) are taken.
After timeout of `PROGRAM_MODE_TIMEOUT_MILLIS` (5 seconds) the advanced programming mode is ended
and the effective duration is echoed by the feedback LED.

## TIMEOUT
After a timeout of `TIMEOUT_RELAY_ON_SIGNAL_MINUTES`_(1 to 3) (2, 4 or 8 hours) the relay goes OFF for 1 second.
In the next `TIMEOUT_RELAY_SIGNAL_TO_OFF_MINUTES` (3) minutes you must then press the button or whistle the pitch to cancel the timeout, otherwise the relay will switch OFF afterwards.
Cancellation of timeout is acknowledged by the LED blinking 5 times for 1 second on and off. Timeout can be switched on by selecting the dummy ranges 11 to 13 and off by selecting the dummy range 10.
The setting is stored in EEPROM. Default is `TIMEOUT_RELAY_ON_SIGNAL_MINUTES_3` (8 hours).

## RESET
A reset can be performed by power off/on or by pressing the button two times, each time shorter than `RESET_ENTER_BUTTON_PUSH_MILLIS` (0.12 seconds) within a `RESET_WAIT_TIMEOUT_MILLIS` (0.3 seconds) interval.

## Using a Digispark board
If you enable `INFO`, the program will be too big for the Digispark board in the Arduino IDE, since it is checked against the old (pre V2) bootloader size.<br/>
If you want `INFO` on the ATtiny85, first use the ATtiny25/45/85 at 1MHz from the ATTinyCore in the Arduino Board manager, since this leads to smaller code size - 6996/5184 compared to 6152/5914 with `INFO` enabled/disabled.<br/>
Second, upgrade the micronucleus bootloader on the digispark board with *https://github.com/ArminJo/micronucleus-firmware/tree/master/firmware/upgrades/upgrade-t85_default.hex*.<br/>
Load the new bootloader with `%UserProfile%\AppData\Local\Arduino15\packages\digistump\tools\micronucleus\2.0a4\launcher.exe -cdigispark -Uflash:w:upgrade-t85_default.hex:i`, this gives additional 500 bytes more program space.<br/>
Then create the hex file by pressing the upload button in the Arduino IDE.
The upload will fail, but in one of the last lines in the console you will find the filename of the hex file e.g. *C:\\Users\\<username>\\AppData\\Local\\Temp\\arduino_build_**12345**\\WhistleSwitch.ino.hex*.<br/>
You can then upload the hex program file manually with e.g.:
`%UserProfile%\AppData\Local\Arduino15\packages\digistump\tools\micronucleus\2.0a4\launcher.exe -cdigispark -Uflash:w:%UserProfile%\\AppData\\Local\\Temp\\arduino_build_12345\\WhistleSwitch.ino.hex:i`

# SCHEMATIC for external components of FrequencyDetector / WhistleSwitch
```
Discrete microphone amplifier with LM308

         + 5V                             _____                   o--O PIN REF
         |                             o-|_____|--o               |
         _                             |   1M     |               _
        | |                            |          |              | |
        | | 2k2                        |___|\     |              | | 1M
        |_|                            |  2| \____|              |_|
         |    ____             ____    |   | /6   |   ____   | |  |
         o---|____|-----o-----|____|---o---|/     o--|____|--| |--o--O PIN A1
         |     2k2      |      10k     |  3             10k  | |  |
        ---            |O MICROPHONE   _    LM308        10-100nF _
        --- 1 uF        |             | |                        | |
         |              |             | | 10k                    | | 1M
        ___            ___            |_|                        |_|
                                       |                          |
                                       |                          |
                                      ---                        ___
                                      ---  100 nF
                                       |
                                      ___


Connection of Adafruit microphone modules:

         + 5V / 3.3V        o--O PIN REF
         |                  |
         |                  _
         |                 | |
MAX4466 / 9814 MICROPHONE  | | 1M
    AMPLIFIER / MODULE     |_|
         |                  |
        |O -------||--------o--O PIN A1
         |       10nF       |
         |                  _
         |                 | |
         |                 | | 1M
        ___                |_|
                            |
                            |
                           ___
```

# Revision History
### Version 1.1.1
- Moved libraries for WhistleSwitch example.

### Version 1.1.0
- Corrected formula for compensating millis().
- New field PeriodOfOneReadingMillis.
- Now accept dropout values in milliseconds.
- New functions `printLegendForArduinoPlotter()` and `printDataForArduinoPlotter()`.

# CI
Since Travis CI is unreliable and slow, the library examples are now tested with GitHub Actions for the following boards:

- arduino:avr:uno
- digistump:avr:digispark-tiny1
- ATTinyCore:avr:attinyx5:chip=85,clock=1internal

#### If you find this library useful, please give it a star.
