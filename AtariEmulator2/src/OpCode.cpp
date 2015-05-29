/*
 * OpCode.cpp
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#include "OpCode.h"
#include "CPU.h"

namespace cpu {

unsigned char Immediate::
read(CPU *cpu) {
	return cpu->readPCandInc();
}

unsigned char ZeroPage::
read(CPU* cpu) {
	return cpu->zeroPage();
}

void ZeroPage::
write(CPU* cpu, unsigned char val) {
	return cpu->write(addr, val);
}

unsigned char ZeroPageWithXIdx::
read(CPU* cpu) {
	return cpu->zeroPageWithXIdx();
}

void ZeroPageWithXIdx::
write(CPU* cpu, unsigned char val) {
	return cpu->write(addr, val);
}

unsigned char Absolute::
read(CPU* cpu) {
	return cpu->absoluteAddress();
}

void Absolute::
write(CPU* cpu, unsigned char val) {
	cpu->write(addr, val);
}

unsigned char AbsoluteWithX::
read(CPU* cpu) {
	return cpu->absoluteAddressX(_tcount);
}

void AbsoluteWithX::
write(CPU* cpu, unsigned char val) {
	cpu->write(addr, val);
}

unsigned char AbsoluteWithY::
read(CPU* cpu) {
	return cpu->absoluteAddressY(_tcount);
}

unsigned char ZpIdxIndirect::
read(CPU* cpu) {
	return cpu->getZpIdxIndirect();
}

unsigned char ZpIndirectIdxWithY::
read(CPU* cpu)
{
	return cpu->getZpIndirectIdxWithY(_tcount);
}

unsigned char Accumulator::
read(CPU* cpu)
{
	return cpu->getAccumulator();
}

void Accumulator::
write(CPU* cpu, unsigned char val)
{
	return cpu->setAccumulator(val);
}


} /* namespace cpu */
