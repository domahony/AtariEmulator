/*
 * SetFlags.cpp
 *
 *  Created on: June 11, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "SetFlags.h"

namespace cpu {

int CLC::
operator()(CPU* cpu)
{
	cpu->C = false;
	return 2;
}

int CLD::
operator()(CPU* cpu)
{
	cpu->D = false;
	return 2;
}

} /* namespace cpu */
