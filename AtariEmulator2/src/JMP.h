/*
 * JMP.h
 *
 *  Created on: Jul 18, 2015
 *      Author: domahony
 */

#ifndef JMP_H_
#define JMP_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class JMP: public OpCode, T {
public:
	JMP() { }
	virtual ~JMP() { }
	virtual int operator()(CPU* cpu);
};

template <class T>
class JSR: public OpCode, T {
public:
	JSR() { }
	virtual ~JSR() { }
	virtual int operator()(CPU* cpu);
};

} /* namespace cpu */

#endif /* JMP_H_ */
