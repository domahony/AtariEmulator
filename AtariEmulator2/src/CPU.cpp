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
#include "BIT.h"
#include "BRK.h"
#include "Branch.h"
#include "SetFlags.h"
#include "CMP.h"
#include "CPX.h"
#include "CPY.h"
#include "DEC.h"

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

	op[0x24] = new BIT<ZeroPage>();
	op[0x2C] = new BIT<Absolute>();

	op[0x30] = new BMI();
	op[0xD0] = new BNE();
	op[0x10] = new BPL();

	op[0x00] = new BRK();

	op[0x50] = new BVC();
	op[0x70] = new BVS();

	op[0x18] = new CLC();
	op[0xD8] = new CLD();
	op[0x58] = new CLI();
	op[0xB8] = new CLV();

	op[0xC9] = new CMP<Immediate>();
	op[0xC5] = new CMP<ZeroPage>();
	op[0xD5] = new CMP<ZeroPageWithXIdx>();
	op[0xCD] = new CMP<Absolute>();
	op[0xDD] = new CMP<AbsoluteWithX>();
	op[0xD9] = new CMP<AbsoluteWithY>();
	op[0xC1] = new CMP<ZpIdxIndirect>();
	op[0xD1] = new CMP<ZpIndirectIdxWithY>();

	op[0xE0] = new CPX<Immediate>();
	op[0xE4] = new CPX<ZeroPage>();
	op[0xEC] = new CPX<Absolute>();

	op[0xC0] = new CPY<Immediate>();
	op[0xC4] = new CPY<ZeroPage>();
	op[0xCC] = new CPY<Absolute>();

	op[0xC6] = new DEC<ZeroPage>();
	op[0xD6] = new DEC<ZeroPageWithXIdx>();
	op[0xCE] = new DEC<Absolute>();
	op[0xDE] = new DEC<AbsoluteWithX>();

	op[0xCA] = new DEX();
	op[0x88] = new DEY();
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

void CPU::
push(unsigned char b) {

	write(0x100 | SP, b);
	SP -= 1;

}

unsigned char CPU::
pop() {
	++SP;
	return read(0x100 | SP);
}

unsigned char CPU::
get_flags() const {

	unsigned char ret = 0;

	if (N) ret |= 1;
	ret <<=1;
	if (V) ret |= 1;
	ret <<=2;
	if (B) ret |= 1;
	ret <<=1;
	if (D) ret |= 1;
	ret <<=1;
	if (I) ret |= 1;
	ret <<=1;
	if (Z) ret |= 1;
	ret <<=1;
	if (C) ret |= 1;

	return ret;
}

} /* namespace cpu */
