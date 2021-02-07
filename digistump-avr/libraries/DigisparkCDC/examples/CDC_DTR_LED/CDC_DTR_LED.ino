/******************************************************************************
 * Attention!
 * This example likely will not work with 
 * windows versions > XP and current Linux kernels
 * see: http://digistump.com/board/index.php/topic,2720.msg13422.html#msg13422
 ******************************************************************************/
 #include <DigiCDC.h>
void setup() {                
  SerialUSB.begin();
  // initialize the digital pin 1 as an DTR output.
  SerialUSB.setDtrPin(1);
}

// the loop routine runs over and over again forever:
void loop() {
   SerialUSB.delay(10);
}
