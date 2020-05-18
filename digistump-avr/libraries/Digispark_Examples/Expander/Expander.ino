#include <Wire.h>
#define expander 0x20

byte expanderStatus = B11111111; //all off

void setup()
{
    Wire.begin();
}

void loop()
{
    expanderWrite(0,HIGH);
    delay(1000);
    expanderWrite(0,LOW);
    delay(1000);
}


void expanderWrite(byte pinNumber, boolean state){
  if(state == HIGH)
    expanderStatus &= ~(1 << pinNumber);
  else
    expanderStatus |= (1 << pinNumber); 
    
  expanderWrite(expanderStatus);
}

void expanderWrite(byte _data ) {
  Wire.beginTransmission(expander);
  Wire.send(_data);
  Wire.endTransmission();
}
