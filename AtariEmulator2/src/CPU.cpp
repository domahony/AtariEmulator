/*
 * CPU.cpp
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ADC.h"

namespace cpu {

CPU::CPU(int hz, int refresh_rate) : acc(0), hz(hz), refresh_rate(refresh_rate), clock(hz), op(255), wait(0) {

	unsigned char low = read(0xFFFc);
	unsigned char high = read(0xFFFc + 1);

	PC = (high << 8) + low;

	op[0x69] = new ADC<Immediate>();
	op[0x65] = new ADC<ZeroPage>();
	op[0x75] = new ADC<ZeroPageWithXIdx>();
	op[0x62] = new ADC<Absolute>();
	op[0x7D] = new ADC<AbsoluteWithX>();
	op[0x79] = new ADC<AbsoluteWithY>();
	op[0x61] = new ADC<ZpIdxIndirect>();
	op[0x71] = new ADC<ZpIndirectIdxWithY>();

}

CPU::~CPU() {
}

int CPU::
_execute()
{
	unsigned char opcode = read(PC++);
	return (*op[0x69])(this);
}

double CPU::
ticks_per_second()
{
	return clock.ticks_per_second();
}

bool CPU::
execute()
{
	while (acc < hz) {
		acc += refresh_rate;
		clock.tick();

		if (--wait <= 0) {
			wait = _execute();
		}
	}

	acc %= hz;

	return true;

	/*
	while(1) // repeat forever
	{
	  acc += 115200;
	  if(acc>=2000000) printf("*"); else printf(" ");

	  acc %= 2000000;
	}
	*/
}

unsigned char CPU::
read(unsigned short addr) const {
	return 0;
}

unsigned char CPU::
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}


} /* namespace cpu */
