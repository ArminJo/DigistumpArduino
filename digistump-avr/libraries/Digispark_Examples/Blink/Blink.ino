#include <Arduino.h>

// the setup routine runs once when you press reset:
void setup() {
    // initialize the digital pin as an output.
    pinMode(0, OUTPUT); //LED on MH-ET LIVE Tiny88 or Model B - Never seen Model B in the wild
    pinMode(LED_BUILTIN, OUTPUT); //LED on Model A or Pro
}

// the loop routine runs over and over again forever:
// If you only see short flashes, you own a Model B Or you have an MH-ET LIVE Tiny88 board
void loop() {
    digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);               // wait for 100 ms
    digitalWrite(0, LOW);     // turn the Model B LED off by making the voltage LOW
    delay(900);               // wait for a second
    digitalWrite(LED_BUILTIN, LOW); // turn the Model A or Pro LED off by making the voltage LOW
    delay(1000);              // wait for a second
}
