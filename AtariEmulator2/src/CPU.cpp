/*
 * CPU.cpp
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ADC.h"

namespace cpu {

CPU::CPU() : wait(5), clock(2000000), op(255) {

	op[69] = new ADC<Immediate>();

}

CPU::~CPU() {
}

int CPU::
_execute()
{
	return (*op[69])(this);
}

double CPU::
ticks_per_second()
{
	return clock.ticks_per_second();
}

bool CPU::
execute()
{

	int tick_count = 2000000 / 59;

	for (int i = 0; i < tick_count; i++) {
		clock.tick();
		if (wait--) {
			continue;
		} else {
			wait = _execute();
		}
	}

	return true;

	if (!clock.tick()) {
		return false;
	}

	if (wait--) {
		return false;
	}

	wait = _execute();
	return true;
}

unsigned char CPU::
BCD(unsigned char v)
{
	unsigned char tens = (v >> 4) * 10;
	unsigned char ones = v & 0x0F;

	return tens + ones;
}


} /* namespace cpu */
