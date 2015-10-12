/*
 * SetFlags.h
 *
 *  Created on: June 11, 2015
 *      Author: domahony
 */

#ifndef SETFLAGS_H_
#define SETFLAGS_H_

#include "OpCode.h"

namespace cpu {

class CLC : public OpCode {
public:
	CLC() {};
	virtual ~CLC() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "CLC";
	}
};

class CLD : public OpCode {
public:
	CLD() {};
	virtual ~CLD() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "CLD";
	}
};

class CLI : public OpCode {
public:
	CLI() {};
	virtual ~CLI() {};
	std::string mnemonic() {
		return "CLI";
	}
	virtual int operator()(CPU*);
};

class CLV : public OpCode {
public:
	CLV() {};
	virtual ~CLV() {};
	std::string mnemonic() {
		return "CLV";
	}
	virtual int operator()(CPU*);
};

class SEC : public OpCode {
public:
	SEC() {};
	virtual ~SEC() {};
	std::string mnemonic() {
		return "SEC";
	}
	virtual int operator()(CPU*);
};

class SED : public OpCode {
public:
	SED() {};
	virtual ~SED() {};
	std::string mnemonic() {
		return "SED";
	}
	virtual int operator()(CPU*);
};

class SEI : public OpCode {
public:
	SEI() {};
	virtual ~SEI() {};
	std::string mnemonic() {
		return "SEI";
	}
	virtual int operator()(CPU*);
};

} /* namespace cpu */

#endif /* SETFLAGS_H_ */
