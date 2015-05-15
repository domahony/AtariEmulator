/*
 * OpCode.h
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#ifndef OPCODE_H_
#define OPCODE_H_

namespace cpu {

class CPU;

class Immediate {

protected:
	unsigned char read(CPU *cpu);
	int tcount() {
		return 0;
	}

};

class OpCode {
public:
	OpCode() {
		// TODO Auto-generated constructor stub
	}
	virtual int operator() (CPU*) = 0;

	virtual ~OpCode() {
		// TODO Auto-generated destructor stub
	}
};

} /* namespace cpu */

#endif /* OPCODE_H_ */
