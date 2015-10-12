/*
 * EOR.h
 *
 *  Created on: Jul 11, 2015
 *      Author: domahony
 */

#ifndef EOR_H_
#define EOR_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class EOR: public OpCode, T {
public:
	EOR() {
		// TODO Auto-generated constructor stub

	}
	virtual ~EOR() {
		// TODO Auto-generated destructor stub
	}

	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

} /* namespace cpu */

#endif /* EOR_H_ */
