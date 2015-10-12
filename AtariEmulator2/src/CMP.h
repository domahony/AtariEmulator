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
	std::string mnemonic();
};

template <class T>
class CPX: public OpCode, T {
public:

	CPX() {
	}

	virtual ~CPX() {
	}

	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

template <class T>
class CPY: public OpCode, T {
public:

	CPY() {
	}

	virtual ~CPY() {
	}

	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

} /* namespace cpu */

#endif /* CMP_H_ */
