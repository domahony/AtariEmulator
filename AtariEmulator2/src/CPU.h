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
#include "OpCode.h"
#include <vector>

namespace cpu {

class CPU {
public:
	CPU();
	virtual ~CPU();

	double ticks_per_second();
	bool execute();

private:
	int _execute();

	unsigned char BCD(unsigned char);

	int wait;
	emulator::Clock2 clock;

	unsigned short PC;
	unsigned char ACC;
	bool N,V,B,D,I,Z,C;

	std::vector<OpCode*> op;

	template <class T> friend class ADC;
};

} /* namespace cpu */

#endif /* CPU_H_ */
