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

unsigned char ZeroPageWithXIdx::
read(CPU* cpu) {
	return cpu->zeroPageWithXIdx();
}

unsigned char Absolute::
read(CPU* cpu) {
	return cpu->absoluteAddress();
}

unsigned char AbsoluteWithX::
read(CPU* cpu) {
	return cpu->absoluteAddressX(_tcount);
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

} /* namespace cpu */
