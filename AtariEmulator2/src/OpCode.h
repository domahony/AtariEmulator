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
	Immediate() : _tcount(1) { }

	unsigned char read(CPU *cpu);
	int _tcount;

};

class ZeroPage {
protected:
	ZeroPage() : _tcount(2) { }

	unsigned char read(CPU *cpu);
	int _tcount;
};

class ZeroPageWithXIdx {
protected:
	ZeroPageWithXIdx() : _tcount(3) { }

	unsigned char read(CPU *cpu);
	int _tcount;
};

class Absolute {
protected:
	Absolute() : _tcount(3) { }

	unsigned char read(CPU *cpu);
	int _tcount;
};

class AbsoluteWithX {
protected:
	AbsoluteWithX() : _tcount(3) { }

	unsigned char read(CPU *cpu);
	int _tcount;
};

class AbsoluteWithY {
protected:
	AbsoluteWithY() : _tcount(3) { }

	unsigned char read(CPU *cpu);
	int _tcount;
};

class ZpIdxIndirect {
protected:
	ZpIdxIndirect() : _tcount(5) { }

	unsigned char read(CPU *cpu);
	int _tcount;
};

class ZpIndirectIdxWithY {
protected:
	ZpIndirectIdxWithY() : _tcount(4) { }

	unsigned char read(CPU *cpu);
	int _tcount;
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
