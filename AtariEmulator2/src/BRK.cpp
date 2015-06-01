/*
 * BRK.cpp
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "BRK.h"

namespace cpu {

int BRK::
operator()(CPU* cpu) {

	cpu->PC++;

	unsigned char h = cpu->PC >> 8;
	unsigned char l = cpu->PC & 0xFF;
	cpu->push(h);
	cpu->push(l);

	unsigned char flags = cpu->get_flags();

	cpu->push(flags |= 0x10);

	l = cpu->read(0xFFFE);
	h = cpu->read(0xFFFF);

	cpu->PC = h << 8;
	cpu->PC |= l;

	return _tcount;
}

} /* namespace cpu */

