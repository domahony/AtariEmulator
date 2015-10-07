/*
 * Transfer.h
 *
 *  Created on: Oct 6, 2015
 *      Author: domahony
 */

#ifndef TRANSFER_H_
#define TRANSFER_H_

#include "OpCode.h"

namespace cpu {

class TAX: public OpCode {
public:
	TAX() { }
	virtual ~TAX() { }

	int operator() (CPU*);
};

class TAY: public OpCode {
public:
	TAY() { }
	virtual ~TAY() { }

	int operator() (CPU*);
};

class TSX: public OpCode {
public:
	TSX() { }
	virtual ~TSX() { }

	int operator() (CPU*);
};

class TXA: public OpCode {
public:
	TXA() { }
	virtual ~TXA() { }

	int operator() (CPU*);
};

class TXS: public OpCode {
public:
	TXS() { }
	virtual ~TXS() { }

	int operator() (CPU*);
};

class TYA: public OpCode {
public:
	TYA() { }
	virtual ~TYA() { }

	int operator() (CPU*);
};

} /* namespace cpu */



#endif /* TRANSFER_H_ */
