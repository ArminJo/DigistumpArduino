# Improved version of Digistump avr core for Arduino
Available as Arduino Board Manager entry "Digistump AVR Boards" using the Board Manager URL: https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json

### [Version 1.6.8 ](https://github.com/ArminJo/DigistumpArduino/releases)

[![TestCompile](https://github.com/ArminJo/DigistumpArduino/workflows/TestCompile/badge.svg)](https://github.com/ArminJo/DigistumpArduino/actions)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https://github.com/ArminJo/DigistumpArduino)](https://github.com/brentvollebregt/hit-counter)

## Reduced code size was enabled by the following changes:
- **To shrink generated code size by 5 to 15 percent** (depending on your code) the lto flag was added in `platform.txt`. To help finding code which consumes the flash, the generating of disassembler and memory map files are added. For Arduino IDE you will find these files in *C:\Users\<Name>\AppData\Local\Temp\arduino_build_<number>*.
- To **reflect the smaller bootloader size** of [micronucleus version 2.5](https://github.com/ArminJo/micronucleus-firmware) which allow 6586 instead of 6012 bytes (+11%) the *upload.maximum_size* entry was changed in `boards.txt`.
- Since the original gcc version does not support the lto flag, the compiler path was changed to the latest Arduino gcc (7.3.0-atmel3.6.1-arduino5) in the `package_digistump_index.json`.
- Enabled *compiler.cpp.extra_flags*.

## Other improvements
- Added `#define LED_BUILTIN ` in some *pins_arduino.h*.
- Added `#define __FlashStringHelper fstr_t` in *Print.h*.
- Updated broken extensa links for `xtensa-lx106-elf-gcc` in *package_digistump_index.json*.
- Included most [pull requests](https://github.com/digistump/DigistumpArduino/pulls) done after the 1.6.7 release like `recipe.output.tmp_file={build.project_name}.hex` in *platform.txt* and EEPROM library.
- Added recipe to update booltloader by Arduino IDE.
- Removed the non trusted post_install.bat since Arduino code states: `// Set main and bundled indexes as trusted` => all others are untrusted.
- Extended `DigisparkKeyboard` library with 22 keyboard layouts from [Teensyduino Core Library](https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h), fixed bugs, **documented** and improved it. [Here](https://github.com/ArminJo/DigistumpArduino/blob/542aac12e56a1818af32b303c5709c655a12d98d/digistump-avr/libraries/DigisparkKeyboard/keylayouts.h#L80) it is documented how the mapping works, so now you can fix wrong mappings by your own (but please give me feedback to include the fix).

# Installation
To get all the benefits, just replace the old Digispark board URL **http://digistump.com/package_digistump_index.json** (e.g. in Arduino *File/Preferences*) by the new  **https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json** and install the **Digistump AVR Boards** version **1.6.8**.
![Boards Manager](https://github.com/ArminJo/DigistumpArduino/blob/master/pictures/Digistump1.6.8.jpg)

## Driver installation
For Windows you must install the **Digispark driver** before you can program the board.<br/>
if you have the *Diigistump AVR Boards* already installed, then the driver is located in `%UserProfile%\AppData\Local\Arduino15\packages\digistump\tools\micronucleus\2.0a4`. Just execute the `Install_Digistump_Drivers.bat` file.<br/>
**Or** download it [here](https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip), open it and run `InstallDrivers.exe`. 

## Update the bootloader
To **update** your old flash consuming **bootloader**, open the Arduino IDE, select *Tools/Programmer: "Micronucleus"* and then run *Tools/Burn Bootloder*.<br/>
![Burn Bootloader](https://github.com/ArminJo/DigistumpArduino/blob/master/pictures/Micronucleus_Burn_Bootloader.jpg)<br/>
The bootloader is the recommended configuration [`entry_on_power_on_no_pullup_fast_exit_on_no_USB`](https://github.com/ArminJo/micronucleus-firmware#recommended-configuration).<br/>
**Or** use one of the window [scripts](https://github.com/ArminJo/micronucleus-firmware/tree/master/utils)
like e.g. [Burn_upgrade-t85_default.cmd](https://github.com/ArminJo/micronucleus-firmware/tree/master/utils/Burn_upgrade-t85_default.cmd).<br/>
You may also test the [t85_agressive bootloader](firmware/configuration#overview).
It works for my boards but the USB timing is not guaranteed as stable as in the other configurations.
Do not forget to change the `upload.maximum_size` entry in *%localappdata%\Arduino15\packages\digistump\hardware\avr\1.6.8\boards.txt* to **6778**.<br/>

# Pin layout
### ATtiny85 on Digispark

```
                       +-\/-+
 RESET/ADC0 (D5) PB5  1|    |8  VCC
  USB- ADC3 (D3) PB3  2|    |7  PB2 (D2) INT0/ADC1 - default TX Debug output for ATtinySerialOut
  USB+ ADC2 (D4) PB4  3|    |6  PB1 (D1) MISO/DO/AIN1/OC0B/OC1A/PCINT1 - (Digispark) LED
                 GND  4|    |5  PB0 (D0) OC0A/AIN0
                       +----+
  USB+ and USB- are each connected to a 3.3 volt Zener to GND and with a 68 Ohm series resistor to the ATtiny pin.
  On boards with a micro USB connector, the series resistor is 22 Ohm instead of 68 Ohm. 
  USB- has a 1k pullup resistor to indicate a low-speed device (standard says 1k5).                  
  USB+ and USB- are each terminated on the host side with 15k to 25k pull-down resistors.
```

### ATtiny167 on Digispark pro
Digital Pin numbers in braces are for ATTinyCore library

```
                  +-\/-+
RX   6 (D0) PA0  1|    |20  PB0 (D8)  0 OC1AU
TX   7 (D1) PA1  2|    |19  PB1 (D9)  1 OC1BU - (Digispark) LED
     8 (D2) PA2  3|    |18  PB2 (D10) 2 OC1AV
INT1 9 (D3) PA3  4|    |17  PB3 (D11) 4 OC1BV USB-
           AVCC  5|    |16  GND
           AGND  6|    |15  VCC
    10 (D4) PA4  7|    |14  PB4 (D12)   XTAL1
    11 (D5) PA5  8|    |13  PB5 (D13)   XTAL2
    12 (D6) PA6  9|    |12  PB6 (D14) 3 INT0  USB+
     5 (D7) PA7 10|    |11  PB7 (D15)   RESET
                  +----+
  USB+ and USB- are each connected to a 3.3 volt Zener to GND and with a 51 Ohm series resistor to the ATtiny pin.
  USB- has a 1k5 pullup resistor to indicate a low-speed device.
  USB+ and USB- are each terminated on the host side with 15k to 25k pull-down resistors.

```

## Oak board
The Arduino ESP8266 core available with https://arduino.esp8266.com/stable/package_esp8266com_index.json supports the *Digistump Oak* board now, better use that.

# Revision History

### Version 1.6.8
- The original Digistump version with `lto` and changed `upload.maximum_size` for [micronucleus bootloader 2.5](https://github.com/ArminJo/micronucleus-firmware).
- Added `LED_BUILTIN` definition in *pins_arduino.h*.
- Added `#define __FlashStringHelper fstr_t` in *tiny/Print.h*.
- Updated broken extensa links for `xtensa-lx106-elf-gcc` in *package_digistump_index.json*.
- Included most [pull requests](https://github.com/digistump/DigistumpArduino/pulls) done after the 1.6.7 release like `recipe.output.tmp_file={build.project_name}.hex` in *platform.txt* and EEPROM library.
- Added recipe to update bootloader by Arduino IDE.
- Changed message for BIN redefined in *Print.h* and it can be suppressed by commenting out #define SUPPRESS_BIN_WARNING in line 39 in *Print.h*.
- Commented out the annoying `#define true 0x1` and `#define false 0x0` in *wiring.h*.
- Removed unnecessary files  like .gitignore.
- Added `#define TwoWire USI_TWI` in *Wire.h*.
- Changed` #include <avr/delay.h>` to `#include <util/delay.h>` in 3 files.
- Included [Multi-Keyboard Layout MOD](https://github.com/rsrdesarrollo/DigistumpArduino).
- Redefining BIN to 2 for print. BIN can not longer be used as bit position (7) for the x5 ADC "Bipolar Input Mode".
- Enabled all warnings at compile time and removed compiler warnings in tiny core.
- Modified definition for yield() in *WProgram.h* to avoid error "undefined reference to `yield()'".

## Requests for modifications / extensions
Please write me a PM including your motivation/problem if you need a modification or an extension.

#### If you find this library useful, please give it a star.