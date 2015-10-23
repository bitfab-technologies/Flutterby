// LTM8328PKR04 counter example
// goebish 2011
//
// LTM8328PKR04 pins 3 & 8  --> to ground
// LTM8328PKR04 pin 4 (data) --> to Arduino pin 8 
// LTM8328PKR04 pin 5 (clock) --> to Arduino pin 9
// LTM8328PKR04 pin 6 (Vcc) --> to +5V
// LTM8328PKR04 pin 7 (dimmer) --> to +5V via 10kOhm resistor + 1nF capacitor if flickering occurs
// LTM8328PKR04 pin 9 (VLeds) --> to +3.3V

#include <LTM8328PKR04.h>

const byte dataPin = 8;
const byte clockPin = 9;

LTM8328PKR04 counter(dataPin,clockPin);
int kCount = -999;

void setup()
{
   pinMode(13, OUTPUT);
}

void loop()
{
  if (kCount > 9999)
  {
     kCount = -999; 
  }
     
  digitalWrite(13, HIGH);
  counter.print(kCount);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  
  kCount++;
}
