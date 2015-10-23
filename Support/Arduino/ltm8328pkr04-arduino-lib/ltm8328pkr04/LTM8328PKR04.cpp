//
// LTM-8328PKR-04 4x7 segments display library for Arduino
// goebish 2011
//
//
#include "LTM8328PKR04.h"

// 7 segs digits pattern ( 0,1,2,3,4,5,6,7,8,9,empty,- )
const byte LTM8328PKR04::num[12]={
  		B11111100,B01100000,B11011010,
  		B11110010,B01100110,B10110110,
  		B10111110,B11100000,B11111110,
  		B11110110,B00000000,B00000010};

LTM8328PKR04::LTM8328PKR04(byte dataPin,byte clockPin)
{
	m_dataPin=dataPin;
	m_clockPin=clockPin;
  pinMode(m_dataPin, OUTPUT);
  pinMode(m_clockPin, OUTPUT);
  m_leadingZeros=false;
  clear();
}

void LTM8328PKR04::clear()
{
	pushBit(1);
	pushDigit(10);
  pushDigit(10);
  pushDigit(10);
  pushDigit(10);
  pushBit(0);
  pushBit(0);
  pushBit(0);
};

void LTM8328PKR04::print(int number)
{
  // send a "1" first
  pushBit(1);
  if( number<-999 or number>9999)
	{
    // ---- out of range
    pushDigit(11);
    pushDigit(11);
    pushDigit(11);
    pushDigit(11);
    pushBit(0);
  	pushBit(0);
  	pushBit(0);
  	return;
  }
  bool positive=number>=0;
  number=abs(number);
  if( number>999)
  {
    pushDigit(number/1000);
    pushDigit((number%1000)/100);
    pushDigit((number%100)/10);
    pushDigit(number%10);
  }
  else if( number>99)
  {
    if(positive)
    	pushDigit(m_leadingZeros?0:10);
    else
    	pushDigit(11);
    pushDigit(number/100);
    pushDigit((number%100)/10);
    pushDigit(number%10);
  }
  else if( number>9)
  {
    if(positive)
    {
    	pushDigit(m_leadingZeros?0:10);
    	pushDigit(m_leadingZeros?0:10);
    }
    else
    {
    	pushDigit(m_leadingZeros?11:10);
    	pushDigit(m_leadingZeros?0:11);
    }
    pushDigit(number/10);
    pushDigit(number%10);
  }
  else
  {
    if(positive)
    {
    	pushDigit(m_leadingZeros?0:10);
    	pushDigit(m_leadingZeros?0:10);
    	pushDigit(m_leadingZeros?0:10);
  	}
  	else
  	{
  		pushDigit(m_leadingZeros?11:10);
  		pushDigit(m_leadingZeros?0:10);
  		pushDigit(m_leadingZeros?0:11);
  	}
    pushDigit(number);
  }  
  // then send 3 other bits (2 external leds + 1 final latch clock)
  pushBit(0);
  pushBit(0);
  pushBit(0);
}

void LTM8328PKR04::pushDigit(int digit,bool decimal)
{
  for(int segment=7;segment!=0;segment--)
    pushBit((num[digit]>>segment)&1);
  pushBit(decimal);
}

void LTM8328PKR04::pushBit(bool state)
{
  digitalWrite(m_dataPin, state ? HIGH : LOW);
  digitalWrite(m_clockPin, HIGH);
  digitalWrite(m_clockPin, LOW);
}
