/*
 * DEC.h
 *
 *  Created on: Jun 17, 2015
 *      Author: domahony
 */

#ifndef SRC_DEC_H_
#define SRC_DEC_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class DEC: public OpCode, T {
public:
	DEC() {};
	virtual ~DEC() {};

	virtual int operator()(CPU* cpu);
};

class DEX: public OpCode {
public:
	DEX() {};
	virtual ~DEX() {};

	virtual int operator()(CPU* cpu);
};

class DEY: public OpCode {
public:
	DEY() {};
	virtual ~DEY() {};

	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */

#endif /* SRC_DEC_H_ */
