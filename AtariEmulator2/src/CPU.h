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

namespace video {
	class Video;
}

namespace cpu {

class CPU {
public:
	CPU(int hz, int refresh_rate, video::Video*);
	virtual ~CPU();

	void breakpoint();

	double ticks_per_second();
	bool execute();

	unsigned char readPCandInc() {
		return read(PC++);
	}

	unsigned short getIndirect() {
		unsigned char l1 = readPCandInc();
		unsigned char h1 = readPCandInc();

		unsigned short addr_low = make_short(l1, h1);
		unsigned short addr_high = addr_low + 1;

		unsigned short low = read(addr_low);
		unsigned short high = read(addr_high);

		return make_short(low, high);
	}

	unsigned short zeroPageWithXIdx() {
		unsigned char zp = readPCandInc();
		return make_short(zp + X, 0);
	}

	void zeroPageWithXIdxx(unsigned short& addr, unsigned char val) {
		unsigned char zp = readPCandInc();
		addr = make_short(zp + X, 0);
		return write(addr, val);
	}

	unsigned short zeroPageWithYIdx() {
		unsigned char zp = readPCandInc();
		return make_short(zp + Y, 0);
	}

	unsigned short absoluteAddress()
	{
		unsigned char low = readPCandInc();
		unsigned char high = readPCandInc();

		return make_short(low, high);
		//should this read here? or just return the 16 bit address
		//return read(make_short(low, high));
	}

	unsigned short absoluteAddressX(int& _tcount)
	{
		unsigned char low = readPCandInc();
		unsigned char high = readPCandInc();

		unsigned short addr1 = make_short(low, high);
		unsigned short addr2 = addr1 + X;

		if ((addr1 >> 8) != (addr2 >> 8)) {
			_tcount += 1;
		}

		return addr2;
	}

	unsigned short absoluteAddressY(int& _tcount)
	{
		unsigned char low = readPCandInc();
		unsigned char high = readPCandInc();

		unsigned short addr1 = make_short(low, high);
		unsigned short addr2 = addr1 + Y;

		if ((addr1 >> 8) != (addr2 >> 8)) {
			_tcount += 1;
		}

		return addr2;
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

	void
	setZpIdxIndirect(unsigned char val)
	{
		unsigned char zp = readPCandInc();
		zp += static_cast<char>(X);

		unsigned char low = read(zp);
		unsigned char high = read(zp + 1);

		return write(make_short(low, high), val);
	}

	unsigned short
	getZpIndirectIdxWithY(int& _tcount)
	{
		unsigned char zp = readPCandInc();

		unsigned char low = read(zp);
		unsigned char high = read(zp + 1);

		unsigned short addr1 = make_short(low, high);
		unsigned short addr2 = addr1 + Y; // change from signed to unsigned here...

		if ((addr1 >> 8) != (addr2 >> 8)) {
			_tcount += 1;
		}

		return addr2;
	}

	unsigned char
	getAccumulator()
	{
		return ACC;
	}

	unsigned char
	getX()
	{
		return X;
	}

	unsigned char
	getY()
	{
		return Y;
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
	unsigned char read(unsigned short) const;

private:
	int acc;
	int hz;
	int refresh_rate;

	int _execute();
	int execute_irq();
	int execute_nmi();

	unsigned short make_short(unsigned char low, unsigned char high) {
		unsigned short ret = high;
		ret <<= 8;
		ret |= low;

		return ret;
	}

	unsigned char pop();
	void push(unsigned char);
	unsigned char get_flags() const;
	void set_flags(unsigned char);

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
	std::shared_ptr<address::Pokey> pokey;
	std::shared_ptr<address::ANTIC> antic;

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
	friend class CLI;
	friend class CLV;
	template <class T> friend class CMP;
	template <class T> friend class CPX;
	template <class T> friend class CPY;

	template <class T> friend class DEC;
	friend class DEX;
	friend class DEY;

	template <class T> friend class EOR;

	template <class T> friend class INC;
	friend class INX;
	friend class INY;
	template <class T> friend class JMP;
	friend class JSR;
	template <class T> friend class LDA;
	template <class T> friend class LDX;
	template <class T> friend class LDY;
	template <class T> friend class LSR;
	template <class T> friend class ORA;
	friend class PHA;
	friend class PHP;
	friend class PLA;
	friend class PLP;
	template <class T> friend class ROL;
	template <class T> friend class ROR;
	friend class RTI;
	friend class RTS;
	template <class T> friend class SBC;
	friend class SEC;
	friend class SED;
	friend class SEI;

	template <class T> friend class STA;
	template <class T> friend class STX;
	template <class T> friend class STY;

	friend class TAX;
	friend class TAY;
	friend class TSX;
	friend class TXA;
	friend class TXS;
	friend class TYA;

	friend std::string dbg_flags(const CPU*);
};

} /* namespace cpu */

#endif /* CPU_H_ */
