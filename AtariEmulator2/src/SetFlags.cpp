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

int CLI::
operator()(CPU* cpu)
{
	cpu->I = false;
	return 2;
}

int CLV::
operator()(CPU* cpu)
{
	cpu->V = false;
	return 2;
}

int SEC::
operator()(CPU* cpu)
{
	cpu->C = true;
	return 2;
}

int SED::
operator()(CPU* cpu)
{
	cpu->D = true;
	return 2;
}

int SEI::
operator()(CPU* cpu)
{
	cpu->I = true;
	return 2;
}

} /* namespace cpu */
