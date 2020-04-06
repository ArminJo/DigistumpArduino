DigistumpArduino
================
## Changed made in this fork:
- In `platform.txt` added lto flag to shring code size and added generating of disassembler and memory map files. Enabled compiler.cpp.extra_flags.
- In `boards.txt` changed upload.maximum_size to reflect values of [micronucleus version 2.4](https://github.com/ArminJo/micronucleus-firmware).
- In `package_digistump_index.json`, changed compiler path to the latest Arduino one (7.3.0-atmel3.6.1-arduino5), since the original version does not support the lto flag.
- Bumped version to 1.6.8

## How to update the bootloader to version 2.4
To update your old flash consuming bootloader you simply can run one of the window [scripts](https://github.com/ArminJo/micronucleus-firmware/tree/master/utils)
like e.g. the [Burn_upgrade-t85_default.cmd](https://github.com/ArminJo/micronucleus-firmware/blob/master/utils/Burn_upgrade-t85_default.cmd).

Files to add Digistump support (Digispark, Pro, DigiX) to Arduino 1.6.X (1.6.4+)

**These files are designed for install via the Arduino Boards Manager:** 

Board manager URL: https://raw.githubusercontent.com/ArminJo/DigistumpArduino/master/package_digistump_index.json

**Full Install Instructions:** 

Digispark: http://digistump.com/wiki/digispark/tutorials/connecting

Digispark Pro: http://digistump.com/wiki/digispark/tutorials/connectingpro

DigiX: http://digistump.com/wiki/digix/tutorials/software

**To compile:**

Micronucleus is the only executable in these packages that is pre-compiled:

Micronucleus: https://github.com/micronucleus/micronucleus/tree/80419704f68bf0783c5de63a6a4b9d89b45235c7
Dependencies: libusb and possibly lib32stdc on linux - (on ubuntu get it by issuing: apt-get install lib32stdc++6)