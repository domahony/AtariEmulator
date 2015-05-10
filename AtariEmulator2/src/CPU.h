/*
 * CPU.h
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#ifndef CPU_H_
#define CPU_H_

#include "Clock.h"
#include "Clock2.h"

namespace cpu {

class CPU {
public:
	CPU();
	virtual ~CPU();

	double ticks_per_second();
	bool execute();

private:
	int _execute();
	int wait;
	emulator::Clock clock;
};

} /* namespace cpu */

#endif /* CPU_H_ */
