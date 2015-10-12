/*
 * SBC.h
 *
 *  Created on: Sep 17, 2015
 *      Author: domahony
 */

#ifndef SBC_H_
#define SBC_H_

#include "OpCode.h"

namespace cpu {

template <class T>
class SBC: public OpCode, T {
public:
	SBC() {
		// TODO Auto-generated constructor stub

	}
	virtual ~SBC() {
		// TODO Auto-generated destructor stub
	}
	virtual int operator() (CPU*);

	std::string mnemonic();
};

} /* namespace cpu */

#endif /* SBC_H_ */
