// I2C Scanner
// Written by Nick Gammon
// Date: 20th April 2011
/*
  จากบทความ ค้นหา Address I2C ด้วย Arduino กันเถอะ
  https://www.9arduino.com/article/69/
*/
 
#include <Wire.h>
void setup() {

  Serial.begin (9600);
  // Leonardo: wait for serial port to connect
  while (!Serial) 
    {
    }

  Serial.println ();
  Serial.println ("www.9arduino.com ...");
  Serial.println ("I2C scanner. Scanning ...");

  
}

void loop() {
  
  byte count = 0;
  Wire.begin();
  for (byte i = 8; i < 120; i++)  // Loop ค้นหา Address 
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1); 
      } 
  } 
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  delay(1000);
 }
