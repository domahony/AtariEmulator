/*
 * CPU.h
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#ifndef CPU_H_
#define CPU_H_

#include "Clock.h"
#include "Clock2.h"
#include "OpCode.h"
#include "AddressSpace.h"
#include <vector>

namespace cpu {

class CPU {
public:
	CPU(int hz, int refresh_rate);
	virtual ~CPU();

	double ticks_per_second();
	bool execute();

	unsigned char readPCandInc() {
		return read(PC++);
	}

	unsigned char zeroPage() {
		unsigned char low = readPCandInc();
		return read(make_short(low, 0));
	}

	unsigned char zeroPageWithXIdx() {
		unsigned char zp = readPCandInc();
		return read(make_short(zp + X, 0));
	}

	unsigned char absoluteAddress()
	{
		unsigned char low = readPCandInc();
		unsigned char high = readPCandInc();
		return read(make_short(low, high));
	}

	unsigned char absoluteAddressX(int& _tcount)
	{
		unsigned char low = readPCandInc();
		unsigned char high = readPCandInc();

		unsigned short addr1 = make_short(low, high);
		unsigned short addr2 = addr1 + X;

		if ((addr1 >> 8) != (addr2 >> 8)) {
			_tcount += 1;
		}

		return read(addr2);
	}

	unsigned char absoluteAddressY(int& _tcount)
	{
		unsigned char low = readPCandInc();
		unsigned char high = readPCandInc();

		unsigned short addr1 = make_short(low, high);
		unsigned short addr2 = addr1 + Y;

		if ((addr1 >> 8) != (addr2 >> 8)) {
			_tcount += 1;
		}

		return read(addr2);
	}

	char getRelative()
	{
		return static_cast<char>(readPCandInc());
	}

	unsigned char
	getZpIdxIndirect()
	{
		unsigned char zp = readPCandInc();
		zp += static_cast<char>(X);

		unsigned char low = read(zp);
		unsigned char high = read(zp + 1);

		return read(make_short(low, high));
	}

	unsigned char
	getZpIndirectIdxWithY(int& _tcount)
	{
		unsigned char zp = readPCandInc();

		unsigned char low = read(zp);
		unsigned char high = read(zp + 1);

		unsigned short addr1 = make_short(low, high);
		unsigned short addr2 = addr1 + static_cast<char>(Y);

		if ((addr1 >> 8) != (addr2 >> 8)) {
			_tcount += 1;
		}

		return read(addr2);
	}

	unsigned char
	getAccumulator()
	{
		return ACC;
	}

	unsigned short
	getPC() const
	{
		return PC;
	}

	void
	setPC(unsigned short val)
	{
		PC = val;
	}

	void
	setAccumulator(unsigned char val)
	{
		ACC = val;
	}

	void write(unsigned short, unsigned char val);

private:
	int acc;
	int hz;
	int refresh_rate;

	int _execute();

	unsigned short make_short(unsigned char low, unsigned char high) {
		unsigned short ret = high;
		ret <<= 8;
		ret |= low;

		return ret;
	}

	unsigned char read(unsigned short) const;
	unsigned char pop();
	void push(unsigned char);
	unsigned char get_flags() const;

	unsigned char BCD(unsigned char);

	int wait;
	emulator::Clock2 clock;

	unsigned short PC;
	unsigned short SP;
	unsigned char ACC;
	unsigned char X;
	unsigned char Y;
	bool N,V,B,D,I,Z,C;

	std::vector<OpCode*> op;

	address::AddressSpace address_space;

	template <class T> friend class ADC;
	template <class T> friend class AND;
	template <class T> friend class ASL;
	friend class BCC;
	friend class BCS;
	friend class BEQ;
	template <class T> friend class BIT;
	friend class BMI;
	friend class BNE;
	friend class BPL;
	friend class BRK;
	friend class BVC;
	friend class BVS;
	friend class CLC;
	friend class CLD;
};

} /* namespace cpu */

#endif /* CPU_H_ */
