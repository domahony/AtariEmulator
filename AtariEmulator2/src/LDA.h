/*
 * LDA.h
 *
 *  Created on: Jul 19, 2015
 *      Author: domahony
 */

#ifndef LDA_H_
#define LDA_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class LDA: public OpCode, T {
public:
	LDA() { }
	virtual ~LDA() { }
	int operator() (CPU*);

	std::string mnemonic();
};

template <class T>
class LDX: public OpCode, T {
public:
	LDX() { }
	virtual ~LDX() { }
	int operator() (CPU*);

	std::string mnemonic();
};

template <class T>
class LDY: public OpCode, T {
public:
	LDY() { }
	virtual ~LDY() { }
	int operator() (CPU*);

	std::string mnemonic();
};

} /* namespace cpu */

#endif /* LDA_H_ */
