/*
 * RTS.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "RTS.h"

namespace cpu {
int RTS::
operator() (CPU* cpu)
{
	unsigned char l = cpu->pop();
	unsigned char h = cpu->pop();
	unsigned short PC = (h << 8) | l;
	cpu->PC = PC + 1;

	return 6;
}

} /* namespace cpu */
