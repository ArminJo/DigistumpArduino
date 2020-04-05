DigistumpArduino
================
## Changed made in this fork:
- In `boards.txt` upload.maximum_size changed to values of [micronucleus version 2.4](https://github.com/ArminJo/micronucleus-firmware)
- In `platform.txt` added lto flag and added generating of disassembler and memory map files
- In `package_digistump_index.json`, changed compiler path to the one of Arduino 1.8.12 Version (7.3.0-atmel3.6.1-arduino5), since the original version does not support lto flag.

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