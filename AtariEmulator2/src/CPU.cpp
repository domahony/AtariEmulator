/*
 * CPU.cpp
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#include "CPU.h"

namespace cpu {

CPU::CPU() : wait(5), clock(2000000) {

}

CPU::~CPU() {
}

int CPU::
_execute()
{
	return 5;
}

double CPU::
ticks_per_second()
{
	return clock.ticks_per_second();
}

bool CPU::
execute()
{
	if (!clock.tick()) {
		return false;
	}

	if (wait--) {
		return false;
	}

	wait = _execute();
	return true;
}

} /* namespace cpu */
