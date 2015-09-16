/*
 * ORA.h
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#ifndef ORA_H_
#define ORA_H_
#include "OpCode.h"

namespace cpu {

template <class T>
class ORA: public OpCode, T {
public:

	ORA() {
	}

	virtual ~ORA() {
	}

	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */


#endif /* ORA_H_ */
