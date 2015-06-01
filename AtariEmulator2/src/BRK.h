/*
 * BRK.h
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#ifndef BRK_H_
#define BRK_H_

#include "OpCode.h"

namespace cpu {

class BRK: public OpCode {
public:

	BRK() : _tcount(7) {
	}

	virtual ~BRK() {
	}

	virtual int operator()(CPU* cpu);

private:
	int _tcount;
};

} /* namespace cpu */

#endif /* BRK_H_ */
