/*
 * Pokey.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#include "Pokey.h"
#include <string>
#include <iostream>

namespace address {
using namespace std;

Pokey::Pokey() : reg(0xF + 1, 0x0), transmit_idx(0), transmit_byte_ready(false), transmit(0), recieve_idx(0), recieve(0) {
	// TODO Auto-generated constructor stub

	irqen = {0};
	irqset = {0};

	cout << "Reg Size: " << reg.size() << endl;
}

Pokey::~Pokey() {
	// TODO Auto-generated destructor stub
}

void Pokey::
tick() {

	if (transmit_idx) {
		cout << "SHIFTOUT: " << transmit_idx << endl;

		/*
		 * shift out the bit here ...
		 */
		--transmit_idx;
	} else { // there is no byte being shifted out

			// check to see if another byte is ready
			if (transmit_byte_ready) {
				// there is another byte ready
				transmit = reg[WriteReg::SEROUT];
				transmit_byte_ready = false;
				irqset.ODN = (irqen.ODN) ? false : true; //signal another byte needed (if that interrupt is enabled!!
				transmit_idx = 32; // we need to shift out 10bits really
			} else {
				// we've shifted everything out, no other byte is ready, so signal transmit done (XD)
				irqset.XD = (irqen.XD) ? false : true;
			}
	}
}

unsigned char Pokey::
read(unsigned short addr) const
{
	unsigned char ret;
	switch (addr) {
	case ReadReg::POT0:
		ret = reg[addr];
		break;
	case ReadReg::POT1:
		ret = reg[addr];
		break;
	case ReadReg::POT2:
		ret = reg[addr];
		break;
	case ReadReg::POT3:
		ret = reg[addr];
		break;
	case ReadReg::POT4:
		ret = reg[addr];
		break;
	case ReadReg::POT5:
		ret = reg[addr];
		break;
	case ReadReg::POT6:
		ret = reg[addr];
		break;
	case ReadReg::POT7:
		ret = reg[addr];
		break;
	case ReadReg::ALLPOT:
		ret = reg[addr];
		break;
	case ReadReg::KBCODE:
		ret = reg[addr];
		break;
	case ReadReg::RANDOM:
		ret = reg[addr];
		break;
	case ReadReg::SERIN:
		ret = reg[addr];
		break;
	case ReadReg::IRQST:
		ret = get_irq();
		break;
	case ReadReg::SKSTAT:
		ret = reg[addr];
		break;
	default:
		break;
	}

	return ret;
}

void Pokey::
write(unsigned short addr, unsigned char val)
{
	std::string rname;
	switch(addr) {
	case WriteReg::AUDF1:
		rname = "AUDF1";
		break;
	case WriteReg::AUDC1:
		rname = "AUDC1";
		break;
	case WriteReg::AUDF2:
		rname = "AUDF2";
		break;
	case WriteReg::AUDC2:
		rname = "AUDC2";
		break;
	case WriteReg::AUDF3:
		rname = "AUDF3";
		break;
	case WriteReg::AUDC3:
		rname = "AUDC3";
		break;
	case WriteReg::AUDF4:
		rname = "AUDF4";
		break;
	case WriteReg::AUDC4:
		rname = "AUDC4";
		break;
	case WriteReg::AUDCTL:
		rname = "AUDCTL";
		break;
	case WriteReg::STIMER:
		rname = "STIMER";
		break;
	case WriteReg::SKREST:
		rname = "SKREST";
		break;
	case WriteReg::POTGO:
		rname = "POTGO";
		break;
	case WriteReg::SEROUT:
		transmit_byte_ready = true;
		rname = "SEROUT";
		break;
	case WriteReg::IRQEN:
		enable_irq(val);
		rname = "IRQEN";
		break;
	case WriteReg::SKCTL:
		rname = "SKCTL";
		break;
	default:
		rname = "UNDEFINED WRITE to REG!!";
		break;
	}

	cout << "POKEY REG: " << rname << " " << hex << addr << " " << static_cast<unsigned short>(val) << endl;
	reg[addr] = val;
}

unsigned char Pokey::
get_enabled_irq() const
{
	unsigned char ret = 0;
	if (irqen.BREAK) ret |= (1 << IRQ_T::BREAK);
	if (irqen.K) ret |= (1 << IRQ_T::K);
	if (irqen.ODN) ret |= (1 << IRQ_T::ODN);
	if (irqen.SIR) ret |= (1 << IRQ_T::SIR);
	if (irqen.T1) ret |= (1 << IRQ_T::T1);
	if (irqen.T2) ret |= (1 << IRQ_T::T2);
	if (irqen.T4) ret |= (1 << IRQ_T::T4);
	if (irqen.XD) ret |= (1 << IRQ_T::XD);

	return ret;
}

unsigned char Pokey::
get_irq() const
{
	unsigned char ret = 0;
	if (irqset.BREAK) ret |= (1 << IRQ_T::BREAK);
	if (irqset.K) ret |= (1 << IRQ_T::K);
	if (irqset.ODN) ret |= (1 << IRQ_T::ODN);
	if (irqset.SIR) ret |= (1 << IRQ_T::SIR);
	if (irqset.T1) ret |= (1 << IRQ_T::T1);
	if (irqset.T2) ret |= (1 << IRQ_T::T2);
	if (irqset.T4) ret |= (1 << IRQ_T::T4);
	if (irqset.XD) ret |= (1 << IRQ_T::XD);

	return ret;
}

void Pokey::
enable_irq(unsigned char val)
{
	// enable the interrupts
	 irqen.BREAK = (val >> IRQ_T::BREAK) & 1;
	 irqen.K = (val >> IRQ_T::K) & 1;
	 irqen.ODN = (val >> IRQ_T::ODN) & 1;
	 irqen.SIR = (val >> IRQ_T::SIR) & 1;
	 irqen.T1 = (val >> IRQ_T::T1) & 1;
	 irqen.T2 = (val >> IRQ_T::T2) & 1;
	 irqen.T4 = (val >> IRQ_T::T4) & 1;
	 irqen.XD = (val >> IRQ_T::XD) & 1;

	 unsigned char inv_val = ~val;
	 irqset.BREAK |= (inv_val >> IRQ_T::BREAK) & 1;
	 irqset.K |= (inv_val >> IRQ_T::K) & 1;
	 irqset.ODN |= (inv_val >> IRQ_T::ODN) & 1;
	 irqset.SIR |= (inv_val >> IRQ_T::SIR) & 1;
	 irqset.T1 |= (inv_val >> IRQ_T::T1) & 1;
	 irqset.T2 |= (inv_val >> IRQ_T::T2) & 1;
	 irqset.T4 |= (inv_val >> IRQ_T::T4) & 1;
	 irqset.XD |= (inv_val >> IRQ_T::XD) & 1;

	cout << "DECODING POKEY IRQEN VAL: " << static_cast<unsigned short>(val) << endl;

	for (int i = 0; i < 8; i++) {
		switch (i) {
		case IRQ_T::BREAK:
			cout << "IRQEN BREAK: " << irqen.BREAK << endl;
			break;
		case IRQ_T::K:
			cout << "IRQEN K: " << irqen.K << endl;
			break;
		case IRQ_T::ODN:
			cout << "IRQEN ODN: " << irqen.ODN << endl;
			break;
		case IRQ_T::SIR:
			cout << "IRQEN SIR: " << irqen.SIR << endl;
			break;
		case IRQ_T::T1:
			cout << "IRQEN T1: " << irqen.T1 << endl;
			break;
		case IRQ_T::T2:
			cout << "IRQEN T2: " << irqen.T2 << endl;
			break;
		case IRQ_T::T4:
			cout << "IRQEN T4: " << irqen.T4 << endl;
			break;
		case IRQ_T::XD:
			cout << "IRQEN XD: " << irqen.XD << endl;
			break;
		}
	}
}

} /* namespace address */
