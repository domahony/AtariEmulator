/*
 * BCC.h
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#ifndef BCC_H_
#define BCC_H_

#include "OpCode.h"

namespace cpu {

class BCC : public OpCode {
public:
	BCC() {};
	virtual ~BCC() {};
	virtual int operator()(CPU*);
};

class BCS : public OpCode {
public:
	BCS() {};
	virtual ~BCS() {};
	virtual int operator()(CPU*);
};

class BEQ : public OpCode {
public:
	BEQ() {};
	virtual ~BEQ() {};
	virtual int operator()(CPU*);
};

class BMI : public OpCode {
public:
	BMI() {};
	virtual ~BMI() {};
	virtual int operator()(CPU*);
};

class BNE : public OpCode {
public:
	BNE() {};
	virtual ~BNE() {};
	virtual int operator()(CPU*);
};

class BPL : public OpCode {
public:
	BPL() {};
	virtual ~BPL() {};
	virtual int operator()(CPU*);
};

} /* namespace cpu */

#endif /* BCC_H_ */
