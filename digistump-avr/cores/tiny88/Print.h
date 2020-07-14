/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 20-11-2010 by B.Cook ...

    http://arduiniana.org/libraries/flash/
    Printable support thanks to Mikal Hart
*/

#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h> // for size_t

#include "WString.h"

#define DEC 10
#define HEX 16
#define OCT 8
#ifdef BIN
#define ABIN BIN
//One of the ATtiny84 registers has a bit called BIN, so rename it to avoid compiler warnings.
#undef BIN
#endif
#define BIN 2

#define ARDUINO_CORE_PRINTABLE_SUPPORT

#define FLASHSTRING_SUPPORT

class Print;

/* Printable...*/

class _Printable
{
public:
  virtual void print(Print &stream) const = 0;
};

/* ...Printable */

typedef struct
{
  char c;
}
fstr_t;


class Print
{
  private:
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);
  protected:
    void setWriteError(int err = 1) { write_error = err; }
  public:
    Print() : write_error(0) {}

    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }

    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) { return write((const uint8_t *)str, strlen(str)); }
    virtual size_t write(const uint8_t *buffer, size_t size);

    size_t print(fstr_t*);
    size_t print(const String &);
    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(long long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(double, int = 2);

    size_t println(fstr_t*);
    size_t println(const String &s);
    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(long long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(double, int = 2);
    size_t println(void);

    int16_t printf(const char *ifsh, ...);

    #ifdef FLASHSTRING_SUPPORT
    size_t print(const __FlashStringHelper *ifsh);
    size_t println(const __FlashStringHelper *ifsh);
    int16_t printf(const __FlashStringHelper *ifsh, ...);
    #endif
};

#endif
