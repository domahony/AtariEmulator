/*
 * BIT.h
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#ifndef BIT_H_
#define BIT_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class BIT: public OpCode, T {
public:

	BIT() {
	}

	virtual ~BIT() {
	}

	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */

#endif /* BIT_H_ */
