# [Attiny Serial Out](https://github.com/ArminJo/ATtinySerialOut)
### [Version 1.1.0](https://github.com/ArminJo/ATtinySerialOut/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Installation instructions](https://www.ardu-badge.com/badge/ATtinySerialOut.svg?)](https://www.ardu-badge.com/ATtinySerialOut)
[![Commits since latest](https://img.shields.io/github/commits-since/ArminJo/ATtinySerialOut/latest)](https://github.com/ArminJo/ATtinySerialOut/commits/master)
[![Build Status](https://github.com/ArminJo/ATtinySerialOut/workflows/LibraryBuild/badge.svg)](https://github.com/ArminJo/ATtinySerialOut/actions)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https%3A%2F%2Fgithub.com%2FArminJo%2FATtinySerialOut)](https://github.com/brentvollebregt/hit-counter)

Minimal bit-bang send serial

115200 baud for 1/8/16 MHz ATtiny clock.
### Perfect for debugging purposes.
### Provides Serial.print / println functions for easy software porting. 
### Code size is only 76 Bytes@38400 baud or 196 Bytes@115200 baud (including first call)
### Default TX pin is PB2 on a ATtiny85.
To change the output pin, just modify the line "#define TX_PIN ..." in `TinySerialOut.h`. You will find the file in the Arduino IDE under *Sketch/Show Sketch Folder (Ctrl+K)* and then in the `libraries/TinySerialOut/src` directory. Or define global symbol with `-DTX_PIN PB1` which is not yet possible in Arduino IDE:-(.<br/>
## Consider to use [Sloeber](http://eclipse.baeyens.it/stable.php?OS=Windows) as IDE<br/>
If you are using Sloeber as your IDE, you can easily define global symbols at *Properties/Arduino/CompileOptions*.<br/>
![Sloeber settings](https://github.com/ArminJo/ServoEasing/blob/master/pictures/SloeberDefineSymbols.png)

## Serial functions provided (linefeed is \n instead of \r\n):
```   
    void print(const __FlashStringHelper * aStringPtr);
    void print(const char* aStringPtr);
    void print(char aChar);
    void print(uint8_t aByte, uint8_t aBase = 10);
    void print(int16_t, uint8_t aBase = 10);
    void print(uint16_t aInteger, uint8_t aBase = 10);
    void print(uint32_t aLong, uint8_t aBase = 10);
    void print(uint32_t aLong, uint8_t aBase = 10);
    void print(double aFloat, uint8_t aDigits = 2);

    void printHex(uint8_t aByte); // with 0x prefix

    void println(const __FlashStringHelper * aStringPtr);
    void println(char aChar);
    void println(uint8_t aByte, uint8_t aBase = 10);
    void println(int16_t aInteger, uint8_t aBase = 10);
    void println(uint16_t aInteger, uint8_t aBase = 10);
    void println(int32_t aLong, uint8_t aBase = 10);
    void println(uint32_t aLong, uint8_t aBase = 10);
    void println(double aFloat, uint8_t aDigits = 2);

    void println(void);
```
## [OpenWindowAlarm example](https://raw.githubusercontent.com/ArminJo/ATtinySerialOut/master/examples/OpenWindowAlarm/OpenWindowAlarm.ino)
This example issues an alarm if the chip sensor detect a falling teperarure and is fully documented [here](https://github.com/ArminJo/Arduino-OpenWindowAlarm)

# Revision History
### Version 1.1.0 - 5/2020
- Changed `int` to `int16_t` and `long` to `int32_t`.
- Use `utoa()` and `ultoa()` for `uint16_t` and `uint32_t`.

### Version 1.0.5 - 3/2020
- Added function `writeCRLF()`

### Version 1.0.4 - 1/2020
- Symbol TINY_SERIAL_INHERIT_FROM_PRINT - if defined, you can use this class as a replacement for standard Serial as a print class.
- Improved all ...Hex() functions.
- Define FlashStringHelper for digispark.
- Changed label `loop` to `txloop` in `write1Start8Data1StopNoParity()` for 38400 baud.

### Version 1.0.3
- OpenWindowAlarm example updated.

### Version 1.0.2
- `printHex()` now using capital letters.
- Improved OpenWindowAlarm example.

### Version 1.0.1
- Renamed example to be consistent.

### Version 1.0.0
Initial Arduino library version.

### Remark
C version of serial code is included for better understanding, but assembler version is used. This is because for the C code the timing depends on compiler optimisation switches. You should get the right timing if you compile the C code it with Arduino standard settings or:
```
avr-g++ -I"C:\arduino\hardware\arduino\avr\cores\arduino" -I"C:\arduino\hardware\arduino\avr\variants\standard" -c -g -w -Os -ffunction-sections -fdata-sections -mmcu=attiny85 -DF_CPU=1000000UL -MMD -o "TinySerialOut.o" "TinySerialOut.cpp"
```

#### If you find this library useful, please give it a star.
