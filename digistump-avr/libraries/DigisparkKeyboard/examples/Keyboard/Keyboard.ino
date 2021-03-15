/*
 * Comment out the line for your layout
 */

//#define LAYOUT_US_ENGLISH // Is default
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
#include "DigiKeyboard.h"

void setup() {
    DigiKeyboard.enableLEDFeedback();
}

// The loop function is called in an endless loop
void loop() {

    // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
    // if doing keyboard stuff because it keeps talking to the computer to make
    // sure the computer knows the keyboard is alive and connected
    DigiKeyboard.delay(5000);

    // this is generally not necessary but with some older systems it seems to
    // prevent missing the first character after a delay:
//    DigiKeyboard.sendKeyDEStroke(0);

    DigiKeyboard.print("Hello Digispark!");
    DigiKeyboard.write('\n');
    //    DigiKeyboard.println(F("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"));
    DigiKeyboard.println(TEST_STRING);

    // Send all ASCII codes in a loop
//    for (uint8_t tSendChar = 0x20; tSendChar < 0x7F; ++tSendChar) {
//        DigiKeyboard.write(tSendChar);
//        DigiKeyboard.delay(50);
//    }
//    DigiKeyboard.write('\n');
}
