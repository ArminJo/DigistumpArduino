
void setup() {                
  Serial.begin(9600); 
}

// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read());
  }

}