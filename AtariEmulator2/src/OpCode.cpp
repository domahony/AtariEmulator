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

} /* namespace cpu */
