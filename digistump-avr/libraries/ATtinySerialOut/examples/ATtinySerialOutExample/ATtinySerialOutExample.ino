/*
 * ATtinySerialOutExample.cpp
 * Example for using ATtinySerialOut library
 *
 *  Copyright (C) 2015-2019  Armin Joachimsmeyer
 *  Email: armin.joachimsmeyer@gmail.com
 *
 *  This file is part of TinySerialOut https://github.com/ArminJo/ATtinySerialOut.
 *
 *  TinySerialOut is free software: you can redistribute it and/or modify
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

#include <Arduino.h> // needed for main()

#include "ATtinySerialOut.h"

#include <avr/pgmspace.h> // needed for PSTR()

#define VERSION_EXAMPLE "1.0"

void setup(void) {
    initTXPin();

    writeString(F("START " __FILE__ "\nVersion " VERSION_EXAMPLE " from " __DATE__ "\n"));

    uint8_t tOSCCAL = OSCCAL;

    writeString("Value of OSCCAL is:");
    writeUnsignedByteHexWithPrefix(tOSCCAL);
}

void loop(void) {
    static uint8_t tIndex = 0;
    /*
     * Example of 3 Byte output. View in combined ASSCI / HEX View in HTerm (http://www.der-hammer.info/terminal/)
     * Otherwise use writeUnsignedByteHexWithoutPrefix or writeUnsignedByteHex
     */
    write1Start8Data1StopNoParityWithCliSei('I');
    writeBinary(tIndex);                    // 1 Byte binary output
    writeUnsignedByte(tIndex);              // 1-3 Byte ASCII output
    writeUnsignedByteHexWithPrefix(tIndex); // 4 Byte output
    writeUnsignedByteHex(tIndex);           // 2 Byte output
    write1Start8Data1StopNoParityWithCliSei('\n');
    /*
     * Serial.print usage example
     */
    Serial.print("I=");
    Serial.print((char) tIndex);
    Serial.print(" | ");
    Serial.print(tIndex);
    Serial.print(" | ");
    Serial.print(tIndex, HEX);
    Serial.print(" | ");
    Serial.printHex(tIndex);
    Serial.print(" | ");
    Serial.println(tIndex);

    tIndex++;
    delay(100);
}
