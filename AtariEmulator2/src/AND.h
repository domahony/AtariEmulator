/*
 * ADC.h
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#ifndef AND_H_
#define AND_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class AND: public OpCode, T {
public:

	AND() {
	}

	virtual ~AND() {
	}

	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

} /* namespace cpu */

#endif /* ADC_H_ */
