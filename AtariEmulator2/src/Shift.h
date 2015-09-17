/*
 * Shift.h
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#ifndef SHIFT_H_
#define SHIFT_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class LSR : public OpCode, T {
public:
	LSR() {
		// TODO Auto-generated constructor stub

	}
	virtual ~LSR() {
		// TODO Auto-generated destructor stub
	}
	virtual int operator()(CPU* cpu);
};

template <class T>
class ROL : public OpCode, T {
public:
	ROL() {
		// TODO Auto-generated constructor stub

	}
	virtual ~ROL() {
		// TODO Auto-generated destructor stub
	}
	virtual int operator()(CPU* cpu);
};

template <class T>
class ROR : public OpCode, T {
public:
	ROR() {
		// TODO Auto-generated constructor stub

	}
	virtual ~ROR() {
		// TODO Auto-generated destructor stub
	}
	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */

#endif /* SHIFT_H_ */
