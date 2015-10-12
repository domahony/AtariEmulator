/*
 * PHA.h
 *
 *  Created on: Sep 16, 2015
 *      Author: domahony
 */

#ifndef PHA_H_
#define PHA_H_

#include "OpCode.h"

namespace cpu {

class PHA: public OpCode {
public:
	PHA() {
	}
	virtual ~PHA() {

	}
	virtual int operator() (CPU*);
	std::string mnemonic() {
		return "PHA";
	}
};

class PHP: public OpCode {
public:
	PHP() {
	}
	virtual ~PHP() {

	}
	virtual int operator() (CPU*);
	std::string mnemonic() {
		return "PHP";
	}
};

class PLA: public OpCode {
public:
	PLA() {
	}
	virtual ~PLA() {

	}
	virtual int operator() (CPU*);
	std::string mnemonic() {
		return "PLA";
	}
};

class PLP: public OpCode {
public:
	PLP() {
	}
	virtual ~PLP() {

	}
	virtual int operator() (CPU*);
	std::string mnemonic() {
		return "PLP";
	}
};

} /* namespace cpu */

#endif /* PHA_H_ */
