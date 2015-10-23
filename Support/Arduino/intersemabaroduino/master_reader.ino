// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <stdarg.h>
#include "intersemabaro.h"

void p(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}

Intersema::BaroPressure_MS5534B baro(false);

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  baro.begin();
}

void loop()                     
{  
  const uint32_t altitude = baro.getHeightCentiMeters();
  const uint32_t temp = baro.getTemperatureCelsius();
  Serial.print(altitude / 100, DEC);
  Serial.print(".");
  Serial.print(altitude % 100, DEC);
  Serial.println("m");
  Serial.print(temp, DEC);
  Serial.println(" deg.C");
  delay(2000);
}
