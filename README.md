# Improved version of Digistump avr core for Arduino
Available as Arduino Board Manager entry "Digistump AVR Boards" using the Board Manager URL: https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json

### [Version 1.7.3 ](https://github.com/ArminJo/DigistumpArduino/archive/master.zip) - work in progress

[![TestCompile](https://github.com/ArminJo/DigistumpArduino/workflows/TestCompile/badge.svg)](https://github.com/ArminJo/DigistumpArduino/actions)
[![Commits since latest](https://img.shields.io/github/commits-since/ArminJo/DigistumpArduino/latest)](https://github.com/ArminJo/DigistumpArduino/commits/master)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https://github.com/ArminJo/DigistumpArduino)](https://github.com/brentvollebregt/hit-counter)

Another **great core for ATtinies** with ongoing support is the [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) of Spence Konde, which **currently added micronucleus support**. Use the Board Manager URL: http://drazzy.com/package_drazzy.com_index.json for it.

## Reduced code size was enabled by the following changes:
- **To shrink generated code size by 5 to 15 percent** (depending on your code) the lto flag was added in `platform.txt`. To help finding code which consumes the flash, the generating of disassembler and memory map files are added. For Arduino IDE you will find these files in *C:\Users\<Name>\AppData\Local\Temp\arduino_build_<number>*.
- To **reflect the smaller bootloader size** of [micronucleus version 2.5](https://github.com/ArminJo/micronucleus-firmware) which allow 6586 instead of 6012 bytes (+11%) the *upload.maximum_size* entry was changed in `boards.txt`.
- Since the original gcc version does not support the lto flag, the compiler path was changed to the latest Arduino gcc (7.3.0-atmel3.6.1-arduino5) in the `package_digistump_index.json`.

## Other improvements
- Added `#define LED_BUILTIN ` in some *pins_arduino.h*.
- Added `#define __FlashStringHelper fstr_t` in *Print.h*.
- Updated broken extensa links for `xtensa-lx106-elf-gcc` in *package_digistump_index.json*.
- Included most [pull requests](https://github.com/digistump/DigistumpArduino/pulls) done after the 1.6.7 release like `recipe.output.tmp_file={build.project_name}.hex` in *platform.txt* and EEPROM library.
- Added recipe to update booltloader by Arduino IDE.
- Removed the non trusted post_install.bat since Arduino code states: `// Set main and bundled indexes as trusted` => all others are untrusted.
- Extended `DigisparkKeyboard` library with 22 keyboard layouts from [Teensyduino Core Library](https://github.com/PaulStoffregen/cores/blob/master/teensy/keylayouts.h), fixed bugs, **documented** and improved it. [Here](https://github.com/ArminJo/DigistumpArduino/blob/542aac12e56a1818af32b303c5709c655a12d98d/digistump-avr/libraries/DigisparkKeyboard/keylayouts.h#L80) it is documented how the mapping works, so now you can fix wrong mappings by your own (but please give me feedback to include the fix).
- Fixed and extended a growing number of examples.

![Digisparks](https://github.com/ArminJo/micronucleus-firmware/blob/master/pictures/Digisparks.jpg)

# Installation
To get all the benefits, just replace the old Digispark board URL **http://digistump.com/package_digistump_index.json** (e.g. in Arduino *File/Preferences*) by the new  **https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json** and install the **Digistump AVR Boards** version **1.7.2** or later.
![Boards Manager](https://github.com/ArminJo/DigistumpArduino/blob/master/pictures/Digistump1.6.8.jpg)

## Manual installation
1. Download this repo.
2. Create a directory *C:\Users<YourName>\AppData\Local\Arduino15\packages\digistump\hardware\avr\1.7.x* and extract the *digistump-avr-1.7.x.zip* to it.
3. Create a directory *C:\Users<YourName>\AppData\Local\Arduino15\packages\digistump\tools\micronucleus\2.5* and extract the *tools\micronucleus-cli-2.5-i686-mingw32.zip* to it.
4. Extract the file *package_digistump_index.json* to *C:\Users<YourName>\AppData\Local\Arduino15\*.

As reference you may look at your *C:\Users<YourName>\AppData\Local\Arduino\packages* directory to see how other packages are installed.

## Driver installation
For **Windows** you must install the **Digispark driver** before you can program the board.<br/>
if you have the *Digistump AVR Boards* already installed, then the driver is located in `%UserProfile%\AppData\Local\Arduino15\packages\digistump\tools\micronucleus\2.5\Digistump_Drivers`. Just execute the `Install_Digistump_Drivers.bat` file.<br/>
**Or** download it [here](https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip), open it and run `InstallDrivers.exe`.

## Update the bootloader to a new version
Different bootloader configurations are available [here](https://github.com/ArminJo/micronucleus-firmware#configuration-overview).<br/>
To **update** your old, flash consuming **bootloader**, you have 2 choices.
1. Use the new Digistump board manager URL (see above), choose a bootloader with *Tools > Micronucleus variant* and then burn it with *Tools > Burn Bootloader*.<br/>
![Burn Bootloader](https://github.com/ArminJo/DigistumpArduino/blob/master/pictures/Micronucleus_Burn_Bootloader.jpg)<br/>

2. Run one of the Windows [scripts](https://github.com/ArminJo/micronucleus-firmware/tree/master/utils)
like e.g. the [0_Upgrade-t85_recommended.cmd](https://github.com/ArminJo/micronucleus-firmware/tree/master/utils/0_Upgrade-t85_recommended.cmd). The internal mechanism is described [here](https://github.com/ArminJo/micronucleus-firmware/blob/master/firmware/upgrades/README.md).<br/>
You may also test the t85_agressive bootloader, [a configuration overwiew is available here](https://github.com/ArminJo/micronucleus-firmware#configuration-overview).
It works for my boards but the USB timing is not guaranteed as stable as in the other configurations.

## Fuse setting
The meaning of fuses can be seen with the [Engbedded Atmel AVR® Fuse Calculator](https://www.engbedded.com/fusecalc/).
Windows helper scripts for setting Fuses can be found [here](https://github.com/ArminJo/micronucleus-firmware/tree/master/utils).

The default fuses for a **Digispark** board are:<br/>
- ATtiny85 Lfuse: 0xE1 - (digispark default) PLL Clock + Startup 64 ms
- ATtiny85 Hfuse: 0xDD - External Reset pin enabled (Pin5 not usable as I/O) + BOD 2.7 V + Enable Serial Program and Data Downloading
- ATtiny85 Efuse: 0xFE - self programming enabled.

BOD enabled requires additional 20 µA in sleep state and therefore may be not desirable for low power battery applications. To disable BOD, use 0xDF as Hfuse.

The default fuses for a **Digispark Pro** board are:<br/>
- ATtiny167 Lfuse: 0xFF - External crystal osc. Frequency 8-16 MHz + Startup 65 ms
- ATtiny167 Hfuse: 0xDC - External Reset pin enabled + BOD 4.3Volt + Enable Serial Program and Data Downloading
- ATtiny167 Efuse: 0xFE - self programming enabled.

## Flash the bootloader to a bricked device
This can only be done by means of a [High Voltage programmer](https://github.com/ArminJo/ATtiny-HighVoltageProgrammer_FuseEraser).

# 16.5 MHz or 16 MHz?
You require **16.5 MHz only if your appliction uses the V-USB library**, i.e. if it acts as an USB devive like mouse, keyboard etc.<br/>
In all other cases it is recommended to use the standard CPU frequencies of 16, 8, 1 MHz.

# Power reducing
Information about reducing power consumption can be found [here](https://github.com/ArminJo/micronucleus-firmware#reducing-current-of-digispark-bords-for-low-power-applications) and [here](https://www.instructables.com/Reducing-Battery-Power-Consumption-for-Digispark-A/).
![Final power reduction](https://github.com/ArminJo/Arduino-OpenWindowAlarm/blob/master/pictures/Final-Version-Detail_annotated.jpg)

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
  USB- has a 1.5k pullup resistor to indicate a low-speed device.
  USB+ and USB- are each terminated on the host side with 15k to 25k pull-down resistors.
```

### ATtiny167 on Digispark pro
Digital Pin numbers in parenthesis are for ATTinyCore library

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

### MH-ET LIVE Tiny88 (16.0MHz) board
Digital Pin numbers in parenthesis are for ATTinyCore library

```
                       USB
                     +-\__/-+
              PA2  15|      |14  PB7
              PA3  16|      |13  PB5 SCK
           17 PA0  A6|      |12  PB4 MISO
           18 PA1  A7|      |11  PB3 MOSI
     (D17) 19 PC0  A0|      |10  PB2 OC1B/PWM SS
     (D18) 20 PC1  A1|      |9   PB1 OC1A/PWM
     (D19) 21 PC2  A2|      |8   PB0
     (D20) 22 PC3  A3|      |7   PD7 RX
SDA  (D21) 23 PC4  A4|      |6   PD6 TX
SCL  (D22) 24 PC5  A5|      |5   PD5
     (D23)    PC1  25|      |4   PD4
RESET         PC6 RST|      |3   PD3 INT1
LED           PD0   0|      |5V
USB-          PD1   1|      |GND
USB+  INT0    PD2   2|      |VIN
                     +------+
  USB+ and USB- are each connected to a 3.3 volt Zener to GND and with a 68 Ohm series resistor to the ATtiny pin.
  USB- has a 1k0 pullup resistor to indicate a low-speed device.
  USB+ and USB- are each terminated on the host side with 15k to 25k pull-down resistors.

  Pins not available: PB6 is CLOCK_IN, PC7 is 25

```
## Oak board
The Arduino ESP8266 core available with https://arduino.esp8266.com/stable/package_esp8266com_index.json supports the *Digistump Oak* board now, better use that.

# Revision History
### Version 1.7.3 - work in progress
- Improved bootloaders
- Added Attiny support to usbconfig.h.
- Added `Burn Bootloader Method` like in ATTinyCore.
- Removed digistump-sam from repo.
- ISR_NOBLOCK in millis interrupt only active for 16.5 MHz setting.
- Improved DigiKeboard.h and keylayouts.h.

### Version 1.7.2
- Updated examples and added warnings for CDC examples.
- Version to force update of all 1.7.1 changes.

### Version 1.7.1 - rolling version
- New micronucleus binaries for all platforms.
- Bootloaders with updated MCUSR handling.

### Version 1.7.0
- Support of the cheap Chinese MH-ET LIVE Tiny88(16.0MHz) board with ATTinyCore.
- Corrected wrong mouse buttons PR#2.
- Updated `boards.txt` to make use of menus. Therefore some board names changed like `digispark-tiny1` -> `digispark-tiny:clock=clock1` etc.
- Set `OSCCAL` to factory default instead of using a rule of thumb, which was not reliable.
- Added linker flag `-mrelax`. This reduces code size at least for ATtiny167.

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
- Enabled *compiler.cpp.extra_flags*.

## Requests for modifications / extensions
Please write me a PM including your motivation/problem if you need a modification or an extension.

#### If you find this library useful, please give it a star.