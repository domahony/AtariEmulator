/*
 * DEC.h
 *
 *  Created on: Jul 11, 2015
 *      Author: domahony
 */

#ifndef DEC_H_
#define DEC_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class DEC: public OpCode, T {
public:
	DEC() {};
	virtual ~DEC() {};
	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

class DEX: public OpCode {
public:
	DEX() {};
	virtual ~DEX() {};
	virtual int operator()(CPU* cpu);
	std::string mnemonic() {
		return "DEX";
	}
};

class DEY: public OpCode {
public:
	DEY() {};
	virtual ~DEY() {};
	virtual int operator()(CPU* cpu);
	std::string mnemonic() {
		return "DEY";
	}
};

} /* namespace cpu */

#endif /* DEC_H_ */
