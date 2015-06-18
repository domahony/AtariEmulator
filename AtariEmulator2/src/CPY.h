/*
 * CPY.h
 *
 *  Created on: Jun 17, 2015
 *      Author: domahony
 */

#ifndef SRC_CPY_H_
#define SRC_CPY_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class CPY: public OpCode, T {
public:
	CPY() {};
	virtual ~CPY() {};

	virtual int operator()(CPU* cpu);

};

} /* namespace cpu */

#endif /* SRC_CPY_H_ */
