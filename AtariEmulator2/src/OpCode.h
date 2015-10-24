/*
 * OpCode.h
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#ifndef OPCODE_H_
#define OPCODE_H_

#include <string>

namespace cpu {

class CPU;

class Accumulator {
protected:
	Accumulator() : _tcount(0), address_mode("Accumulator") { }
	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);

	int _tcount;
	std::string address_mode;
};

class Indirect {
protected:
	Indirect() : _tcount(5), address_mode("Indirect"), addr(0), value(0) { }
	unsigned char read(CPU *cpu);
	unsigned short get_address(CPU *cpu);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;

};

class Immediate {
protected:
	Immediate() : _tcount(1), address_mode("Immediate"), addr(0) { }

	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;

};

class ZeroPage {
protected:
	ZeroPage() : _tcount(2), address_mode("ZeroPage"), addr(0), value(0) { }
	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;

};

class ZeroPageWithXIdx {
protected:
	ZeroPageWithXIdx() : _tcount(3), address_mode("ZeroPageWithXIdx"), addr(0), value(0) { }
	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;

private:
};

class ZeroPageWithYIdx {
protected:
	ZeroPageWithYIdx() : _tcount(3), address_mode("ZeroPageWithYIdx"), addr(0), value(0) { }
	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;

private:
};

class Absolute {
protected:
	Absolute() : _tcount(3), address_mode("Absolute"), addr(0), value(0) { }
	unsigned char read(CPU *cpu);
	unsigned short get_address(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;

private:
};

class AbsoluteWithX {
protected:
	AbsoluteWithX() : _tcount(3), address_mode("AbsoluteWithX"), addr(0), value(0) { }
	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;

private:

};

class AbsoluteWithY {
protected:
	AbsoluteWithY() : _tcount(3), address_mode("AbsoluteWithY"), addr(0), value(0) { }

	unsigned char read(CPU *cpu);
	void write(CPU* cpu, unsigned char val);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;
};

class ZpIdxIndirect {
protected:
	ZpIdxIndirect() : _tcount(5), address_mode("ZpIdxIndirect"), addr(0), value(0) { }

	unsigned char read(CPU *cpu);
	void write(CPU *cpu, unsigned char);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;
};

class ZpIndirectIdxWithY {
protected:
	ZpIndirectIdxWithY() : _tcount(4), address_mode("ZpIndirectIdxWithY"), addr(0), value(0) { }

	unsigned char read(CPU *cpu);
	void write(CPU *cpu, unsigned char);
	int _tcount;
	std::string address_mode;
	unsigned short addr;
	unsigned char value;
};

class OpCode {
public:
	OpCode() { }
	virtual int operator() (CPU*) = 0;
	virtual std::string mnemonic() = 0;
	std::string to_string(CPU*);

	virtual ~OpCode() { }
};

} /* namespace cpu */

#endif /* OPCODE_H_ */
