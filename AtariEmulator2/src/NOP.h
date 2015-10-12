/*
 * NOP.h
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#ifndef NOP_H_
#define NOP_H_

#include "OpCode.h"

namespace cpu {

class NOP : public OpCode {
public:
	NOP() {

	}

	virtual ~NOP() {
	}

	virtual int operator()(CPU* cpu);
	std::string mnemonic() {
		return "NOP";
	}
};/* namespace cpu */
}

#endif /* NOP_H_ */
