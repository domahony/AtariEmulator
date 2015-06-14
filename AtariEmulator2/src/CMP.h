/*
 * CMP.h
 *
 *  Created on: Jun 14, 2015
 *      Author: domahony
 */

#ifndef CMP_H_
#define CMP_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class CMP: public OpCode, T {
public:

	CMP() {
	}

	virtual ~CMP() {
	}

	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */

#endif /* CMP_H_ */
