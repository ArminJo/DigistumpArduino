/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2013 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef KEYLAYOUTS_H__
#define KEYLAYOUTS_H__

#include <stdint.h>
#include <avr/pgmspace.h>

#ifdef __cplusplus
extern "C" {
#endif

//#define LAYOUT_US_ENGLISH
//#define LAYOUT_CANADIAN_FRENCH
//#define LAYOUT_CANADIAN_MULTILINGUAL
//#define LAYOUT_DANISH
//#define LAYOUT_FINNISH
//#define LAYOUT_FRENCH
//#define LAYOUT_FRENCH_BELGIAN
//#define LAYOUT_FRENCH_SWISS
//#define LAYOUT_GERMAN
//#define LAYOUT_GERMAN_MAC
//#define LAYOUT_GERMAN_SWISS
//#define LAYOUT_ICELANDIC
//#define LAYOUT_IRISH
//#define LAYOUT_ITALIAN
//#define LAYOUT_NORWEGIAN
//#define LAYOUT_PORTUGUESE
//#define LAYOUT_PORTUGUESE_BRAZILIAN
//#define LAYOUT_SPANISH
//#define LAYOUT_SPANISH_LATIN_AMERICA
//#define LAYOUT_SWEDISH
//#define LAYOUT_TURKISH
//#define LAYOUT_UNITED_KINGDOM	
//#define LAYOUT_US_INTERNATIONAL

#define LAYOUT_UNSPECIFIED

//http://en.wikipedia.org/wiki/Keyboard_layout
// @formatter:off
/*
 * Usage Page for key codes to be used in implementing a USB keyboard.
 * https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
 * Chapter 10 "Keyboard/Keypad Page (0x07)"
 *
 * The code the keyboard must send when a key is pressed, e.g. 0x04 for Keyboard a and A.
 * This code is independent of the keyboard layout and is translated by the operating system
 * to the right character by using the OS Keyboard layout information.
 * Therefore we must convert our regional code to this independent one and the host converts it back.
 *
 * The rule is: look at you keyboard which key position and shift modifier you have for this character.
 * Then look at the US keyboard https://en.wikipedia.org/wiki/Keyboard_layout#/media/File:Qwerty.svg
 * which character you generate by pressing your key. This is the value you must use for the lookup table.
 * e.g. On the German keyboard the Y is in the lower row left. On the US keyboard you find the Z at this position.
 * So the entry is:
 * #define ASCII_79        KEY_Z
 *
 * On 105-ISO keyboards, there is 1 additional key bottom left with code KEY_NON_US_BS (BS->Backslash)
 * and the top right key KEY_BACKSLASH (| and \) is moved to the key left of return (# and ~).
 * Here you can see a 105-ISO keyboard, but do not use this layout for key discovery, since it is an UK and no US layout!
 * https://en.wikipedia.org/wiki/Keyboard_layout#/media/File:ISO_keyboard_(105)_QWERTY_UK.svg
 */
/*
 * USB Keyboard scancodes from Keyboard/Keypad Page (0x07)
 */
#define MODIFIERKEY_CTRL        ( 0x01 | 0xE000 )
#define MODIFIERKEY_SHIFT       ( 0x02 | 0xE000 )
#define MODIFIERKEY_ALT         ( 0x04 | 0xE000 )
#define MODIFIERKEY_GUI         ( 0x08 | 0xE000 )
#define MODIFIERKEY_LEFT_CTRL   ( 0x01 | 0xE000 )
#define MODIFIERKEY_LEFT_SHIFT  ( 0x02 | 0xE000 )
#define MODIFIERKEY_LEFT_ALT    ( 0x04 | 0xE000 )
#define MODIFIERKEY_LEFT_GUI    ( 0x08 | 0xE000 )
#define MODIFIERKEY_RIGHT_CTRL  ( 0x10 | 0xE000 )
#define MODIFIERKEY_RIGHT_SHIFT ( 0x20 | 0xE000 )
#define MODIFIERKEY_RIGHT_ALT   ( 0x40 | 0xE000 )
#define MODIFIERKEY_RIGHT_GUI   ( 0x80 | 0xE000 )

#define KEY_SYSTEM_POWER_DOWN   ( 0x81 | 0xE200 )
#define KEY_SYSTEM_SLEEP        ( 0x82 | 0xE200 )
#define KEY_SYSTEM_WAKE_UP      ( 0x83 | 0xE200 )

#define KEY_MEDIA_PLAY          ( 0xB0 | 0xE400 )
#define KEY_MEDIA_PAUSE         ( 0xB1 | 0xE400 )
#define KEY_MEDIA_RECORD        ( 0xB2 | 0xE400 )
#define KEY_MEDIA_FAST_FORWARD  ( 0xB3 | 0xE400 )
#define KEY_MEDIA_REWIND        ( 0xB4 | 0xE400 )
#define KEY_MEDIA_NEXT_TRACK    ( 0xB5 | 0xE400 )
#define KEY_MEDIA_PREV_TRACK    ( 0xB6 | 0xE400 )
#define KEY_MEDIA_STOP          ( 0xB7 | 0xE400 )
#define KEY_MEDIA_EJECT         ( 0xB8 | 0xE400 )
#define KEY_MEDIA_RANDOM_PLAY   ( 0xB9 | 0xE400 )
#define KEY_MEDIA_PLAY_PAUSE    ( 0xCD | 0xE400 )
#define KEY_MEDIA_PLAY_SKIP     ( 0xCE | 0xE400 )
#define KEY_MEDIA_MUTE          ( 0xE2 | 0xE400 )
#define KEY_MEDIA_VOLUME_INC    ( 0xE9 | 0xE400 )
#define KEY_MEDIA_VOLUME_DEC    ( 0xEA | 0xE400 )

#define KEY_NOKEY             0x00     // Reserved (no event indicated)
#define KEY_ERR_ROLLOVER      0x01     // Keyboard ErrorRollOver
#define KEY_POSTFAIL          0x02     // Keyboard POSTFail
#define KEY_ERR_UNDEFINED     0x03     // Keyboard ErrorUndefined
#define KEY_A                   ( 0x04 | 0xF000 )    // Keyboard a and A
#define KEY_B                   ( 0x05 | 0xF000 )    // Keyboard b and B
#define KEY_C                   ( 0x06 | 0xF000 )    // Keyboard c and C
#define KEY_D                   ( 0x07 | 0xF000 )    // Keyboard d and D
#define KEY_E                   ( 0x08 | 0xF000 )    // Keyboard e and E
#define KEY_F                   ( 0x09 | 0xF000 )    // Keyboard f and F
#define KEY_G                   ( 0x0A | 0xF000 )    // Keyboard g and G
#define KEY_H                   ( 0x0B | 0xF000 )    // Keyboard h and H
#define KEY_I                   ( 0x0C | 0xF000 )    // Keyboard i and I
#define KEY_J                   ( 0x0D | 0xF000 )    // Keyboard j and J
#define KEY_K                   ( 0x0E | 0xF000 )    // Keyboard k and K
#define KEY_L                   ( 0x0F | 0xF000 )    // Keyboard l and L
#define KEY_M                   ( 0x10 | 0xF000 )    // Keyboard m and M
#define KEY_N                   ( 0x11 | 0xF000 )    // Keyboard n and N
#define KEY_O                   ( 0x12 | 0xF000 )    // Keyboard o and O
#define KEY_P                   ( 0x13 | 0xF000 )    // Keyboard p and P
#define KEY_Q                   ( 0x14 | 0xF000 )    // Keyboard q and Q
#define KEY_R                   ( 0x15 | 0xF000 )    // Keyboard r and R
#define KEY_S                   ( 0x16 | 0xF000 )    // Keyboard s and S
#define KEY_T                   ( 0x17 | 0xF000 )    // Keyboard t and T
#define KEY_U                   ( 0x18 | 0xF000 )    // Keyboard u and U
#define KEY_V                   ( 0x19 | 0xF000 )    // Keyboard v and V
#define KEY_W                   ( 0x1A | 0xF000 )    // Keyboard w and W
#define KEY_X                   ( 0x1B | 0xF000 )    // Keyboard x and X
#define KEY_Y                   ( 0x1C | 0xF000 )    // Keyboard y and Y
#define KEY_Z                   ( 0x1D | 0xF000 )    // Keyboard z and Z
#define KEY_1                   ( 0x1E | 0xF000 )    // Keyboard 1 and !
#define KEY_2                   ( 0x1F | 0xF000 )    // Keyboard 2 and
#define KEY_3                   ( 0x20 | 0xF000 )    // Keyboard 3 and #
#define KEY_4                   ( 0x21 | 0xF000 )    // Keyboard 4 and $
#define KEY_5                   ( 0x22 | 0xF000 )    // Keyboard 5 and %
#define KEY_6                   ( 0x23 | 0xF000 )    // Keyboard 6 and ^
#define KEY_7                   ( 0x24 | 0xF000 )    // Keyboard 7 and &
#define KEY_8                   ( 0x25 | 0xF000 )    // Keyboard 8 and *
#define KEY_9                   ( 0x26 | 0xF000 )    // Keyboard 9 and (
#define KEY_0                   ( 0x27 | 0xF000 )    // Keyboard 0 and )
#define KEY_ENTER               (  40  | 0xF000 )
#define KEY_ESC                 (  41  | 0xF000 )
#define KEY_BACKSPACE           (  42  | 0xF000 )
#define KEY_TAB                 (  43  | 0xF000 )
#define KEY_SPACE               (  44  | 0xF000 )
#define KEY_MINUS               ( 0x2D | 0xF000 )    // Keyboard - and (underscore)
#define KEY_EQUAL               ( 0x2E | 0xF000 )    // Keyboard = and +
#define KEY_LEFT_BRACE          ( 0x2F | 0xF000 )    // Keyboard [ and {
#define KEY_RIGHT_BRACE         ( 0x30 | 0xF000 )    // Keyboard ] and }
#define KEY_BACKSLASH           ( 0x31 | 0xF000 )    // Keyboard \ and | - if not existent, the code of the left of return key (Non-US # and ~)
#define KEY_NON_US_HASH         ( 0x32 | 0xF000 )    // Keyboard Non-US # and ~ - left of return key
#define KEY_SEMICOLON           ( 0x33 | 0xF000 )    // Keyboard ; and :
#define KEY_QUOTE               ( 0x34 | 0xF000 )    // Keyboard â€˜ and â€œ
#define KEY_TILDE               ( 0x35 | 0xF000 )    // Keyboard Grave Accent and Tilde
#define KEY_COMMA               ( 0x36 | 0xF000 )    // Keyboard , and <
#define KEY_PERIOD              ( 0x37 | 0xF000 )    // Keyboard . and >
#define KEY_SLASH               ( 0x38 | 0xF000 )    // Keyboard / and ?
#define KEY_CAPS_LOCK           (  57  | 0xF000 )
#define KEY_F1                  (  58  | 0xF000 )
#define KEY_F2                  (  59  | 0xF000 )
#define KEY_F3                  ( 0x3C | 0xF000 )
#define KEY_F4                  (  61  | 0xF000 )
#define KEY_F5                  (  62  | 0xF000 )
#define KEY_F6                  (  63  | 0xF000 )
#define KEY_F7                  ( 0x40 | 0xF000 )
#define KEY_F8                  (  65  | 0xF000 )
#define KEY_F9                  (  66  | 0xF000 )
#define KEY_F10                 (  67  | 0xF000 )
#define KEY_F11                 (  68  | 0xF000 )
#define KEY_F12                 (  69  | 0xF000 )
#define KEY_PRINTSCREEN         (  70  | 0xF000 )
#define KEY_SCROLL_LOCK         (  71  | 0xF000 )
#define KEY_PAUSE               ( 0x48 | 0xF000 )
#define KEY_INSERT              (  73  | 0xF000 )
#define KEY_HOME                (  74  | 0xF000 )
#define KEY_PAGE_UP             (  75  | 0xF000 )
#define KEY_DELETE              (  76  | 0xF000 )
#define KEY_END                 (  77  | 0xF000 )
#define KEY_PAGE_DOWN           (  78  | 0xF000 )
#define KEY_RIGHT               (  79  | 0xF000 )
#define KEY_LEFT                ( 0x50 | 0xF000 )
#define KEY_DOWN                (  81  | 0xF000 )
#define KEY_UP                  (  82  | 0xF000 )
#define KEY_NUM_LOCK            (  83  | 0xF000 )
#define KEYPAD_SLASH            (  84  | 0xF000 )
#define KEYPAD_ASTERIX          (  85  | 0xF000 )
#define KEYPAD_MINUS            (  86  | 0xF000 )
#define KEYPAD_PLUS             (  87  | 0xF000 )
#define KEYPAD_ENTER            ( 0x58 | 0xF000 )
#define KEYPAD_1                (  89  | 0xF000 )    // Keypad 1 and End
#define KEYPAD_2                (  90  | 0xF000 )    // Keypad 2 and Down Arrow
#define KEYPAD_3                (  91  | 0xF000 )    // Keypad 3 and PageDn
#define KEYPAD_4                (  92  | 0xF000 )    // Keypad 4 and Left Arrow
#define KEYPAD_5                (  93  | 0xF000 )
#define KEYPAD_6                (  94  | 0xF000 )    // Keypad 6 and Right Arrow
#define KEYPAD_7                (  95  | 0xF000 )    // Keypad 7 and Home
#define KEYPAD_8                ( 0x60 | 0xF000 )    // Keypad 8 and Up Arrow
#define KEYPAD_9                (  97  | 0xF000 )    // Keypad 9 and PageUp
#define KEYPAD_0                (  98  | 0xF000 )    // Keypad 0 and Insert
#define KEYPAD_PERIOD           (  99  | 0xF000 )    // Keypad . and Delete
#define KEY_NON_US_BS           ( 0x64 | 0xF000 )    // Keypad Non-US \ and | - bottom left
#define KEY_NON_US_BS_MAPPING   ( 0x3F          )    // Special code for this key in keycodes_ascii array. Must be < 0x40
#define KEY_MENU                ( 101  | 0xF000 )
#define KEY_F13                 ( 104  | 0xF000 )
#define KEY_F14                 ( 105  | 0xF000 )
#define KEY_F15                 ( 0x68 | 0xF000 )
#define KEY_F16                 ( 107  | 0xF000 )
#define KEY_F17                 ( 108  | 0xF000 )
#define KEY_F18                 ( 109  | 0xF000 )
#define KEY_F19                 ( 110  | 0xF000 )
#define KEY_F20                 ( 111  | 0xF000 )
#define KEY_F21                 ( 0x70 | 0xF000 )
#define KEY_F22                 ( 113  | 0xF000 )
#define KEY_F23                 ( 114  | 0xF000 )
#define KEY_F24                 ( 115  | 0xF000 )

// for compatibility with Leonardo's slightly different names
#define KEY_UP_ARROW    KEY_UP
#define KEY_DOWN_ARROW  KEY_DOWN
#define KEY_LEFT_ARROW  KEY_LEFT
#define KEY_RIGHT_ARROW KEY_RIGHT
#define KEY_RETURN      KEY_ENTER
#define KEY_LEFT_CTRL   MODIFIERKEY_LEFT_CTRL
#define KEY_LEFT_SHIFT  MODIFIERKEY_LEFT_SHIFT
#define KEY_LEFT_ALT    MODIFIERKEY_LEFT_ALT
#define KEY_LEFT_GUI    MODIFIERKEY_LEFT_GUI
#define KEY_RIGHT_CTRL  MODIFIERKEY_RIGHT_CTRL
#define KEY_RIGHT_SHIFT MODIFIERKEY_RIGHT_SHIFT
#define KEY_RIGHT_ALT   MODIFIERKEY_RIGHT_ALT
#define KEY_RIGHT_GUI   MODIFIERKEY_RIGHT_GUI

#define KEYCODE_MASK_SCANCODE   0x003F // to be used for 8 bit array keycodes_ascii
#define SHIFT_MASK              0x0040 // to be used for 8 bit array keycodes_ascii
#define ALTGR_MASK              0x0080 // to be used for 8 bit array keycodes_ascii
#define DEADKEYS_MASK           0x0F00
#define ACUTE_ACCENT_BITS       0x0100
#define DEGREE_SIGN_BITS        0x0200
#define CARON_BITS              0x0300
#define CIRCUMFLEX_BITS         0x0400
#define BREVE_BITS              0x0500
#define OGONEK_BITS             0x0600
#define GRAVE_ACCENT_BITS       0x0700
#define DOT_ABOVE_BITS          0x0800
#define DOUBLE_ACUTE_BITS       0x0900
#define DIAERESIS_BITS          0x0A00
#define CEDILLA_BITS            0x0B00
#define SHIFT_MASK_UNICODE      0x4000
#define ALTGR_MASK_UNICODE      0x8000
#define KEYCODE_MASK            0x0FFF

#define KEYCODE_TYPE            uint16_t

// Everything below this line is not intended for use in "normal" programs.
// These private symbols populate lookup tables, which are used to translate
// ascii and UTF8 unicode into keystroke sequences.

#ifdef LAYOUT_US_INTERNATIONAL

#define DEADKEY_CIRCUMFLEX      KEY_6 + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_QUOTE
#define DEADKEY_GRAVE_ACCENT    KEY_TILDE
#define DEADKEY_TILDE           KEY_TILDE + SHIFT_MASK
#define DEADKEY_DIAERESIS       KEY_QUOTE + SHIFT_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        DIAERESIS_BITS + KEY_SPACE              // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        ACUTE_ACCENT_BITS + KEY_SPACE           // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_SLASH                               // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SEMICOLON + SHIFT_MASK              // 58 :
#define ASCII_3B        KEY_SEMICOLON                           // 59 ;
#define ASCII_3C        KEY_COMMA + SHIFT_MASK                  // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_PERIOD + SHIFT_MASK                 // 62 >
#define ASCII_3F        KEY_SLASH + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + SHIFT_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE                          // 91 [
#define ASCII_5C        KEY_BACKSLASH                           // 92
#define ASCII_5D        KEY_RIGHT_BRACE                         // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_LEFT_BRACE + SHIFT_MASK             // 123 {
#define ASCII_7C        KEY_BACKSLASH + SHIFT_MASK              // 124 |
#define ASCII_7D        KEY_RIGHT_BRACE + SHIFT_MASK            // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreaking Space
#define ISO_8859_1_A1   KEY_1 + ALTGR_MASK                      // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_C + ALTGR_MASK + SHIFT_MASK         // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_4 + ALTGR_MASK + SHIFT_MASK         // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_4 + ALTGR_MASK                      // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   KEY_MINUS + ALTGR_MASK                  // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_BACKSLASH + ALTGR_MASK + SHIFT_MASK // 166 Â¦     BROKEN BAR                        ??
#define ISO_8859_1_A7   KEY_S + ALTGR_MASK + SHIFT_MASK         // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   KEY_QUOTE + ALTGR_MASK + SHIFT_MASK     // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   KEY_C + ALTGR_MASK                      // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_LEFT_BRACE + ALTGR_MASK             // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_BACKSLASH + ALTGR_MASK              // 172 Â¬     NOT SIGN                  ??
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   KEY_R + ALTGR_MASK                      // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_SEMICOLON + ALTGR_MASK + SHIFT_MASK // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_2 + ALTGR_MASK                      // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   KEY_3 + ALTGR_MASK                      // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   KEY_QUOTE + ALTGR_MASK                  // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   KEY_SEMICOLON + ALTGR_MASK              // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   KEY_1 + ALTGR_MASK + SHIFT_MASK         // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   KEY_RIGHT_BRACE + ALTGR_MASK            // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   KEY_6 + ALTGR_MASK                      // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_7 + ALTGR_MASK                      // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   KEY_8 + ALTGR_MASK                      // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   KEY_SLASH + ALTGR_MASK                  // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   KEY_A + ALTGR_MASK + SHIFT_MASK         // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   KEY_Q + ALTGR_MASK + SHIFT_MASK         // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   KEY_W + ALTGR_MASK + SHIFT_MASK         // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_Z + ALTGR_MASK + SHIFT_MASK         // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_COMMA + ALTGR_MASK + SHIFT_MASK     // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   KEY_E + ALTGR_MASK + SHIFT_MASK         // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   KEY_I + ALTGR_MASK + SHIFT_MASK         // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_D + ALTGR_MASK + SHIFT_MASK         // 208 Ã�     ETH
#define ISO_8859_1_D1   KEY_N + ALTGR_MASK + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   KEY_O + ALTGR_MASK + SHIFT_MASK         // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   KEY_P + ALTGR_MASK + SHIFT_MASK         // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   KEY_EQUAL + ALTGR_MASK                  // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   KEY_L + ALTGR_MASK + SHIFT_MASK         // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   KEY_U + ALTGR_MASK + SHIFT_MASK         // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   KEY_Y + ALTGR_MASK + SHIFT_MASK         // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_T + ALTGR_MASK + SHIFT_MASK         // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + ALTGR_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   KEY_A + ALTGR_MASK                      // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   KEY_W + ALTGR_MASK                      // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_Z + ALTGR_MASK                      // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_COMMA + ALTGR_MASK                  // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   KEY_I + ALTGR_MASK                      // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_D + ALTGR_MASK                      // 240 Ã°     ETH
#define ISO_8859_1_F1   KEY_N + ALTGR_MASK                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   KEY_O + ALTGR_MASK                      // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_P + ALTGR_MASK                      // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   KEY_EQUAL + ALTGR_MASK + SHIFT_MASK     // 247 Ã·     DIVISION
#define ISO_8859_1_F8   KEY_L + ALTGR_MASK                      // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   KEY_U + ALTGR_MASK                      // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   KEY_Y + ALTGR_MASK                      // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_T + ALTGR_MASK                      // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_5 + ALTGR_MASK                      //     €     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_5 + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_US_INTERNATIONAL

#ifdef LAYOUT_GERMAN

#define DEADKEY_CIRCUMFLEX      KEY_TILDE
#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_BACKSLASH                           // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH + SHIFT_MASK              // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_RIGHT_BRACE + SHIFT_MASK            // 42 *
#define ASCII_2B        KEY_RIGHT_BRACE                         // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                   // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK      // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_Q + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Z + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Y + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_MINUS + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        KEY_TILDE                               // 94 ^
//#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        KEY_EQUAL + SHIFT_MASK                  // 96 `
//#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Z                                   // 121 y - z and y are swapped on German keyboard
#define ASCII_7A        KEY_Y                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + ALTGR_MASK      // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        KEY_RIGHT_BRACE + ALTGR_MASK            // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreaking Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   0                                       // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_E + ALTGR_MASK                      // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_3 + SHIFT_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   0                                       // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_TILDE + SHIFT_MASK                  // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_2 + ALTGR_MASK                      // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   KEY_3 + ALTGR_MASK                      // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   0                                       // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   KEY_QUOTE + SHIFT_MASK                  // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   0                                       // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   0                                       // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   KEY_SEMICOLON + SHIFT_MASK              // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   KEY_LEFT_BRACE + SHIFT_MASK             // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Z + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_MINUS                               // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   KEY_QUOTE                               // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   0                                       // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   0                                       // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_SEMICOLON                           // 246 ¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   KEY_LEFT_BRACE                          // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Z               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   0                                       // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //      €     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_GERMAN

#ifdef LAYOUT_GERMAN_MAC

#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_CIRCUMFLEX      KEY_6 + SHIFT_MASK + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_U + ALTGR_MASK
#define DEADKEY_TILDE           KEY_N + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_BACKSLASH                           // 35 #         ??
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH + SHIFT_MASK              // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_RIGHT_BRACE + SHIFT_MASK            // 42 *
#define ASCII_2B        KEY_RIGHT_BRACE                         // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_TILDE                               // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_TILDE + SHIFT_MASK                  // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_Q + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Z + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Y + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_5 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_7 + ALTGR_MASK + SHIFT_MASK         // 92
#define ASCII_5D        KEY_6 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Z                                   // 121 y
#define ASCII_7A        KEY_Y                                   // 122 z
#define ASCII_7B        KEY_8 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_7 + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_9 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   KEY_1 + ALTGR_MASK                      // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_4 + ALTGR_MASK                      // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   KEY_4 + SHIFT_MASK + ALTGR_MASK         // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_E + ALTGR_MASK                      // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   KEY_Z + ALTGR_MASK                      // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_3 + SHIFT_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   KEY_G + ALTGR_MASK                      // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   KEY_H + ALTGR_MASK                      // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_Q + ALTGR_MASK                      // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   KEY_R + ALTGR_MASK                      // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   KEY_0 + SHIFT_MASK + ALTGR_MASK         // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_LEFT_BRACE + ALTGR_MASK + SHIFT_MASK// 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   KEY_RIGHT_BRACE + ALTGR_MASK            // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   KEY_3 + ALTGR_MASK                      // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   KEY_9 + SHIFT_MASK + ALTGR_MASK         // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   KEY_J + ALTGR_MASK                      // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   KEY_Q + SHIFT_MASK + ALTGR_MASK         // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   KEY_MINUS + ALTGR_MASK                  // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   KEY_QUOTE + SHIFT_MASK                  // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   KEY_A + ALTGR_MASK + SHIFT_MASK         // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_QUOTE + ALTGR_MASK + SHIFT_MASK     // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_C + ALTGR_MASK + SHIFT_MASK         // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   KEY_SEMICOLON + SHIFT_MASK              // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   KEY_O + ALTGR_MASK + SHIFT_MASK         // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   KEY_LEFT_BRACE + SHIFT_MASK             // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Z + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_MINUS                               // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   KEY_QUOTE                               // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   KEY_A + ALTGR_MASK                      // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_QUOTE + ALTGR_MASK                  // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_C + ALTGR_MASK                      // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_SEMICOLON                           // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   KEY_O + ALTGR_MASK                      // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   KEY_LEFT_BRACE                          // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Z               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Z                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_GERMAN_MAC

#ifdef LAYOUT_CANADIAN_FRENCH

#define KEYCODE_TYPE            uint16_t
#define KEYCODE_MASK            0x07FF
#define DEADKEY_CIRCUMFLEX      KEY_LEFT_BRACE
#define DEADKEY_ACUTE_ACCENT    KEY_SLASH + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_QUOTE
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_CEDILLA         KEY_RIGHT_BRACE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_TILDE + SHIFT_MASK                  // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_COMMA + SHIFT_MASK                  // 39 '
//#define ASCII_27      ACUTE_ACCENT_BITS + KEY_SPACE           // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_3 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SEMICOLON + SHIFT_MASK              // 58 :
#define ASCII_3B        KEY_SEMICOLON                           // 59 ;
#define ASCII_3C        KEY_BACKSLASH                           // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_BACKSLASH + SHIFT_MASK              // 62 >
#define ASCII_3F        KEY_6 + SHIFT_MASK                      // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE + ALTGR_MASK             // 91 [
#define ASCII_5C        KEY_TILDE + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_RIGHT_BRACE + ALTGR_MASK            // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_QUOTE + ALTGR_MASK                  // 123 {
#define ASCII_7C        KEY_TILDE + SHIFT_MASK                  // 124 |
#define ASCII_7D        KEY_BACKSLASH + ALTGR_MASK              // 125 }
#define ASCII_7E        KEY_SEMICOLON + ALTGR_MASK              // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_4 + ALTGR_MASK                      // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_5 + ALTGR_MASK                      // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_7 + ALTGR_MASK                      // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_O + ALTGR_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   0                                       // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_NON_US_BS                          // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_6 + ALTGR_MASK                      // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   KEY_PERIOD + ALTGR_MASK                 // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   KEY_COMMA + ALTGR_MASK                  // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_NON_US_BS + ALTGR_MASK             // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   KEY_1 + ALTGR_MASK                      // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_8 + ALTGR_MASK                      // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   KEY_9 + ALTGR_MASK                      // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   0                                       // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   KEY_P + ALTGR_MASK                      // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   KEY_NON_US_BS + SHIFT_MASK             // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   KEY_0 + ALTGR_MASK                      // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_MINUS + ALTGR_MASK                  // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   KEY_EQUAL + ALTGR_MASK                  // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   CEDILLA_BITS + KEY_C + SHIFT_MASK       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   KEY_SLASH + SHIFT_MASK                  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U                  // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   CEDILLA_BITS + KEY_C                    // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_SLASH                               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_CANADIAN_FRENCH

#ifdef LAYOUT_CANADIAN_MULTILINGUAL

#define DEADKEY_CIRCUMFLEX      KEY_LEFT_BRACE
#define DEADKEY_DIAERESIS       KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_SEMICOLON + RCTRL_MASK
#define DEADKEY_CEDILLA         KEY_EQUAL + RCTRL_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_LEFT_BRACE + ALTGR_MASK
#define DEADKEY_TILDE           KEY_RIGHT_BRACE + ALTGR_MASK
#define DEADKEY_RING_ABOVE      KEY_LEFT_BRACE + SHIFT_MASK + RCTRL_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_PERIOD + SHIFT_MASK                 // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_COMMA + SHIFT_MASK                  // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_TILDE                               // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SEMICOLON + SHIFT_MASK              // 58 :
#define ASCII_3B        KEY_SEMICOLON                           // 59 ;
#define ASCII_3C        KEY_COMMA + ALTGR_MASK                  // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_PERIOD + ALTGR_MASK                 // 62 >
#define ASCII_3F        KEY_6 + SHIFT_MASK                      // 63 ?
#define ASCII_40        KEY_2 + SHIFT_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_9 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_TILDE + SHIFT_MASK                  // 92
#define ASCII_5D        KEY_0 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_TILDE + ALTGR_MASK                  // 124 |
#define ASCII_7D        KEY_8 + ALTGR_MASK                      // 125 }
#define ASCII_7E        KEY_RIGHT_BRACE + RCTRL_MASK            // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE + ALTGR_MASK                  // 160       Nonbreakng Space
#define ISO_8859_1_A1   KEY_1 + SHIFT_MASK + RCTRL_MASK         // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_C + RCTRL_MASK                      // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + SHIFT_MASK + RCTRL_MASK         // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_4 + SHIFT_MASK + RCTRL_MASK         // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   KEY_Y + SHIFT_MASK + RCTRL_MASK         // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_NON_US_BS + SHIFT_MASK + RCTRL_MASK// 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_S + SHIFT_MASK + RCTRL_MASK         // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   KEY_C + SHIFT_MASK + RCTRL_MASK         // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   KEY_F + SHIFT_MASK + RCTRL_MASK         // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_Z + ALTGR_MASK                      // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_EQUAL + ALTGR_MASK                  // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   KEY_TILDE + SHIFT_MASK + RCTRL_MASK     // 173       SOFT HYPHEN
#define ISO_8859_1_AE   KEY_R + SHIFT_MASK + RCTRL_MASK         // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0  // special dead key - no implemented // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_SEMICOLON + ALTGR_MASK              // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   KEY_9 + SHIFT_MASK + RCTRL_MASK         // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_2 + RCTRL_MASK                      // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   KEY_3 + RCTRL_MASK                      // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + RCTRL_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   KEY_R + RCTRL_MASK                      // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   CEDILLA_BITS + KEY_SPACE                // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   KEY_1 + RCTRL_MASK                      // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   KEY_M + SHIFT_MASK + RCTRL_MASK         // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   KEY_X + ALTGR_MASK                      // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   KEY_4 + RCTRL_MASK                      // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_5 + RCTRL_MASK                      // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   KEY_6 + RCTRL_MASK                      // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   KEY_MINUS + SHIFT_MASK + RCTRL_MASK     // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   KEY_BACKSLASH + SHIFT_MASK              // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   RING_ABOVE_BITS + KEY_A + SHIFT_MASK    // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_A + SHIFT_MASK + RCTRL_MASK         // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_RIGHT_BRACE + SHIFT_MASK            // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   KEY_QUOTE + SHIFT_MASK                  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   KEY_SLASH + SHIFT_MASK                  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_D + SHIFT_MASK + RCTRL_MASK         // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   KEY_COMMA + SHIFT_MASK + RCTRL_MASK     // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   KEY_O + SHIFT_MASK + RCTRL_MASK         // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   KEY_NON_US_BS + SHIFT_MASK             // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U                  // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_P + RCTRL_MASK + SHIFT_MASK         // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + RCTRL_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   KEY_BACKSLASH                           // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   RING_ABOVE_BITS + KEY_A                 // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_A + RCTRL_MASK                      // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_RIGHT_BRACE                         // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   KEY_QUOTE                               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_SLASH                               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_D + RCTRL_MASK                      // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   KEY_PERIOD + SHIFT_MASK + RCTRL_MASK    // 247 Ã·     DIVISION
#define ISO_8859_1_F8   KEY_O + RCTRL_MASK                      // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   KEY_NON_US_BS                          // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_P + RCTRL_MASK                      // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_CANADIAN_MULTILINGUAL

#ifdef LAYOUT_UNITED_KINGDOM

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_BACKSLASH                           // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_QUOTE                               // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_SLASH                               // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SEMICOLON + SHIFT_MASK              // 58 :
#define ASCII_3B        KEY_SEMICOLON                           // 59 ;
#define ASCII_3C        KEY_COMMA + SHIFT_MASK                  // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_PERIOD + SHIFT_MASK                 // 62 >
#define ASCII_3F        KEY_SLASH + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_QUOTE + SHIFT_MASK                  // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE                          // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING                          // 92
#define ASCII_5D        KEY_RIGHT_BRACE                         // 93 ]
#define ASCII_5E        KEY_6 + SHIFT_MASK                      // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        KEY_TILDE                               // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_LEFT_BRACE + SHIFT_MASK             // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 124 |
#define ASCII_7D        KEY_RIGHT_BRACE + SHIFT_MASK            // 125 }
#define ASCII_7E        KEY_BACKSLASH + SHIFT_MASK              // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + SHIFT_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_TILDE + ALTGR_MASK                  // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   0                                       // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   0                                       // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_TILDE + SHIFT_MASK                  // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   0                                       // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   0                                       // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   KEY_A + ALTGR_MASK + SHIFT_MASK         // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   0                                       // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   0                                       // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   0                                       // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   KEY_E + ALTGR_MASK + SHIFT_MASK         // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   0                                       // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   0                                       // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   0                                       // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   KEY_I + ALTGR_MASK + SHIFT_MASK         // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   0                                       // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   0                                       // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   0                                       // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   KEY_O + ALTGR_MASK + SHIFT_MASK         // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   0                                       // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   0                                       // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   0                                       // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   KEY_U + ALTGR_MASK + SHIFT_MASK         // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   0                                       // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   0                                       // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   0                                       // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   0                                       // 224 Ã      a GRAVE
#define ISO_8859_1_E1   KEY_A + ALTGR_MASK                      // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   0                                       // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   0                                       // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   0                                       // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_E + ALTGR_MASK                      // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   0                                       // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   0                                       // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   0                                       // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   KEY_I + ALTGR_MASK                      // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   0                                       // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   0                                       // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   0                                       // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   KEY_O + ALTGR_MASK                      // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   0                                       // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   0                                       // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   0                                       // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   KEY_U + ALTGR_MASK                      // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   0                                       // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   0                                       // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   0                                       // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   0                                       // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_4 + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_4 + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_UNITED_KINGDOM

#ifdef LAYOUT_FINNISH

#define DEADKEY_CIRCUMFLEX      KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_TILDE           KEY_RIGHT_BRACE + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + ALTGR_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH                           // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_BACKSLASH + SHIFT_MASK              // 42 *
#define ASCII_2B        KEY_MINUS                               // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_MINUS + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE + ALTGR_MASK                  // 160       Nonbreakng Space
#define ISO_8859_1_A1   KEY_1 + SHIFT_MASK + ALTGR_MASK         // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_4 + SHIFT_MASK                      // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_TILDE                               // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_4 + ALTGR_MASK + SHIFT_MASK         // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   KEY_SLASH + ALTGR_MASK                  // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_0 + ALTGR_MASK + SHIFT_MASK         // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   KEY_X + ALTGR_MASK + SHIFT_MASK         // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   KEY_3 + ALTGR_MASK + SHIFT_MASK         // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_TILDE + SHIFT_MASK                  // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   KEY_MINUS + ALTGR_MASK + SHIFT_MASK     // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   KEY_QUOTE + SHIFT_MASK                  // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   KEY_LEFT_BRACE + SHIFT_MASK             // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_QUOTE + ALTGR_MASK + SHIFT_MASK     // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_D + ALTGR_MASK + SHIFT_MASK         // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   KEY_SEMICOLON + SHIFT_MASK              // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   KEY_X + ALTGR_MASK                      // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   KEY_SEMICOLON + ALTGR_MASK + SHIFT_MASK // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_T + ALTGR_MASK + SHIFT_MASK         // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + ALTGR_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   KEY_QUOTE                               // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   KEY_LEFT_BRACE                          // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_QUOTE + ALTGR_MASK                  // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_D + ALTGR_MASK                      // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_SEMICOLON                           // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   KEY_SEMICOLON + ALTGR_MASK              // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_T + ALTGR_MASK                      // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign
// TODO: Finnish Multilingual layout can type many more glyphs
// but we currently don't have tables to store them...

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_FINNISH

#ifdef LAYOUT_FRENCH

#define DEADKEY_CIRCUMFLEX      KEY_LEFT_BRACE
#define DEADKEY_GRAVE_ACCENT    KEY_7 + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE           KEY_2 + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_SLASH                               // 33 !
#define ASCII_22        KEY_3                                   // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_RIGHT_BRACE                         // 36 $
#define ASCII_25        KEY_QUOTE + SHIFT_MASK                  // 37 %
#define ASCII_26        KEY_1                                   // 38 &
#define ASCII_27        KEY_4                                   // 39 '
#define ASCII_28        KEY_5                                   // 40 (
#define ASCII_29        KEY_MINUS                               // 41 )
#define ASCII_2A        KEY_BACKSLASH                           // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_M                                   // 44 ,
#define ASCII_2D        KEY_6                                   // 45 -
#define ASCII_2E        KEY_COMMA + SHIFT_MASK                  // 46 .
#define ASCII_2F        KEY_PERIOD + SHIFT_MASK                 // 47 /
#define ASCII_30        KEY_0 + SHIFT_MASK                      // 48 0
#define ASCII_31        KEY_1 + SHIFT_MASK                      // 49 1
#define ASCII_32        KEY_2 + SHIFT_MASK                      // 50 2
#define ASCII_33        KEY_3 + SHIFT_MASK                      // 51 3
#define ASCII_34        KEY_4 + SHIFT_MASK                      // 52 4
#define ASCII_35        KEY_5 + SHIFT_MASK                      // 53 5
#define ASCII_36        KEY_6 + SHIFT_MASK                      // 54 6
#define ASCII_37        KEY_7 + SHIFT_MASK                      // 55 7
#define ASCII_38        KEY_8 + SHIFT_MASK                      // 55 8
#define ASCII_39        KEY_9 + SHIFT_MASK                      // 57 9
#define ASCII_3A        KEY_PERIOD                              // 58 :
#define ASCII_3B        KEY_COMMA                               // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_M + SHIFT_MASK                      // 63 ?
#define ASCII_40        KEY_0 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_Q + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_SEMICOLON + SHIFT_MASK              // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_A + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_Z + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_W + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_5 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_8 + ALTGR_MASK                      // 92
#define ASCII_5D        KEY_MINUS + ALTGR_MASK                  // 93 ]
#define ASCII_5E        KEY_9 + ALTGR_MASK                      // 94 ^
#define ASCII_5F        KEY_8                                   // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_Q                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_SEMICOLON                           // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_A                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_Z                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_W                                   // 122 z
#define ASCII_7B        KEY_4 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_6 + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_EQUAL + ALTGR_MASK                  // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_RIGHT_BRACE + SHIFT_MASK            // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_RIGHT_BRACE + ALTGR_MASK            // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_SLASH + SHIFT_MASK                  // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_MINUS + SHIFT_MASK                  // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_TILDE                               // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   0                                       // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_BACKSLASH + SHIFT_MASK              // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_Q + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   0                                       // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_Q + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_Q + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_Q + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   0                                       // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   0                                       // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   0                                       // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   0                                       // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U                  // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   0                                       // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   KEY_0                                   // 224 Ã      a GRAVE
#define ISO_8859_1_E1   0                                       // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_Q                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_Q                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_Q                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_9                                   // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   KEY_7                                   // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_2                                   // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   0                                       // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   0                                       // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   KEY_SEMICOLON                           // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   0                                       // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   0                                       // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_FRENCH

#ifdef LAYOUT_DANISH

#define DEADKEY_CIRCUMFLEX      KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_TILDE           KEY_RIGHT_BRACE + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + ALTGR_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH                           // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_BACKSLASH + SHIFT_MASK              // 42 *
#define ASCII_2B        KEY_MINUS                               // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_EQUAL + ALTGR_MASK                  // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_4 + SHIFT_MASK                      // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_TILDE + SHIFT_MASK                  // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_4                                   // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_TILDE                               // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   KEY_LEFT_BRACE + SHIFT_MASK             // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_SEMICOLON + SHIFT_MASK              // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_D + ALTGR_MASK + SHIFT_MASK         // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   KEY_QUOTE + SHIFT_MASK                  // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_T + ALTGR_MASK + SHIFT_MASK         // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + ALTGR_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   KEY_LEFT_BRACE                          // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_SEMICOLON                           // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_D + ALTGR_MASK                      // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   KEY_QUOTE                               // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_T + ALTGR_MASK                      // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_DANISH

#ifdef LAYOUT_NORWEGIAN

#define DEADKEY_CIRCUMFLEX      KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_TILDE           KEY_RIGHT_BRACE + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + ALTGR_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH                           // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_BACKSLASH + SHIFT_MASK              // 42 *
#define ASCII_2B        KEY_MINUS                               // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_EQUAL                               // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_TILDE                               // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_4 + SHIFT_MASK                      // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_TILDE + SHIFT_MASK                  // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_4                                   // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_TILDE                               // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   KEY_LEFT_BRACE + SHIFT_MASK             // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_QUOTE + SHIFT_MASK                  // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_D + ALTGR_MASK + SHIFT_MASK         // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   KEY_SEMICOLON + SHIFT_MASK              // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_T + ALTGR_MASK + SHIFT_MASK         // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + ALTGR_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   KEY_LEFT_BRACE                          // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_QUOTE                               // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_D + ALTGR_MASK                      // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   KEY_SEMICOLON                           // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_T + ALTGR_MASK                      // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_NORWEGIAN

#ifdef LAYOUT_SWEDISH

#define DEADKEY_CIRCUMFLEX      KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_TILDE           KEY_RIGHT_BRACE + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + ALTGR_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH                           // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_BACKSLASH + SHIFT_MASK              // 42 *
#define ASCII_2B        KEY_MINUS                               // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_MINUS + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_4 + SHIFT_MASK                      // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_TILDE                               // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_4                                   // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_TILDE + SHIFT_MASK                  // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   KEY_QUOTE + SHIFT_MASK                  // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   KEY_LEFT_BRACE + SHIFT_MASK             // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_D + ALTGR_MASK + SHIFT_MASK         // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   KEY_SEMICOLON + SHIFT_MASK              // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_T + ALTGR_MASK + SHIFT_MASK         // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + ALTGR_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   KEY_QUOTE                               // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   KEY_LEFT_BRACE                          // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_D + ALTGR_MASK                      // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_SEMICOLON                           // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_T + ALTGR_MASK                      // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_SWEDISH

#ifdef LAYOUT_SPANISH

#define DEADKEY_CIRCUMFLEX      KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_QUOTE
#define DEADKEY_GRAVE_ACCENT    KEY_LEFT_BRACE
#define DEADKEY_TILDE           KEY_4 + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_QUOTE + SHIFT_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_RIGHT_BRACE + SHIFT_MASK            // 42 *
#define ASCII_2B        KEY_RIGHT_BRACE                         // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE + ALTGR_MASK             // 91 [
#define ASCII_5C        KEY_TILDE + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_RIGHT_BRACE + ALTGR_MASK            // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_QUOTE + ALTGR_MASK                  // 123 {
#define ASCII_7C        KEY_1 + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_BACKSLASH + ALTGR_MASK              // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   KEY_EQUAL                               // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   0                                       // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   0                                       // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   KEY_TILDE + SHIFT_MASK                  // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_6 + ALTGR_MASK                      // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   KEY_3 + SHIFT_MASK                      // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   KEY_TILDE                               // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   KEY_EQUAL                               // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_BACKSLASH + SHIFT_MASK              // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   KEY_SEMICOLON + SHIFT_MASK              // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_BACKSLASH                           // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   KEY_SEMICOLON                           // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_5 + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_5 + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_SPANISH

#ifdef LAYOUT_PORTUGUESE

#define DEADKEY_CIRCUMFLEX      KEY_BACKSLASH
#define DEADKEY_ACUTE_ACCENT    KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_RIGHT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE           KEY_BACKSLASH
#define DEADKEY_DIAERESIS       KEY_LEFT_BRACE + SHIFT_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_LEFT_BRACE + SHIFT_MASK             // 42 *
#define ASCII_2B        KEY_LEFT_BRACE                          // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_TILDE + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_TILDE + SHIFT_MASK                  // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_4 + ALTGR_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   KEY_QUOTE + SHIFT_MASK                  // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   KEY_EQUAL                               // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   KEY_QUOTE                               // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   KEY_EQUAL + SHIFT_MASK                  // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_SEMICOLON + SHIFT_MASK              // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_SEMICOLON                           // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_PORTUGUESE

#ifdef LAYOUT_ITALIAN

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_QUOTE + ALTGR_MASK                  // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_RIGHT_BRACE + SHIFT_MASK            // 42 *
#define ASCII_2B        KEY_RIGHT_BRACE                         // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_SEMICOLON + ALTGR_MASK              // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE + ALTGR_MASK             // 91 [
#define ASCII_5C        KEY_TILDE                               // 92
#define ASCII_5D        KEY_RIGHT_BRACE + ALTGR_MASK            // 93 ]
#define ASCII_5E        KEY_EQUAL + SHIFT_MASK                  // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        0                                       // 96 `  (how to type this on Italian?)
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_LEFT_BRACE + SHIFT_MASK + ALTGR_MASK // 123 {
#define ASCII_7C        KEY_TILDE + SHIFT_MASK                  // 124 |
#define ASCII_7D        KEY_RIGHT_BRACE + SHIFT_MASK + ALTGR_MASK // 125 }
#define ASCII_7E        0                                       // 126 ~   (how to type this on Italian?)
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   KEY_3 + SHIFT_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_BACKSLASH + SHIFT_MASK              // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   0                                       // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_QUOTE + SHIFT_MASK                  // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   0                                       // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   0                                       // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   0                                       // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   0                                       // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   0                                       // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   0                                       // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   0                                       // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   0                                       // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   0                                       // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   0                                       // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   0                                       // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   0                                       // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   0                                       // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   0                                       // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   0                                       // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   0                                       // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   0                                       // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   0                                       // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   0                                       // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   0                                       // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   0                                       // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   0                                       // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   KEY_QUOTE                               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   0                                       // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   0                                       // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   0                                       // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_SEMICOLON + SHIFT_MASK              // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   KEY_LEFT_BRACE                          // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_LEFT_BRACE + SHIFT_MASK             // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   0                                       // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   0                                       // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   KEY_EQUAL                               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   0                                       // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   0                                       // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   0                                       // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   KEY_SEMICOLON                           // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   0                                       // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   0                                       // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   0                                       // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   KEY_BACKSLASH                           // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   0                                       // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   0                                       // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   0                                       // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   0                                       // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   0                                       // 255 Ã¿     y DIAERESIS

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_ITALIAN

#ifdef LAYOUT_PORTUGUESE_BRAZILIAN

#define DEADKEY_CIRCUMFLEX      KEY_QUOTE + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_LEFT_BRACE
#define DEADKEY_GRAVE_ACCENT    KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE           KEY_QUOTE
#define DEADKEY_DIAERESIS       KEY_6 + SHIFT_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_TILDE + SHIFT_MASK                  // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_TILDE                               // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_Q + ALTGR_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SLASH + SHIFT_MASK                  // 58 :
#define ASCII_3B        KEY_SLASH                               // 59 ;
#define ASCII_3C        KEY_COMMA + SHIFT_MASK                  // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_PERIOD + SHIFT_MASK                 // 62 >
#define ASCII_3F        KEY_W + ALTGR_MASK                      // 63 ?
#define ASCII_40        KEY_2 + SHIFT_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_RIGHT_BRACE                         // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING                          // 92
#define ASCII_5D        KEY_BACKSLASH                           // 93 ]
#define ASCII_5E        KEY_QUOTE + SHIFT_MASK                  // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        KEY_LEFT_BRACE + SHIFT_MASK             // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_RIGHT_BRACE + SHIFT_MASK            // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 124 |
#define ASCII_7D        KEY_BACKSLASH + SHIFT_MASK              // 125 }
#define ASCII_7E        KEY_QUOTE                               // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_5 + ALTGR_MASK                      // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_4 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_EQUAL + ALTGR_MASK                  // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   KEY_RIGHT_BRACE + ALTGR_MASK            // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_6 + ALTGR_MASK                      // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_E + ALTGR_MASK                      // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_2 + ALTGR_MASK                      // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   KEY_2 + ALTGR_MASK                      // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   KEY_1 + ALTGR_MASK                      // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   KEY_BACKSLASH + ALTGR_MASK              // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_SEMICOLON + SHIFT_MASK              // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_SEMICOLON                           // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_PORTUGUESE_BRAZILIAN

#ifdef LAYOUT_FRENCH_BELGIAN

#define DEADKEY_CIRCUMFLEX      KEY_LEFT_BRACE
#define DEADKEY_ACUTE_ACCENT    KEY_QUOTE + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_BACKSLASH + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE           KEY_SLASH + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_8                                   // 33 !
#define ASCII_22        KEY_3                                   // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_RIGHT_BRACE                         // 36 $
#define ASCII_25        KEY_QUOTE + SHIFT_MASK                  // 37 %
#define ASCII_26        KEY_1                                   // 38 &
#define ASCII_27        KEY_4                                   // 39 '
#define ASCII_28        KEY_5                                   // 40 (
#define ASCII_29        KEY_MINUS                               // 41 )
#define ASCII_2A        KEY_RIGHT_BRACE + SHIFT_MASK            // 42 *
#define ASCII_2B        KEY_SLASH + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_M                                   // 44 ,
#define ASCII_2D        KEY_EQUAL                               // 45 -
#define ASCII_2E        KEY_COMMA + SHIFT_MASK                  // 46 .
#define ASCII_2F        KEY_PERIOD + SHIFT_MASK                 // 47 /
#define ASCII_30        KEY_0 + SHIFT_MASK                      // 48 0
#define ASCII_31        KEY_1 + SHIFT_MASK                      // 49 1
#define ASCII_32        KEY_2 + SHIFT_MASK                      // 50 2
#define ASCII_33        KEY_3 + SHIFT_MASK                      // 51 3
#define ASCII_34        KEY_4 + SHIFT_MASK                      // 52 4
#define ASCII_35        KEY_5 + SHIFT_MASK                      // 53 5
#define ASCII_36        KEY_6 + SHIFT_MASK                      // 54 6
#define ASCII_37        KEY_7 + SHIFT_MASK                      // 55 7
#define ASCII_38        KEY_8 + SHIFT_MASK                      // 55 8
#define ASCII_39        KEY_9 + SHIFT_MASK                      // 57 9
#define ASCII_3A        KEY_PERIOD                              // 58 :
#define ASCII_3B        KEY_COMMA                               // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_SLASH                               // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_M + SHIFT_MASK                      // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_Q + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_SEMICOLON + SHIFT_MASK              // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_A + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_Z + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_W + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE + ALTGR_MASK             // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 92
#define ASCII_5D        KEY_RIGHT_BRACE + ALTGR_MASK            // 93 ]
#define ASCII_5E        KEY_6 + ALTGR_MASK                      // 94 ^
#define ASCII_5F        KEY_EQUAL + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_Q                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_SEMICOLON                           // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_A                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_Z                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_W                                   // 122 z
#define ASCII_7B        KEY_9 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_1 + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreaking Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_BACKSLASH + SHIFT_MASK              // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_6                                   // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_MINUS + SHIFT_MASK                  // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   KEY_TILDE                               // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   KEY_TILDE + SHIFT_MASK                  // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_BACKSLASH                           // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_Q + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_Q + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_Q + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_Q + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_Q + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U                  // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   KEY_0                                   // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_Q               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_Q                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_Q                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_Q                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_9                                   // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   KEY_7                                   // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_2                                   // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   KEY_QUOTE                               // 249 Ã¹     u GRAVE - TODO; check FRENCH
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_FRENCH_BELGIAN

#ifdef LAYOUT_GERMAN_SWISS

#define DEADKEY_CIRCUMFLEX      KEY_EQUAL
#define DEADKEY_ACUTE_ACCENT    KEY_MINUS + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE
#define DEADKEY_TILDE           KEY_EQUAL + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_RIGHT_BRACE + SHIFT_MASK            // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_BACKSLASH                           // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_3 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_1 + SHIFT_MASK                      // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Z + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Y + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE + ALTGR_MASK             // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 92
#define ASCII_5D        KEY_RIGHT_BRACE + ALTGR_MASK            // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Z                                   // 121 y
#define ASCII_7A        KEY_Y                                   // 122 z
#define ASCII_7B        KEY_QUOTE + ALTGR_MASK                  // 123 {
#define ASCII_7C        KEY_7 + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_BACKSLASH + ALTGR_MASK              // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_8 + ALTGR_MASK                      // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   KEY_BACKSLASH + SHIFT_MASK              // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_1 + ALTGR_MASK                      // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_5 + ALTGR_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_6 + ALTGR_MASK                      // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_4 + ALTGR_MASK                      // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   KEY_QUOTE + SHIFT_MASK                  // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   KEY_QUOTE                               // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_4 + SHIFT_MASK                      // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   KEY_LEFT_BRACE + SHIFT_MASK             // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_SEMICOLON + SHIFT_MASK              // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS  TODO: check this
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_SEMICOLON                           // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   KEY_LEFT_BRACE                          // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_GERMAN_SWISS

#ifdef LAYOUT_FRENCH_SWISS

#define DEADKEY_CIRCUMFLEX      KEY_EQUAL
#define DEADKEY_ACUTE_ACCENT    KEY_MINUS + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_EQUAL + SHIFT_MASK
#define DEADKEY_DIAERESIS       KEY_RIGHT_BRACE
#define DEADKEY_TILDE           KEY_EQUAL + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_RIGHT_BRACE + SHIFT_MASK            // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_BACKSLASH                           // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_3 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_1 + SHIFT_MASK                      // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Z + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Y + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE + ALTGR_MASK             // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 92
#define ASCII_5D        KEY_RIGHT_BRACE + ALTGR_MASK            // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Z                                   // 121 y
#define ASCII_7A        KEY_Y                                   // 122 z
#define ASCII_7B        KEY_QUOTE + ALTGR_MASK                  // 123 {
#define ASCII_7C        KEY_7 + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_BACKSLASH + ALTGR_MASK              // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   KEY_8 + ALTGR_MASK                      // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   KEY_BACKSLASH + SHIFT_MASK              // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_1 + ALTGR_MASK                      // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_5 + ALTGR_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_6 + ALTGR_MASK                      // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_4 + ALTGR_MASK                      // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   KEY_QUOTE                               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   KEY_QUOTE + SHIFT_MASK                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_4 + SHIFT_MASK                      // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   KEY_LEFT_BRACE                          // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_SEMICOLON                           // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_SEMICOLON + SHIFT_MASK              // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   KEY_LEFT_BRACE + SHIFT_MASK             // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_FRENCH_SWISS

#ifdef LAYOUT_SPANISH_LATIN_AMERICA

#define DEADKEY_CIRCUMFLEX      KEY_QUOTE + ALTGR_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_LEFT_BRACE
#define DEADKEY_GRAVE_ACCENT    KEY_BACKSLASH + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_LEFT_BRACE + SHIFT_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_RIGHT_BRACE + SHIFT_MASK            // 42 *
#define ASCII_2B        KEY_RIGHT_BRACE                         // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_Q + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_QUOTE + SHIFT_MASK                  // 91 [
#define ASCII_5C        KEY_MINUS + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_BACKSLASH + SHIFT_MASK              // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_QUOTE                               // 123 {
#define ASCII_7C        KEY_TILDE                               // 124 |
#define ASCII_7D        KEY_BACKSLASH                           // 125 }
#define ASCII_7E        KEY_RIGHT_BRACE + ALTGR_MASK            // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   KEY_EQUAL + SHIFT_MASK                  // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   0                                       // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   0                                       // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_TILDE + ALTGR_MASK                  // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_TILDE + SHIFT_MASK                  // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   KEY_EQUAL                               // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   KEY_SEMICOLON + SHIFT_MASK              // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   KEY_SEMICOLON                           // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_SPANISH_LATIN_AMERICA

#ifdef LAYOUT_IRISH

#define DEADKEY_ACUTE_ACCENT    KEY_QUOTE + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_TILDE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_BACKSLASH                           // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_QUOTE                               // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_SLASH                               // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SEMICOLON + SHIFT_MASK              // 58 :
#define ASCII_3B        KEY_SEMICOLON                           // 59 ;
#define ASCII_3C        KEY_COMMA + SHIFT_MASK                  // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_PERIOD + SHIFT_MASK                 // 62 >
#define ASCII_3F        KEY_SLASH + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_QUOTE + SHIFT_MASK                  // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE                          // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING                          // 92
#define ASCII_5D        KEY_RIGHT_BRACE                         // 93 ]
#define ASCII_5E        KEY_6 + SHIFT_MASK                      // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        KEY_QUOTE + SHIFT_MASK + ALTGR_MASK     // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_LEFT_BRACE + SHIFT_MASK             // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 124 |
#define ASCII_7D        KEY_RIGHT_BRACE + SHIFT_MASK            // 125 }
#define ASCII_7E        KEY_BACKSLASH + SHIFT_MASK              // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_3 + SHIFT_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   KEY_TILDE + ALTGR_MASK                  // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   0                                       // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   0                                       // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   KEY_TILDE + SHIFT_MASK                  // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   0                                       // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A               // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   KEY_A + ALTGR_MASK + SHIFT_MASK         // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   0                                       // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   0                                       // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E               // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   KEY_E + ALTGR_MASK + SHIFT_MASK         // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   0                                       // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   0                                       // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I               // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   KEY_I + ALTGR_MASK + SHIFT_MASK         // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   0                                       // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   0                                       // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O               // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   KEY_O + ALTGR_MASK + SHIFT_MASK         // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   0                                       // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   0                                       // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U               // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   KEY_U + ALTGR_MASK + SHIFT_MASK         // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   0                                       // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   0                                       // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   KEY_A + ALTGR_MASK                      // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   0                                       // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   0                                       // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_E + ALTGR_MASK                      // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   0                                       // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   0                                       // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   KEY_I + ALTGR_MASK                      // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   0                                       // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   0                                       // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   KEY_O + ALTGR_MASK                      // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   0                                       // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   0                                       // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   KEY_U + ALTGR_MASK                      // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   0                                       // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   0                                       // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   0                                       // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_4 + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_4 + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_IRISH

#ifdef LAYOUT_ICELANDIC

#define DEADKEY_CIRCUMFLEX      KEY_QUOTE + ALTGR_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_QUOTE
#define DEADKEY_GRAVE_ACCENT    KEY_BACKSLASH + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_TILDE + SHIFT_MASK
#define DEADKEY_RING_ABOVE      KEY_TILDE

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_QUOTE + SHIFT_MASK                  // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_BACKSLASH + SHIFT_MASK              // 42 *
#define ASCII_2B        KEY_BACKSLASH                           // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_EQUAL                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_RIGHT_BRACE + SHIFT_MASK            // 63 ?
#define ASCII_40        KEY_Q + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_MINUS + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_EQUAL + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + ALTGR_MASK             // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        KEY_RIGHT_BRACE + ALTGR_MASK            // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   0                                       // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR                        ??
#define ISO_8859_1_A7   0                                       // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN                  ??
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   KEY_TILDE + ALTGR_MASK                  // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   KEY_M + ALTGR_MASK                      // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + ALTGR_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   RING_ABOVE_BITS + KEY_A + SHIFT_MASK    // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_SEMICOLON + SHIFT_MASK              // 198 Ã†     AE
#define ISO_8859_1_C7   0                                       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   KEY_LEFT_BRACE + SHIFT_MASK             // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   KEY_SLASH + SHIFT_MASK                  // 222 Ãž     THORN
#define ISO_8859_1_DF   0                                       // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   RING_ABOVE_BITS + KEY_A                 // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   KEY_SEMICOLON                           // 230 Ã¦     ae
#define ISO_8859_1_E7   0                                       // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   KEY_LEFT_BRACE                          // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   KEY_SLASH                               // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_5 + ALTGR_MASK                      //     â‚¬     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_5 + ALTGR_MASK                      // 20AC â‚¬    Euro Sign

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_ICELANDIC

#ifdef LAYOUT_TURKISH
// http://forum.pjrc.com/threads/18781-Turkish-Language-Support

#define DEADKEY_CIRCUMFLEX      KEY_3 + SHIFT_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_SEMICOLON + ALTGR_MASK
#define DEADKEY_GRAVE_ACCENT    KEY_BACKSLASH + ALTGR_MASK
#define DEADKEY_TILDE           KEY_RIGHT_BRACE + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_LEFT_BRACE + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_TILDE                               // 34 "
#define ASCII_23        KEY_3 + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_4 + ALTGR_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_2 + SHIFT_MASK                      // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_MINUS                               // 42 *
#define ASCII_2B        KEY_4 + SHIFT_MASK                      // 43 +
#define ASCII_2C        KEY_BACKSLASH                           // 44 ,
#define ASCII_2D        KEY_EQUAL                               // 45 -
#define ASCII_2E        KEY_SLASH                               // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SLASH + SHIFT_MASK                  // 58 :
#define ASCII_3B        KEY_BACKSLASH + SHIFT_MASK              // 59 ;
#define ASCII_3C        KEY_TILDE + ALTGR_MASK                  // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_1 + ALTGR_MASK                      // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_Q + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_8 + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_MINUS + ALTGR_MASK                  // 92
#define ASCII_5D        KEY_9 + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_EQUAL + SHIFT_MASK                  // 95 _
#define ASCII_60        GRAVE_ACCENT_BITS + KEY_SPACE           // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_QUOTE                               // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_7 + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_EQUAL + ALTGR_MASK                  // 124 |
#define ASCII_7D        KEY_0 + ALTGR_MASK                      // 125 }
#define ASCII_7E        TILDE_BITS + KEY_SPACE                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent SIGN
#define ISO_8859_1_A3   KEY_2 + ALTGR_MASK                      // 163 Â£     Pound Sign
#define ISO_8859_1_A4   0                                       // 164 Â¤     Currency or Euro Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR                        ??
#define ISO_8859_1_A7   0                                       // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN                  ??
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   0                                       // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   0                                       // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   KEY_5 + ALTGR_MASK                      // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   GRAVE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   TILDE_BITS + KEY_A + SHIFT_MASK         // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   KEY_A + ALTGR_MASK                      // 198 Ã†     AE
#define ISO_8859_1_C7   KEY_PERIOD + SHIFT_MASK                 // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   TILDE_BITS + KEY_N + SHIFT_MASK         // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   TILDE_BITS + KEY_O + SHIFT_MASK         // 213 Ã•     O TILDE
#define ISO_8859_1_D6   KEY_COMMA + SHIFT_MASK                  // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   0                                       // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   KEY_RIGHT_BRACE + SHIFT_MASK            // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Y + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_S + ALTGR_MASK                      // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   GRAVE_ACCENT_BITS + KEY_A               // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   TILDE_BITS + KEY_A                      // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   KEY_PERIOD                              // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   GRAVE_ACCENT_BITS + KEY_E               // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_TILDE + SHIFT_MASK                  // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   GRAVE_ACCENT_BITS + KEY_I               // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   TILDE_BITS + KEY_N                      // 241 Ã±     n TILDE
#define ISO_8859_1_F2   GRAVE_ACCENT_BITS + KEY_O               // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   TILDE_BITS + KEY_O                      // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   KEY_COMMA                               // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   0                                       // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   GRAVE_ACCENT_BITS + KEY_U               // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   KEY_RIGHT_BRACE                         // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Y               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   DIAERESIS_BITS + KEY_Y                  // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign

// not yet implemented
#define UNICODE_EXTRA00 0x20AC
#define KEYCODE_EXTRA00 KEY_E + ALTGR_MASK                      // 20AC â‚¬    Euro Sign
#define UNICODE_EXTRA01 0x011E
#define KEYCODE_EXTRA01 KEY_LEFT_BRACE + SHIFT_MASK             // 011E Äž    Latin capital letter G with breve
#define UNICODE_EXTRA02 0x011F
#define KEYCODE_EXTRA02 KEY_LEFT_BRACE                          // 011F ÄŸ    Latin small letter g with breve
#define UNICODE_EXTRA03 0x0130
#define KEYCODE_EXTRA03 KEY_QUOTE + SHIFT_MASK                  // 0130 Ä°    Latin captial letter I with dot above
#define UNICODE_EXTRA04 0x0131
#define KEYCODE_EXTRA04 KEY_I                                   // 0131 Ä±    Latin small letter dotless i
#define UNICODE_EXTRA05 0x015E
#define KEYCODE_EXTRA05 KEY_SEMICOLON + SHIFT_MASK              // 015E Åž    Latin capital letter S with cedilla
#define UNICODE_EXTRA06 0x0151
#define KEYCODE_EXTRA06 KEY_SEMICOLON                           // 0151 ÅŸ    Latin small letter s with cedilla

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_TURKISH

#ifdef LAYOUT_CZECH
// http://forum.pjrc.com/threads/24495-Czech-keyboard

#define DEADKEY_ACUTE_ACCENT    KEY_EQUAL  // TODO: is it KEY_9 + ALTGR_MASK
#define DEADKEY_DEGREE_SIGN     KEY_TILDE + SHIFT_MASK // TODO: is it KEY_5 + ALTGR_MASK
#define DEADKEY_CARON           KEY_EQUAL + SHIFT_MASK // TODO: is it KEY_2 + ALTGR_MASK
//#define DEADKEY_CIRCUMFLEX    KEY_3 + ALTGR_MASK
#define DEADKEY_BREVE           KEY_4 + ALTGR_MASK
#define DEADKEY_OGONEK          KEY_6 + ALTGR_MASK
//#define DEADKEY_GRAVE_ACCENT  KEY_7 + ALTGR_MASK
#define DEADKEY_DOT_ABOVE       KEY_8 + ALTGR_MASK
#define DEADKEY_DOUBLE_ACUTE    KEY_0 + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_MINUS + ALTGR_MASK
#define DEADKEY_CEDILLA         KEY_EQUAL + ALTGR_MASK

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_QUOTE + SHIFT_MASK                  // 33 !
#define ASCII_22        KEY_SEMICOLON + SHIFT_MASK              // 34 "
#define ASCII_23        KEY_X + ALTGR_MASK                      // 35 #
#define ASCII_24        KEY_SEMICOLON + ALTGR_MASK              // 36 $
#define ASCII_25        KEY_MINUS + SHIFT_MASK                  // 37 %
#define ASCII_26        KEY_C + ALTGR_MASK                      // 38 &
#define ASCII_27        KEY_BACKSLASH + SHIFT_MASK              // 39 '
#define ASCII_28        KEY_RIGHT_BRACE + SHIFT_MASK            // 40 (
#define ASCII_29        KEY_RIGHT_BRACE                         // 41 )
#define ASCII_2A        KEY_SLASH + ALTGR_MASK                  // 42 *
#define ASCII_2B        KEY_1                                   // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_LEFT_BRACE + SHIFT_MASK             // 47 /
#define ASCII_30        KEY_0 + SHIFT_MASK                      // 48 0
#define ASCII_31        KEY_1 + SHIFT_MASK                      // 49 1
#define ASCII_32        KEY_2 + SHIFT_MASK                      // 50 2
#define ASCII_33        KEY_3 + SHIFT_MASK                      // 51 3
#define ASCII_34        KEY_4 + SHIFT_MASK                      // 52 4
#define ASCII_35        KEY_5 + SHIFT_MASK                      // 53 5
#define ASCII_36        KEY_6 + SHIFT_MASK                      // 54 6
#define ASCII_37        KEY_7 + SHIFT_MASK                      // 55 7
#define ASCII_38        KEY_8 + SHIFT_MASK                      // 55 8
#define ASCII_39        KEY_9 + SHIFT_MASK                      // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_TILDE                               // 59 ;
#define ASCII_3C        KEY_COMMA + ALTGR_MASK                  // 60 <
#define ASCII_3D        KEY_MINUS                               // 61 =
#define ASCII_3E        KEY_PERIOD + ALTGR_MASK                 // 62 >
#define ASCII_3F        KEY_COMMA + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_V + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Z + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Y + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_F + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_NON_US_BS_MAPPING                          // 92
#define ASCII_5D        KEY_G + ALTGR_MASK                      // 93 ]
#define ASCII_5E        KEY_3 + ALTGR_MASK                      // 94 ^  TODO: testme
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _
#define ASCII_60        KEY_7 + ALTGR_MASK                      // 96 `  TODO: testme
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Z                                   // 121 y
#define ASCII_7A        KEY_Y                                   // 122 z
#define ASCII_7B        KEY_B + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 124 |
#define ASCII_7D        KEY_N + ALTGR_MASK                      // 125 }
#define ASCII_7E        KEY_1 + ALTGR_MASK                      // 126 ~  TODO: fixme
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   0                                       // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_BACKSLASH + ALTGR_MASK              // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_QUOTE                               // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   0                                       // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   DEGREE_SIGN_BITS + KEY_SPACE            // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   CEDILLA_BITS + KEY_SPACE                // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   0                                       // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   0                                       // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   0                                       // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   CEDILLA_BITS + KEY_C + SHIFT_MASK       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   0                                       // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   0                                       // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   0                                       // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   0                                       // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   0                                       // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   0                                       // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   0                                       // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   0                                       // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   0                                       // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   KEY_RIGHT_BRACE + ALTGR_MASK            // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   0                                       // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   0                                       // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   0                                       // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Z + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_QUOTE + ALTGR_MASK                  // 223 ÃŸ     SHARP S  TODO: testme
#define ISO_8859_1_E0   0                                       // 224 Ã      a GRAVE
#define ISO_8859_1_E1   KEY_8                                   // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   0                                       // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   0                                       // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   CEDILLA_BITS + KEY_C                    // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   0                                       // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   KEY_0                                   // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   0                                       // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   0                                       // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   0                                       // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   KEY_9                                   // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   0                                       // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   0                                       // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   0                                       // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   0                                       // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   0                                       // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   KEY_LEFT_BRACE + ALTGR_MASK             // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   0                                       // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   KEY_LEFT_BRACE                          // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   0                                       // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   0                                       // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   KEY_7                                   // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   0                                       // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign

#define UNICODE_EXTRA00 0x011B  // Ä›  Small Letter E with caron
#define KEYCODE_EXTRA00 KEY_2
#define UNICODE_EXTRA01 0x0161  // Å¡  Small Letter S with caron
#define KEYCODE_EXTRA01 KEY_3
#define UNICODE_EXTRA02 0x010D  // Ä�  Small Letter C with caron
#define KEYCODE_EXTRA02 KEY_4
#define UNICODE_EXTRA03 0x0159  // Å™  Small Letter R with caron
#define KEYCODE_EXTRA03 KEY_5
#define UNICODE_EXTRA04 0x017E  // Å¾  Small Letter Z with caron
#define KEYCODE_EXTRA04 KEY_6
#define UNICODE_EXTRA05 0x016F  // Å¯  Small Letter U with ring above
#define KEYCODE_EXTRA05 KEY_SEMICOLON
#define UNICODE_EXTRA06 0x0111  // Ä‘  Small Letter D with stroke
#define KEYCODE_EXTRA06 KEY_S + ALTGR_MASK
#define UNICODE_EXTRA07 0x0110  // Ä�  Capital Letter D with stroke
#define KEYCODE_EXTRA07 KEY_D + ALTGR_MASK
#define UNICODE_EXTRA08 0x0142  // Å‚  Small Letter L with stroke
#define KEYCODE_EXTRA08 KEY_K + ALTGR_MASK
#define UNICODE_EXTRA09 0x0141  // Å�  Capital Letter L with stroke
#define KEYCODE_EXTRA09 KEY_L + ALTGR_MASK
#define UNICODE_EXTRA0A 0x20AC  // â‚¬  Euro Sign
#define KEYCODE_EXTRA0A KEY_E + ALTGR_MASK

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_CZECH

#ifdef LAYOUT_SERBIAN_LATIN_ONLY
// http://forum.pjrc.com/threads/27032-Serbian-Keyboard-Layout

#define DEADKEY_CEDILLA         KEY_TILDE
#define DEADKEY_CARON           KEY_2 + ALTGR_MASK
#define DEADKEY_CIRCUMFLEX      KEY_3 + ALTGR_MASK
#define DEADKEY_BREVE           KEY_4 + ALTGR_MASK
#define DEADKEY_DEGREE_SIGN     KEY_5 + ALTGR_MASK
#define DEADKEY_OGONEK          KEY_6 + ALTGR_MASK
#define DEADKEY_DOT_ABOVE       KEY_8 + ALTGR_MASK
#define DEADKEY_ACUTE_ACCENT    KEY_9 + ALTGR_MASK
#define DEADKEY_DOUBLE_ACUTE    KEY_0 + ALTGR_MASK
#define DEADKEY_DIAERESIS       KEY_MINUS + ALTGR_MASK
//#define DEADKEY_CEDILLA       KEY_EQUAL + ALTGR_MASK <-- TODO: why are there 2 Cedilla deadkeys?

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_2 + SHIFT_MASK                      // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_6 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_MINUS                               // 39 '
#define ASCII_28        KEY_8 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_9 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_EQUAL + SHIFT_MASK                  // 42 *
#define ASCII_2B        KEY_EQUAL                               // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_SLASH                               // 45 -  TODO: verify
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_7 + SHIFT_MASK                      // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_PERIOD + SHIFT_MASK                 // 58 :
#define ASCII_3B        KEY_COMMA + SHIFT_MASK                  // 59 ;
#define ASCII_3C        KEY_NON_US_BS_MAPPING                          // 60 <
#define ASCII_3D        KEY_0 + SHIFT_MASK                      // 61 =
#define ASCII_3E        KEY_NON_US_BS_MAPPING + SHIFT_MASK             // 62 >
#define ASCII_3F        KEY_MINUS + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_V + ALTGR_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Z + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Y + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_F + ALTGR_MASK                      // 91 [
#define ASCII_5C        KEY_Q + ALTGR_MASK                      // 92
#define ASCII_5D        KEY_G + ALTGR_MASK                      // 93 ]
#define ASCII_5E        CIRCUMFLEX_BITS + KEY_SPACE             // 94 ^
#define ASCII_5F        KEY_SLASH + SHIFT_MASK                  // 95 _   TODO: verify
#define ASCII_60        KEY_7 + ALTGR_MASK                      // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Z                                   // 121 y
#define ASCII_7A        KEY_Y                                   // 122 z
#define ASCII_7B        KEY_B + ALTGR_MASK                      // 123 {
#define ASCII_7C        KEY_W + ALTGR_MASK                      // 124 |
#define ASCII_7D        KEY_N + ALTGR_MASK                      // 125 }
#define ASCII_7E        KEY_1 + ALTGR_MASK                      // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127
#define ISO_8859_1_A0   KEY_SPACE                               // 160       Nonbreakng Space
#define ISO_8859_1_A1   0                                       // 161 Â¡     Inverted Exclamation
#define ISO_8859_1_A2   0                                       // 162 Â¢     Cent Sign
#define ISO_8859_1_A3   0                                       // 163 Â£     Pound Sign
#define ISO_8859_1_A4   KEY_BACKSLASH + ALTGR_MASK              // 164 Â¤     Currency Sign
#define ISO_8859_1_A5   0                                       // 165 Â¥     YEN SIGN
#define ISO_8859_1_A6   0                                       // 166 Â¦     BROKEN BAR
#define ISO_8859_1_A7   KEY_M + ALTGR_MASK                      // 167 Â§     SECTION SIGN
#define ISO_8859_1_A8   DIAERESIS_BITS + KEY_SPACE              // 168 Â¨     DIAERESIS
#define ISO_8859_1_A9   0                                       // 169 Â©     COPYRIGHT SIGN
#define ISO_8859_1_AA   0                                       // 170 Âª     FEMININE ORDINAL
#define ISO_8859_1_AB   0                                       // 171 Â«     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC   0                                       // 172 Â¬     NOT SIGN
#define ISO_8859_1_AD   0                                       // 173       SOFT HYPHEN
#define ISO_8859_1_AE   0                                       // 174 Â®     REGISTERED SIGN
#define ISO_8859_1_AF   0                                       // 175 Â¯     MACRON
#define ISO_8859_1_B0   DEGREE_SIGN_BITS + KEY_SPACE            // 176 Â°     DEGREE SIGN
#define ISO_8859_1_B1   0                                       // 177 Â±     PLUS-MINUS SIGN
#define ISO_8859_1_B2   0                                       // 178 Â²     SUPERSCRIPT TWO
#define ISO_8859_1_B3   0                                       // 179 Â³     SUPERSCRIPT THREE
#define ISO_8859_1_B4   ACUTE_ACCENT_BITS + KEY_SPACE           // 180 Â´     ACUTE ACCENT
#define ISO_8859_1_B5   0                                       // 181 Âµ     MICRO SIGN
#define ISO_8859_1_B6   0                                       // 182 Â¶     PILCROW SIGN
#define ISO_8859_1_B7   0                                       // 183 Â·     MIDDLE DOT
#define ISO_8859_1_B8   CEDILLA_BITS + KEY_SPACE                // 184 Â¸     CEDILLA
#define ISO_8859_1_B9   0                                       // 185 Â¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA   0                                       // 186 Âº     MASCULINE ORDINAL
#define ISO_8859_1_BB   0                                       // 187 Â»     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC   0                                       // 188 Â¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD   0                                       // 189 Â½     FRACTION ONE HALF
#define ISO_8859_1_BE   0                                       // 190 Â¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF   0                                       // 191 Â¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0   0                                       // 192 Ã€     A GRAVE
#define ISO_8859_1_C1   ACUTE_ACCENT_BITS + KEY_A + SHIFT_MASK  // 193 Ã�     A ACUTE
#define ISO_8859_1_C2   CIRCUMFLEX_BITS + KEY_A + SHIFT_MASK    // 194 Ã‚     A CIRCUMFLEX
#define ISO_8859_1_C3   0                                       // 195 Ãƒ     A TILDE
#define ISO_8859_1_C4   DIAERESIS_BITS + KEY_A + SHIFT_MASK     // 196 Ã„     A DIAERESIS
#define ISO_8859_1_C5   0                                       // 197 Ã…     A RING ABOVE
#define ISO_8859_1_C6   0                                       // 198 Ã†     AE
#define ISO_8859_1_C7   CEDILLA_BITS + KEY_C + SHIFT_MASK       // 199 Ã‡     C CEDILLA
#define ISO_8859_1_C8   0                                       // 200 Ãˆ     E GRAVE
#define ISO_8859_1_C9   ACUTE_ACCENT_BITS + KEY_E + SHIFT_MASK  // 201 Ã‰     E ACUTE
#define ISO_8859_1_CA   CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK    // 202 ÃŠ     E CIRCUMFLEX
#define ISO_8859_1_CB   DIAERESIS_BITS + KEY_E + SHIFT_MASK     // 203 Ã‹     E DIAERESIS
#define ISO_8859_1_CC   0                                       // 204 ÃŒ     I GRAVE
#define ISO_8859_1_CD   ACUTE_ACCENT_BITS + KEY_I + SHIFT_MASK  // 205 Ã�     I ACUTE
#define ISO_8859_1_CE   CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK    // 206 ÃŽ     I CIRCUMFLEX
#define ISO_8859_1_CF   DIAERESIS_BITS + KEY_I + SHIFT_MASK     // 207 Ã�     I DIAERESIS
#define ISO_8859_1_D0   0                                       // 208 Ã�     ETH
#define ISO_8859_1_D1   0                                       // 209 Ã‘     N TILDE
#define ISO_8859_1_D2   0                                       // 210 Ã’     O GRAVE
#define ISO_8859_1_D3   ACUTE_ACCENT_BITS + KEY_O + SHIFT_MASK  // 211 Ã“     O ACUTE
#define ISO_8859_1_D4   CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK    // 212 Ã”     O CIRCUMFLEX
#define ISO_8859_1_D5   0                                       // 213 Ã•     O TILDE
#define ISO_8859_1_D6   DIAERESIS_BITS + KEY_O + SHIFT_MASK     // 214 Ã–     O DIAERESIS
#define ISO_8859_1_D7   KEY_RIGHT_BRACE + ALTGR_MASK            // 215 Ã—     MULTIPLICATION
#define ISO_8859_1_D8   0                                       // 216 Ã˜     O STROKE
#define ISO_8859_1_D9   0                                       // 217 Ã™     U GRAVE
#define ISO_8859_1_DA   ACUTE_ACCENT_BITS + KEY_U + SHIFT_MASK  // 218 Ãš     U ACUTE
#define ISO_8859_1_DB   CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK    // 219 Ã›     U CIRCUMFLEX
#define ISO_8859_1_DC   DIAERESIS_BITS + KEY_U + SHIFT_MASK     // 220 Ãœ     U DIAERESIS
#define ISO_8859_1_DD   ACUTE_ACCENT_BITS + KEY_Z + SHIFT_MASK  // 221 Ã�     Y ACUTE
#define ISO_8859_1_DE   0                                       // 222 Ãž     THORN
#define ISO_8859_1_DF   KEY_QUOTE + ALTGR_MASK                  // 223 ÃŸ     SHARP S
#define ISO_8859_1_E0   0                                       // 224 Ã      a GRAVE
#define ISO_8859_1_E1   ACUTE_ACCENT_BITS + KEY_A               // 225 Ã¡     a ACUTE
#define ISO_8859_1_E2   CIRCUMFLEX_BITS + KEY_A                 // 226 Ã¢     a CIRCUMFLEX
#define ISO_8859_1_E3   0                                       // 227 Ã£     a TILDE
#define ISO_8859_1_E4   DIAERESIS_BITS + KEY_A                  // 228 Ã¤     a DIAERESIS
#define ISO_8859_1_E5   0                                       // 229 Ã¥     a RING ABOVE
#define ISO_8859_1_E6   0                                       // 230 Ã¦     ae
#define ISO_8859_1_E7   CEDILLA_BITS + KEY_C                    // 231 Ã§     c CEDILLA
#define ISO_8859_1_E8   0                                       // 232 Ã¨     e GRAVE
#define ISO_8859_1_E9   ACUTE_ACCENT_BITS + KEY_E               // 233 Ã©     e ACUTE
#define ISO_8859_1_EA   CIRCUMFLEX_BITS + KEY_E                 // 234 Ãª     e CIRCUMFLEX
#define ISO_8859_1_EB   DIAERESIS_BITS + KEY_E                  // 235 Ã«     e DIAERESIS
#define ISO_8859_1_EC   0                                       // 236 Ã¬     i GRAVE
#define ISO_8859_1_ED   ACUTE_ACCENT_BITS + KEY_I               // 237 Ã­     i ACUTE
#define ISO_8859_1_EE   CIRCUMFLEX_BITS + KEY_I                 // 238 Ã®     i CIRCUMFLEX
#define ISO_8859_1_EF   DIAERESIS_BITS + KEY_I                  // 239 Ã¯     i DIAERESIS
#define ISO_8859_1_F0   0                                       // 240 Ã°     ETH
#define ISO_8859_1_F1   0                                       // 241 Ã±     n TILDE
#define ISO_8859_1_F2   0                                       // 242 Ã²     o GRAVE
#define ISO_8859_1_F3   ACUTE_ACCENT_BITS + KEY_O               // 243 Ã³     o ACUTE
#define ISO_8859_1_F4   CIRCUMFLEX_BITS + KEY_O                 // 244 Ã´     o CIRCUMFLEX
#define ISO_8859_1_F5   0                                       // 245 Ãµ     o TILDE
#define ISO_8859_1_F6   DIAERESIS_BITS + KEY_O                  // 246 Ã¶     o DIAERESIS
#define ISO_8859_1_F7   KEY_LEFT_BRACE + ALTGR_MASK             // 247 Ã·     DIVISION
#define ISO_8859_1_F8   0                                       // 248 Ã¸     o STROKE
#define ISO_8859_1_F9   0                                       // 249 Ã¹     u GRAVE
#define ISO_8859_1_FA   ACUTE_ACCENT_BITS + KEY_U               // 250 Ãº     u ACUTE
#define ISO_8859_1_FB   CIRCUMFLEX_BITS + KEY_U                 // 251 Ã»     u CIRCUMFLEX
#define ISO_8859_1_FC   DIAERESIS_BITS + KEY_U                  // 252 Ã¼     u DIAERESIS
#define ISO_8859_1_FD   ACUTE_ACCENT_BITS + KEY_Z               // 253 Ã½     y ACUTE
#define ISO_8859_1_FE   0                                       // 254 Ã¾     THORN
#define ISO_8859_1_FF   0                                       // 255 Ã¿     y DIAERESIS
#define UNICODE_20AC    KEY_E + ALTGR_MASK                      //     â‚¬     Euro Sign

#define UNICODE_EXTRA00 0x0160 // S caron
#define KEYCODE_EXTRA00 KEY_LEFT_BRACE + SHIFT_MASK
#define UNICODE_EXTRA01 0x0161 // s caron
#define KEYCODE_EXTRA01 KEY_LEFT_BRACE
#define UNICODE_EXTRA02 0x0110 // D with stroke
#define KEYCODE_EXTRA02 KEY_RIGHT_BRACE + SHIFT_MASK
#define UNICODE_EXTRA03 0x0111 // d with stroke
#define KEYCODE_EXTRA03 KEY_RIGHT_BRACE
#define UNICODE_EXTRA04 0x010C // C with caron
#define KEYCODE_EXTRA04 KEY_SEMICOLON + SHIFT_MASK
#define UNICODE_EXTRA05 0x010D // c with caron
#define KEYCODE_EXTRA05 KEY_SEMICOLON
#define UNICODE_EXTRA06 0x0106 // C with acute
#define KEYCODE_EXTRA06 KEY_QUOTE + SHIFT_MASK
#define UNICODE_EXTRA07 0x0107 // c with acute
#define KEYCODE_EXTRA07 KEY_QUOTE
#define UNICODE_EXTRA08 0x017D // Z with caron
#define KEYCODE_EXTRA08 KEY_BACKSLASH + SHIFT_MASK
#define UNICODE_EXTRA09 0x017E // z with caron
#define KEYCODE_EXTRA09 KEY_BACKSLASH

#define UNICODE_EXTRA10 0x0141 // L with stroke
#define KEYCODE_EXTRA10 KEY_L + ALTGR_MASK
#define UNICODE_EXTRA11 0x0142 // l with stroke
#define KEYCODE_EXTRA11 KEY_K + ALTGR_MASK
#define UNICODE_EXTRA12 0x010E // D with caron
#define KEYCODE_EXTRA12 CARON_BITS + KEY_D + SHIFT_MASK
#define UNICODE_EXTRA13 0x010F // d with caron
#define KEYCODE_EXTRA13 CARON_BITS + KEY_D
#define UNICODE_EXTRA14 0x011A // E with caron
#define KEYCODE_EXTRA14 CARON_BITS + KEY_E + SHIFT_MASK
#define UNICODE_EXTRA15 0x011B // e with caron
#define KEYCODE_EXTRA15 CARON_BITS + KEY_E
#define UNICODE_EXTRA16 0x013D // L with caron
#define KEYCODE_EXTRA16 CARON_BITS + KEY_L + SHIFT_MASK
#define UNICODE_EXTRA17 0x013E // l with caron
#define KEYCODE_EXTRA17 CARON_BITS + KEY_L
#define UNICODE_EXTRA18 0x0147 // N with caron
#define KEYCODE_EXTRA18 CARON_BITS + KEY_N + SHIFT_MASK
#define UNICODE_EXTRA19 0x0148 // n with caron
#define KEYCODE_EXTRA19 CARON_BITS + KEY_N

#define UNICODE_EXTRA20 0x0158 // R with caron
#define KEYCODE_EXTRA20 CARON_BITS + KEY_R + SHIFT_MASK
#define UNICODE_EXTRA21 0x0159 // r with caron
#define KEYCODE_EXTRA21 CARON_BITS + KEY_R
#define UNICODE_EXTRA22 0x0164 // T with caron
#define KEYCODE_EXTRA22 CARON_BITS + KEY_T + SHIFT_MASK
#define UNICODE_EXTRA23 0x0165 // t with caron
#define KEYCODE_EXTRA23 CARON_BITS + KEY_T
#define UNICODE_EXTRA24 0x0102 // A with breve
#define KEYCODE_EXTRA24 BREVE_BITS + KEY_A + SHIFT_MASK
#define UNICODE_EXTRA25 0x0103 // a with breve
#define KEYCODE_EXTRA25 BREVE_BITS + KEY_A
#define UNICODE_EXTRA26 0x016E // U with ring above  TODO: verify
#define KEYCODE_EXTRA26 DEADKEY_DEGREE_SIGN + KEY_U + SHIFT_MASK
#define UNICODE_EXTRA27 0x016F // u with ring above  TODO: verify
#define KEYCODE_EXTRA27 DEADKEY_DEGREE_SIGN + KEY_U
#define UNICODE_EXTRA28 0x0104 // A with ogonek
#define KEYCODE_EXTRA28 OGONEK_BITS + KEY_A + SHIFT_MASK
#define UNICODE_EXTRA29 0x0105 // a with ogonek
#define KEYCODE_EXTRA29 OGONEK_BITS + KEY_A

#define UNICODE_EXTRA30 0x0118 // E with ogonek
#define KEYCODE_EXTRA30 OGONEK_BITS + KEY_E + SHIFT_MASK
#define UNICODE_EXTRA31 0x0119 // e with ogonek
#define KEYCODE_EXTRA31 OGONEK_BITS + KEY_E
#define UNICODE_EXTRA32 0x017B // Z with dot above
#define KEYCODE_EXTRA32 DEADKEY_DOT_ABOVE + KEY_Z + SHIFT_MASK
#define UNICODE_EXTRA33 0x017C // z with dot above
#define KEYCODE_EXTRA33 DEADKEY_DOT_ABOVE + KEY_Z
#define UNICODE_EXTRA34 0x0139 // L with acute
#define KEYCODE_EXTRA34 ACUTE_ACCENT_BITS + KEY_L + SHIFT_MASK
#define UNICODE_EXTRA35 0x013A // l with acute
#define KEYCODE_EXTRA35 ACUTE_ACCENT_BITS + KEY_L
#define UNICODE_EXTRA36 0x0143 // N with acute
#define KEYCODE_EXTRA36 ACUTE_ACCENT_BITS + KEY_N + SHIFT_MASK
#define UNICODE_EXTRA37 0x0144 // n with acute
#define KEYCODE_EXTRA37 ACUTE_ACCENT_BITS + KEY_N
#define UNICODE_EXTRA38 0x0154 // R with acute
#define KEYCODE_EXTRA38 ACUTE_ACCENT_BITS + KEY_R + SHIFT_MASK
#define UNICODE_EXTRA39 0x0155 // r with acute
#define KEYCODE_EXTRA39 ACUTE_ACCENT_BITS + KEY_R

#define UNICODE_EXTRA40 0x015A // S with acute
#define KEYCODE_EXTRA40 ACUTE_ACCENT_BITS + KEY_S + SHIFT_MASK
#define UNICODE_EXTRA41 0x015B // s with acute
#define KEYCODE_EXTRA41 ACUTE_ACCENT_BITS + KEY_S
#define UNICODE_EXTRA42 0x0179 // Z with acute
#define KEYCODE_EXTRA42 ACUTE_ACCENT_BITS + KEY_Z + SHIFT_MASK
#define UNICODE_EXTRA43 0x017A // z with acute
#define KEYCODE_EXTRA43 ACUTE_ACCENT_BITS + KEY_Z
#define UNICODE_EXTRA44 0x0150 // O with double acute
#define KEYCODE_EXTRA44 DOUBLE_ACUTE_BITS + KEY_O + SHIFT_MASK
#define UNICODE_EXTRA45 0x0151 // o with double acute
#define KEYCODE_EXTRA45 DOUBLE_ACUTE_BITS + KEY_O
#define UNICODE_EXTRA46 0x0170 // U with double acute
#define KEYCODE_EXTRA46 DOUBLE_ACUTE_BITS + KEY_u + SHIFT_MASK
#define UNICODE_EXTRA47 0x0171 // u with double acute
#define KEYCODE_EXTRA47 DOUBLE_ACUTE_BITS + KEY_u
#define UNICODE_EXTRA48 0x015E // S with cedilla
#define KEYCODE_EXTRA48 CEDILLA_BITS + KEY_S + SHIFT_MASK
#define UNICODE_EXTRA49 0x015F // s with cedilla
#define KEYCODE_EXTRA49 CEDILLA_BITS + KEY_S

#define UNICODE_EXTRA50 0x201A // single low quote
#define KEYCODE_EXTRA50 KEY_TILDE
#define UNICODE_EXTRA51 0x20AC // euro sign
#define KEYCODE_EXTRA51 KEY_E + ALTGR_MASK

#undef LAYOUT_UNSPECIFIED
#endif // LAYOUT_SERBIAN_LATIN_ONLY

#ifdef LAYOUT_UNSPECIFIED
#warning "Using default layout (LAYOUT_US_ENGLISH)"
#endif

#if defined(LAYOUT_US_ENGLISH) || defined(LAYOUT_UNSPECIFIED)

#define ASCII_20        KEY_SPACE                               // 32
#define ASCII_21        KEY_1 + SHIFT_MASK                      // 33 !
#define ASCII_22        KEY_QUOTE + SHIFT_MASK                  // 34 "
#define ASCII_23        KEY_3 + SHIFT_MASK                      // 35 #
#define ASCII_24        KEY_4 + SHIFT_MASK                      // 36 $
#define ASCII_25        KEY_5 + SHIFT_MASK                      // 37 %
#define ASCII_26        KEY_7 + SHIFT_MASK                      // 38 &
#define ASCII_27        KEY_QUOTE                               // 39 '
#define ASCII_28        KEY_9 + SHIFT_MASK                      // 40 (
#define ASCII_29        KEY_0 + SHIFT_MASK                      // 41 )
#define ASCII_2A        KEY_8 + SHIFT_MASK                      // 42 *
#define ASCII_2B        KEY_EQUAL + SHIFT_MASK                  // 43 +
#define ASCII_2C        KEY_COMMA                               // 44 ,
#define ASCII_2D        KEY_MINUS                               // 45 -
#define ASCII_2E        KEY_PERIOD                              // 46 .
#define ASCII_2F        KEY_SLASH                               // 47 /
#define ASCII_30        KEY_0                                   // 48 0
#define ASCII_31        KEY_1                                   // 49 1
#define ASCII_32        KEY_2                                   // 50 2
#define ASCII_33        KEY_3                                   // 51 3
#define ASCII_34        KEY_4                                   // 52 4
#define ASCII_35        KEY_5                                   // 53 5
#define ASCII_36        KEY_6                                   // 54 6
#define ASCII_37        KEY_7                                   // 55 7
#define ASCII_38        KEY_8                                   // 55 8
#define ASCII_39        KEY_9                                   // 57 9
#define ASCII_3A        KEY_SEMICOLON + SHIFT_MASK              // 58 :
#define ASCII_3B        KEY_SEMICOLON                           // 59 ;
#define ASCII_3C        KEY_COMMA + SHIFT_MASK                  // 60 <
#define ASCII_3D        KEY_EQUAL                               // 61 =
#define ASCII_3E        KEY_PERIOD + SHIFT_MASK                 // 62 >
#define ASCII_3F        KEY_SLASH + SHIFT_MASK                  // 63 ?
#define ASCII_40        KEY_2 + SHIFT_MASK                      // 64 @
#define ASCII_41        KEY_A + SHIFT_MASK                      // 65 A
#define ASCII_42        KEY_B + SHIFT_MASK                      // 66 B
#define ASCII_43        KEY_C + SHIFT_MASK                      // 67 C
#define ASCII_44        KEY_D + SHIFT_MASK                      // 68 D
#define ASCII_45        KEY_E + SHIFT_MASK                      // 69 E
#define ASCII_46        KEY_F + SHIFT_MASK                      // 70 F
#define ASCII_47        KEY_G + SHIFT_MASK                      // 71 G
#define ASCII_48        KEY_H + SHIFT_MASK                      // 72 H
#define ASCII_49        KEY_I + SHIFT_MASK                      // 73 I
#define ASCII_4A        KEY_J + SHIFT_MASK                      // 74 J
#define ASCII_4B        KEY_K + SHIFT_MASK                      // 75 K
#define ASCII_4C        KEY_L + SHIFT_MASK                      // 76 L
#define ASCII_4D        KEY_M + SHIFT_MASK                      // 77 M
#define ASCII_4E        KEY_N + SHIFT_MASK                      // 78 N
#define ASCII_4F        KEY_O + SHIFT_MASK                      // 79 O
#define ASCII_50        KEY_P + SHIFT_MASK                      // 80 P
#define ASCII_51        KEY_Q + SHIFT_MASK                      // 81 Q
#define ASCII_52        KEY_R + SHIFT_MASK                      // 82 R
#define ASCII_53        KEY_S + SHIFT_MASK                      // 83 S
#define ASCII_54        KEY_T + SHIFT_MASK                      // 84 T
#define ASCII_55        KEY_U + SHIFT_MASK                      // 85 U
#define ASCII_56        KEY_V + SHIFT_MASK                      // 86 V
#define ASCII_57        KEY_W + SHIFT_MASK                      // 87 W
#define ASCII_58        KEY_X + SHIFT_MASK                      // 88 X
#define ASCII_59        KEY_Y + SHIFT_MASK                      // 89 Y
#define ASCII_5A        KEY_Z + SHIFT_MASK                      // 90 Z
#define ASCII_5B        KEY_LEFT_BRACE                          // 91 [
#define ASCII_5C        KEY_BACKSLASH                           // 92
#define ASCII_5D        KEY_RIGHT_BRACE                         // 93 ]
#define ASCII_5E        KEY_6 + SHIFT_MASK                      // 94 ^
#define ASCII_5F        KEY_MINUS + SHIFT_MASK                  // 95 _
#define ASCII_60        KEY_TILDE                               // 96 `
#define ASCII_61        KEY_A                                   // 97 a
#define ASCII_62        KEY_B                                   // 98 b
#define ASCII_63        KEY_C                                   // 99 c
#define ASCII_64        KEY_D                                   // 100 d
#define ASCII_65        KEY_E                                   // 101 e
#define ASCII_66        KEY_F                                   // 102 f
#define ASCII_67        KEY_G                                   // 103 g
#define ASCII_68        KEY_H                                   // 104 h
#define ASCII_69        KEY_I                                   // 105 i
#define ASCII_6A        KEY_J                                   // 106 j
#define ASCII_6B        KEY_K                                   // 107 k
#define ASCII_6C        KEY_L                                   // 108 l
#define ASCII_6D        KEY_M                                   // 109 m
#define ASCII_6E        KEY_N                                   // 110 n
#define ASCII_6F        KEY_O                                   // 111 o
#define ASCII_70        KEY_P                                   // 112 p
#define ASCII_71        KEY_Q                                   // 113 q
#define ASCII_72        KEY_R                                   // 114 r
#define ASCII_73        KEY_S                                   // 115 s
#define ASCII_74        KEY_T                                   // 116 t
#define ASCII_75        KEY_U                                   // 117 u
#define ASCII_76        KEY_V                                   // 118 v
#define ASCII_77        KEY_W                                   // 119 w
#define ASCII_78        KEY_X                                   // 120 x
#define ASCII_79        KEY_Y                                   // 121 y
#define ASCII_7A        KEY_Z                                   // 122 z
#define ASCII_7B        KEY_LEFT_BRACE + SHIFT_MASK             // 123 {
#define ASCII_7C        KEY_BACKSLASH + SHIFT_MASK              // 124 |
#define ASCII_7D        KEY_RIGHT_BRACE + SHIFT_MASK            // 125 }
#define ASCII_7E        KEY_TILDE + SHIFT_MASK                  // 126 ~
#define ASCII_7F        KEY_BACKSPACE                           // 127

#endif // defined(LAYOUT_US_ENGLISH) || defined(LAYOUT_UNSPECIFIED)

#ifdef M
#undef M
#endif
#define M(n) ((n) & KEYCODE_MASK)

/*
 * The mapping table in FLASH for ASCII to USB code for the enabled layout
 */
const uint8_t keycodes_ascii[]PROGMEM= {
    M(ASCII_20), M(ASCII_21), M(ASCII_22), M(ASCII_23),
    M(ASCII_24), M(ASCII_25), M(ASCII_26), M(ASCII_27),
    M(ASCII_28), M(ASCII_29), M(ASCII_2A), M(ASCII_2B),
    M(ASCII_2C), M(ASCII_2D), M(ASCII_2E), M(ASCII_2F),
    M(ASCII_30), M(ASCII_31), M(ASCII_32), M(ASCII_33),
    M(ASCII_34), M(ASCII_35), M(ASCII_36), M(ASCII_37),
    M(ASCII_38), M(ASCII_39), M(ASCII_3A), M(ASCII_3B),
    M(ASCII_3C), M(ASCII_3D), M(ASCII_3E), M(ASCII_3F),
    M(ASCII_40), M(ASCII_41), M(ASCII_42), M(ASCII_43),
    M(ASCII_44), M(ASCII_45), M(ASCII_46), M(ASCII_47),
    M(ASCII_48), M(ASCII_49), M(ASCII_4A), M(ASCII_4B),
    M(ASCII_4C), M(ASCII_4D), M(ASCII_4E), M(ASCII_4F),
    M(ASCII_50), M(ASCII_51), M(ASCII_52), M(ASCII_53),
    M(ASCII_54), M(ASCII_55), M(ASCII_56), M(ASCII_57),
    M(ASCII_58), M(ASCII_59), M(ASCII_5A), M(ASCII_5B),
    M(ASCII_5C), M(ASCII_5D), M(ASCII_5E), M(ASCII_5F),
    M(ASCII_60), M(ASCII_61), M(ASCII_62), M(ASCII_63),
    M(ASCII_64), M(ASCII_65), M(ASCII_66), M(ASCII_67),
    M(ASCII_68), M(ASCII_69), M(ASCII_6A), M(ASCII_6B),
    M(ASCII_6C), M(ASCII_6D), M(ASCII_6E), M(ASCII_6F),
    M(ASCII_70), M(ASCII_71), M(ASCII_72), M(ASCII_73),
    M(ASCII_74), M(ASCII_75), M(ASCII_76), M(ASCII_77),
    M(ASCII_78), M(ASCII_79), M(ASCII_7A), M(ASCII_7B),
    M(ASCII_7C), M(ASCII_7D), M(ASCII_7E), M(ASCII_7F)
};

#ifdef ISO_8859_1_A0
const KEYCODE_TYPE keycodes_iso_8859_1[]PROGMEM={
        M(ISO_8859_1_A0), M(ISO_8859_1_A1), M(ISO_8859_1_A2), M(ISO_8859_1_A3),
        M(ISO_8859_1_A4), M(ISO_8859_1_A5), M(ISO_8859_1_A6), M(ISO_8859_1_A7),
        M(ISO_8859_1_A8), M(ISO_8859_1_A9), M(ISO_8859_1_AA), M(ISO_8859_1_AB),
        M(ISO_8859_1_AC), M(ISO_8859_1_AD), M(ISO_8859_1_AE), M(ISO_8859_1_AF),
        M(ISO_8859_1_B0), M(ISO_8859_1_B1), M(ISO_8859_1_B2), M(ISO_8859_1_B3),
        M(ISO_8859_1_B4), M(ISO_8859_1_B5), M(ISO_8859_1_B6), M(ISO_8859_1_B7),
        M(ISO_8859_1_B8), M(ISO_8859_1_B9), M(ISO_8859_1_BA), M(ISO_8859_1_BB),
        M(ISO_8859_1_BC), M(ISO_8859_1_BD), M(ISO_8859_1_BE), M(ISO_8859_1_BF),
        M(ISO_8859_1_C0), M(ISO_8859_1_C1), M(ISO_8859_1_C2), M(ISO_8859_1_C3),
        M(ISO_8859_1_C4), M(ISO_8859_1_C5), M(ISO_8859_1_C6), M(ISO_8859_1_C7),
        M(ISO_8859_1_C8), M(ISO_8859_1_C9), M(ISO_8859_1_CA), M(ISO_8859_1_CB),
        M(ISO_8859_1_CC), M(ISO_8859_1_CD), M(ISO_8859_1_CE), M(ISO_8859_1_CF),
        M(ISO_8859_1_D0), M(ISO_8859_1_D1), M(ISO_8859_1_D2), M(ISO_8859_1_D3),
        M(ISO_8859_1_D4), M(ISO_8859_1_D5), M(ISO_8859_1_D6), M(ISO_8859_1_D7),
        M(ISO_8859_1_D8), M(ISO_8859_1_D9), M(ISO_8859_1_DA), M(ISO_8859_1_DB),
        M(ISO_8859_1_DC), M(ISO_8859_1_DD), M(ISO_8859_1_DE), M(ISO_8859_1_DF),
        M(ISO_8859_1_E0), M(ISO_8859_1_E1), M(ISO_8859_1_E2), M(ISO_8859_1_E3),
        M(ISO_8859_1_E4), M(ISO_8859_1_E5), M(ISO_8859_1_E6), M(ISO_8859_1_E7),
        M(ISO_8859_1_E8), M(ISO_8859_1_E9), M(ISO_8859_1_EA), M(ISO_8859_1_EB),
        M(ISO_8859_1_EC), M(ISO_8859_1_ED), M(ISO_8859_1_EE), M(ISO_8859_1_EF),
        M(ISO_8859_1_F0), M(ISO_8859_1_F1), M(ISO_8859_1_F2), M(ISO_8859_1_F3),
        M(ISO_8859_1_F4), M(ISO_8859_1_F5), M(ISO_8859_1_F6), M(ISO_8859_1_F7),
        M(ISO_8859_1_F8), M(ISO_8859_1_F9), M(ISO_8859_1_FA), M(ISO_8859_1_FB),
        M(ISO_8859_1_FC), M(ISO_8859_1_FD), M(ISO_8859_1_FE), M(ISO_8859_1_FF)
    };
#endif // ISO_8859_1_A0

#ifdef __cplusplus
} // extern "C"
#endif

#endif
