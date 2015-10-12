/*
 * Shift.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "Shift.h"
#include <sstream>

namespace cpu {

template <class T> int LSR<T>::
operator()(CPU* cpu)
{
	unsigned char B = this->read(cpu);

	cpu->N = 0;
	cpu->C = B & 0x1;

	B = (B >> 1) & 0x7F;

	cpu->Z = (B == 0);

	this->write(cpu, B);

	return 2 + this->_tcount;
}

template <class T> std::string LSR<T>::
mnemonic() {
	std::stringstream ret;

	ret << "LSR " << this->address_mode;
	return ret.str();
}

template class LSR<Accumulator>;
template class LSR<ZeroPage>;
template class LSR<ZeroPageWithXIdx>;
template class LSR<Absolute>;
template class LSR<AbsoluteWithX>;

template <class T> int ROL<T>::
operator()(CPU* cpu)
{
	unsigned char B = this->read(cpu);
	bool t = B >> 7;
	B = (B << 1) & 0xFE;
	B |= cpu->C;
	cpu->C = t;
	cpu->Z = (B == 0);
	cpu->N = B >> 7;

	this->write(cpu, B);

	return this->_tcount + 3;
}

template <class T> std::string ROL<T>::
mnemonic() {
	std::stringstream ret;

	ret << "ROL " << this->address_mode;
	return ret.str();
}

template class ROL<Accumulator>;
template class ROL<ZeroPage>;
template class ROL<ZeroPageWithXIdx>;
template class ROL<Absolute>;
template class ROL<AbsoluteWithX>;

template <class T> int ROR<T>::
operator()(CPU* cpu)
{
	unsigned char B = this->read(cpu);
	bool t = B & 0x1;
	B = (B >> 1) & 0x7F;
	B = B | ((cpu->C) ? 0x80 : 0x0);
	cpu->C = t;
	cpu->Z = (B == 0);
	cpu->N = B >> 7;

	this->write(cpu, B);

	return this->_tcount + 3;
}

template <class T> std::string ROR<T>::
mnemonic() {
	std::stringstream ret;

	ret << "ROR " << this->address_mode;
	return ret.str();
}

template class ROR<Accumulator>;
template class ROR<ZeroPage>;
template class ROR<ZeroPageWithXIdx>;
template class ROR<Absolute>;
template class ROR<AbsoluteWithX>;
} /* namespace cpu */
