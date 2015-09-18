/*
 * RTS.h
 *
 *  Created on: Sep 17, 2015
 *      Author: domahony
 */

#ifndef RTS_H_
#define RTS_H_

#include "OpCode.h"

namespace cpu {

class RTS: public OpCode {
public:
	RTS() {
		// TODO Auto-generated constructor stub

	}
	virtual ~RTS() {
		// TODO Auto-generated destructor stub
	}
	virtual int operator() (CPU*);
};

} /* namespace cpu */

#endif /* RTS_H_ */
