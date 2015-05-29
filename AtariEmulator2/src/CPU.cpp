/*
 * CPU.cpp
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ADC.h"
#include "AND.h"
#include "ASL.h"
#include "Branch.h"

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

	op[0x29] = new AND<Immediate>();
	op[0x25] = new AND<ZeroPage>();
	op[0x35] = new AND<ZeroPageWithXIdx>();
	op[0x2D] = new AND<Absolute>();
	op[0x3D] = new AND<AbsoluteWithX>();
	op[0x39] = new AND<AbsoluteWithY>();
	op[0x21] = new AND<ZpIdxIndirect>();
	op[0x31] = new AND<ZpIndirectIdxWithY>();

	op[0x0A] = new ASL<Accumulator>();
	op[0x06] = new ASL<ZeroPage>();
	op[0x16] = new ASL<ZeroPageWithXIdx>();
	op[0x0E] = new ASL<Absolute>();
	op[0x1E] = new ASL<AbsoluteWithX>();

	op[0x90] = new BCC();
	op[0xB0] = new BCS();
	op[0xF0] = new BEQ();
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
	return address_space.read(addr);
}

void CPU::
write(unsigned short addr, unsigned char val) {
	return address_space.write(addr, val);
}

unsigned char CPU::
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}


} /* namespace cpu */
