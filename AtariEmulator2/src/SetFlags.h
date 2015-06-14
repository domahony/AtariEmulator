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
};

class CLD : public OpCode {
public:
	CLD() {};
	virtual ~CLD() {};
	virtual int operator()(CPU*);
};

class CLI : public OpCode {
public:
	CLI() {};
	virtual ~CLI() {};
	virtual int operator()(CPU*);
};

class CLV : public OpCode {
public:
	CLV() {};
	virtual ~CLV() {};
	virtual int operator()(CPU*);
};

} /* namespace cpu */

#endif /* SETFLAGS_H_ */
