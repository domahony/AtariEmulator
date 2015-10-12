/*
 * BIT.cpp
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "BIT.h"
#include <sstream>

namespace cpu {

template <class T> int BIT<T>::
operator()(CPU* cpu) {

	unsigned char M = this->read(cpu);
	unsigned char t = cpu->ACC & M;
	cpu->N = (t >> 7);
	cpu->V = (t >> 6) & 0x1;
	cpu->Z = (t == 0);

	return 1;
}

template <class T> std::string BIT<T>::
mnemonic() {
	std::stringstream ret;

	ret << "BIT " << this->address_mode;
	return ret.str();
}


template class BIT<ZeroPage>;
template class BIT<Absolute>;

} /* namespace cpu */
