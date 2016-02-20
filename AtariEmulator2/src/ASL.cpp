/*
 * ASL.cpp
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ASL.h"
#include <sstream>

namespace cpu {

template <class T> int ASL<T>::
operator()(CPU* cpu) {

	unsigned char B = this->read(cpu);
	cpu->C = (B >> 7);
	B = (B << 1) & 0xFE;
	cpu->N = (B >> 7);
	cpu->Z = (B == 0);

	this->write_back(cpu, B);

	return 2;
}

template <class T> std::string ASL<T>::
mnemonic() {
	std::stringstream ret;

	ret << "ASL " << this->address_mode;
	return ret.str();
}

template class ASL<Accumulator>;
template class ASL<ZeroPage>;
template class ASL<ZeroPageWithXIdx>;
template class ASL<Absolute>;
template class ASL<AbsoluteWithX>;

} /* namespace cpu */
