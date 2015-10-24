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
#include "DEC.h"
#include "EOR.h"
#include "INC.h"
#include "JMP.h"
#include "LDA.h"
#include "Shift.h"
#include "NOP.h"
#include "ORA.h"
#include "PHA.h"
#include "RTI.h"
#include "RTS.h"
#include "SBC.h"
#include "STA.h"
#include "Transfer.h"

namespace cpu {

CPU::CPU(int hz, int refresh_rate) : acc(0), hz(hz), refresh_rate(refresh_rate), clock(hz), op(255), wait(0) {

	unsigned char low = read(0xFFFc);
	unsigned char high = read(0xFFFc + 1);

	PC = (high << 8) + low;

	op[0x69] = new ADC<Immediate>();
	op[0x65] = new ADC<ZeroPage>();
	op[0x75] = new ADC<ZeroPageWithXIdx>();
	op[0x6D] = new ADC<Absolute>();
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

	op[0x49] = new EOR<Immediate>();
	op[0x45] = new EOR<ZeroPage>();
	op[0x55] = new EOR<ZeroPageWithXIdx>();
	op[0x4D] = new EOR<Absolute>();
	op[0x5D] = new EOR<AbsoluteWithX>();
	op[0x59] = new EOR<AbsoluteWithY>();
	op[0x41] = new EOR<ZpIdxIndirect>();
	op[0x51] = new EOR<ZpIndirectIdxWithY>();

	op[0xE6] = new INC<ZeroPage>();
	op[0xF6] = new INC<ZeroPageWithXIdx>();
	op[0xEE] = new INC<Absolute>();
	op[0xFE] = new INC<AbsoluteWithX>();
	op[0xE8] = new INX();
	op[0xC8] = new INY();

	op[0x4C] = new JMP<Absolute>();
	op[0x6C] = new JMP<Indirect>();

	op[0x20] = new JSR();

	op[0xA9] = new LDA<Immediate>();
	op[0xA5] = new LDA<ZeroPage>();
	op[0xB5] = new LDA<ZeroPageWithXIdx>();
	op[0xAD] = new LDA<Absolute>();
	op[0xBD] = new LDA<AbsoluteWithX>();
	op[0xB9] = new LDA<AbsoluteWithY>();
	op[0xA1] = new LDA<ZpIdxIndirect>();
	op[0xB1] = new LDA<ZpIndirectIdxWithY>();

	op[0xA2] = new LDX<Immediate>();
	op[0xA6] = new LDX<ZeroPage>();
	op[0xB6] = new LDX<ZeroPageWithYIdx>();
	op[0xAE] = new LDX<Absolute>();
	op[0xBE] = new LDX<AbsoluteWithY>();

	op[0xA0] = new LDY<Immediate>();
	op[0xA4] = new LDY<ZeroPage>();
	op[0xB4] = new LDY<ZeroPageWithXIdx>();
	op[0xAC] = new LDY<Absolute>();
	op[0xBC] = new LDY<AbsoluteWithY>();

	op[0x4A] = new LSR<Accumulator>();
	op[0x46] = new LSR<ZeroPage>();
	op[0x56] = new LSR<ZeroPageWithXIdx>();
	op[0x4E] = new LSR<Absolute>();
	op[0x5E] = new LSR<AbsoluteWithX>();

	op[0xEA] = new NOP();

	op[0x09] = new ORA<Immediate>();
	op[0x05] = new ORA<ZeroPage>();
	op[0x15] = new ORA<ZeroPageWithXIdx>();
	op[0x0D] = new ORA<Absolute>();
	op[0x1D] = new ORA<AbsoluteWithX>();
	op[0x19] = new ORA<AbsoluteWithY>();
	op[0x01] = new ORA<ZpIdxIndirect>();
	op[0x11] = new ORA<ZpIndirectIdxWithY>();

	op[0x48] = new PHA();
	op[0x08] = new PHP();
	op[0x68] = new PLA();
	op[0x28] = new PLP();

	op[0x2A] = new ROL<Accumulator>();
	op[0x26] = new ROL<ZeroPage>();
	op[0x36] = new ROL<ZeroPageWithXIdx>();
	op[0x2E] = new ROL<Absolute>();
	op[0x3E] = new ROL<AbsoluteWithX>();

	op[0x6A] = new ROR<Accumulator>();
	op[0x66] = new ROR<ZeroPage>();
	op[0x76] = new ROR<ZeroPageWithXIdx>();
	op[0x6E] = new ROR<Absolute>();
	op[0x7E] = new ROR<AbsoluteWithX>();

	op[0x40] = new RTI();
	op[0x60] = new RTS();

	op[0xE9] = new SBC<Immediate>();
	op[0xE5] = new SBC<ZeroPage>();
	op[0x75] = new SBC<ZeroPageWithXIdx>();
	op[0xED] = new SBC<Absolute>();
	op[0xFD] = new SBC<AbsoluteWithX>();
	op[0xF9] = new SBC<AbsoluteWithY>();
	op[0xE1] = new SBC<ZpIdxIndirect>();
	op[0xF1] = new SBC<ZpIndirectIdxWithY>();

	op[0x38] = new SEC();
	op[0xF8] = new SED();
	op[0x78] = new SEI();

	op[0x85] = new STA<ZeroPage>();
	op[0x95] = new STA<ZeroPageWithXIdx>();
	op[0x8D] = new STA<Absolute>();
	op[0x9D] = new STA<AbsoluteWithX>();
	op[0x99] = new STA<AbsoluteWithY>();
	op[0x81] = new STA<ZpIdxIndirect>();
	op[0x91] = new STA<ZpIndirectIdxWithY>();

	op[0x86] = new STX<ZeroPage>();
	op[0x96] = new STX<ZeroPageWithYIdx>();
	op[0x8E] = new STX<Absolute>();

	op[0x84] = new STY<ZeroPage>();
	op[0x94] = new STY<ZeroPageWithXIdx>();
	op[0x8C] = new STY<Absolute>();

	op[0xAA] = new TAX();
	op[0xA8] = new TAY();
	op[0x8A] = new TXA();
	op[0xBA] = new TSX();
	op[0x9A] = new TXS();
	op[0x98] = new TYA();

}

CPU::~CPU() {
}

int CPU::
_execute()
{
	unsigned short pc = PC;
	unsigned char opcode = read(PC++);

	//bug add f27a CLRCHP

	if (pc == 0xf2ad) { //JSR EDITRV+$C... jumps to 0xf3e4, need to find this PWRONA I think
		int x = 1;
	}

	OpCode *o = op[opcode];

	int ret = (*o)(this);
	std::cout << pc << " " << o->to_string(this) << std::endl;

	return ret;

	//return (*op[opcode])(this);
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

void CPU::
set_flags(unsigned char flags) {

	unsigned char ret = 0;

	N = (flags >> 7) & 0x1;
	V = (flags >> 5) & 0x1;
	B = (flags >> 4) & 0x1;
	D = (flags >> 3) & 0x1;
	I = (flags >> 2) & 0x1;
	Z = (flags >> 1) & 0x1;
	C = (flags) & 0x1;

}

void CPU::
breakpoint()
{
	int x = 1;
}


} /* namespace cpu */
