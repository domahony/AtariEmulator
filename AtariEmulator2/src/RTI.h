/*
 * RTI.h
 *
 *  Created on: Sep 17, 2015
 *      Author: domahony
 */

#ifndef RTI_H_
#define RTI_H_

#include "OpCode.h"

namespace cpu {

class RTI: public OpCode {
public:
	RTI() {
		// TODO Auto-generated constructor stub

	}
	virtual ~RTI() {
		// TODO Auto-generated destructor stub
	}
	virtual int operator() (CPU*);
};

} /* namespace cpu */

#endif /* RTI_H_ */
