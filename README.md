# Improved version of Digistump avr core for Arduino
Available as Arduino Board Manager entry "Digistump AVR Boards" using the Board Manager URL: https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json

### [Version 1.6.8 ](https://github.com/ArminJo/DigistumpArduino/releases)

[![TestCompile](https://github.com/ArminJo/DigistumpArduino/workflows/TestCompile/badge.svg)](https://github.com/ArminJo/DigistumpArduino/actions)

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

## Oak board
The Arduino ESP8266 core available with https://arduino.esp8266.com/stable/package_esp8266com_index.json supports the *Digistump Oak* board now, better use that.

# Revision History

### Version 1.6.8
- The original Digistump version with `lto` and changed `upload.maximum_size` for [micronucleus bootloader 2.5](https://github.com/ArminJo/micronucleus-firmware).
- Added `LED_BUILTIN` definition in *pins_arduino.h*.
- Added `#define __FlashStringHelper fstr_t` in *tiny/Print.h*.
- Updated broken extensa links for `xtensa-lx106-elf-gcc` in *package_digistump_index.json*.
- Included most [pull requests](https://github.com/digistump/DigistumpArduino/pulls) done after the 1.6.7 release like `recipe.output.tmp_file={build.project_name}.hex` in *platform.txt* and EEPROM library.
- Added recipe to update booltloader by Arduino IDE.
## Requests for modifications / extensions
Please write me a PM including your motivation/problem if you need a modification or an extension.

#### If you find this library useful, please give it a star.