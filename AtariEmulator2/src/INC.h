/*
 * INC.h
 *
 *  Created on: Jul 11, 2015
 *      Author: domahony
 */

#ifndef INC_H_
#define INC_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class INC: public OpCode, T {
public:
	INC() {};
	virtual ~INC() {};
	virtual int operator()(CPU* cpu);
	std::string mnemonic();
};

class INX: public OpCode {
public:
	INX() {};
	virtual ~INX() {};
	virtual int operator()(CPU* cpu);
	std::string mnemonic() {
		return "INX";
	}
};

class INY: public OpCode {
public:
	INY() {};
	virtual ~INY() {};
	virtual int operator()(CPU* cpu);
	std::string mnemonic() {
		return "INY";
	}
};

} /* namespace cpu */

#endif /* INC_H_ */
