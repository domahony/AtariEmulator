/*
 * STA.h
 *
 *  Created on: Sep 22, 2015
 *      Author: domahony
 */

#ifndef STA_H_
#define STA_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class STA: public OpCode, T {
public:
	STA() { }
	virtual ~STA() { }

	int operator() (CPU*);
};

template <class T>
class STX: public OpCode, T {
public:
	STX() { }
	virtual ~STX() { }

	int operator() (CPU*);
};

template <class T>
class STY: public OpCode, T {
public:
	STY() { }
	virtual ~STY() { }

	int operator() (CPU*);
};

} /* namespace cpu */

#endif /* STA_H_ */
