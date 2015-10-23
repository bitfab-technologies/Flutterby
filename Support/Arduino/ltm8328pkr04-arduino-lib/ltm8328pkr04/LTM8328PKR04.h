#ifndef LTM8328PKR04_H_
#define LTM8328PKR04_H_

#include <WProgram.h>

class LTM8328PKR04
{
	public:
		LTM8328PKR04(byte dataPin,byte clockPin);
		void setLeadingZeros(bool value=true){m_leadingZeros=value;}
		void clear();
		void print(int number);
	private:
		void pushDigit(int digit,bool decimal=false);
		void pushBit(bool state);
		byte m_dataPin,m_clockPin;
		bool m_leadingZeros;
		static const byte num[12];
};

#endif