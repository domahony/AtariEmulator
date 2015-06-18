/*
 * CPX.h
 *
 *  Created on: Jun 17, 2015
 *      Author: domahony
 */

#ifndef SRC_CPX_H_
#define SRC_CPX_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class CPX: public OpCode, T {
public:
	CPX() {};
	virtual ~CPX() {};

	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */

#endif /* SRC_CPX_H_ */
