/*
 * RTI.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "RTI.h"

namespace cpu {

int RTI::
operator() (CPU* cpu)
{
	unsigned char P = cpu->pop();
	unsigned char l = cpu->pop();
	unsigned char h = cpu->pop();

	unsigned short PC = h << 8 | l;
	cpu->PC = PC;

	return 6;
}

} /* namespace cpu */
