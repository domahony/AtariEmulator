/*
 * ADC.h
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#ifndef ADC_H_
#define ADC_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class ADC: public OpCode, T {
public:

	ADC() {
	}

	virtual ~ADC() {
	}

	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

} /* namespace cpu */

#endif /* ADC_H_ */
