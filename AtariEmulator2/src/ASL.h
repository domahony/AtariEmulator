/*
 * ASL.h
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#ifndef ASL_H_
#define ASL_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class ASL: public OpCode, T {
public:
	ASL() {

	}

	virtual ~ASL() {

	}

	virtual int operator()(CPU*);
	std::string mnemonic();
};

} /* namespace cpu */

#endif /* ASL_H_ */
