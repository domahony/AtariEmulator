/*
 * PHA.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "PHA.h"

namespace cpu {

int PHA::
operator() (CPU*cpu)
{
	cpu->push(cpu->ACC);
	return 3;
}

int PHP::
operator() (CPU*cpu)
{
	cpu->push(cpu->get_flags());
	return 3;
}

int PLA::
operator() (CPU*cpu)
{
	cpu->ACC = cpu->pop();
	return 4;
}

int PLP::
operator() (CPU*cpu)
{
	cpu->set_flags(cpu->pop());
	return 4;
}

} /* namespace cpu */
