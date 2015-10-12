/*
 * SBC.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "SBC.h"
#include <sstream>

namespace cpu {

template <class T>
int SBC<T>::
operator() (CPU* cpu)
{

	unsigned char M = this->read(cpu);
	short t;
	if (cpu->D) {
		t = cpu->BCD(cpu->ACC) - cpu->BCD(M) - (cpu->C ? 1 : 0);
		cpu->V = (t > 99 || t < 0);
	} else {
		t = cpu->ACC - M - (cpu->C ? 1 : 0);
		cpu->V = (t > 127 || t < -128);
	}

	cpu->C = t >= 0;
	cpu->N = t >> 7;
	cpu->Z = t == 0;
	cpu->ACC = t & 0xFF;

	return this->_tcount + 1;
}

template <class T> std::string SBC<T>::
mnemonic() {
	std::stringstream ret;

	ret << "SBC " << this->address_mode;
	return ret.str();
}

template class SBC<Immediate>;
template class SBC<ZeroPage>;
template class SBC<ZeroPageWithXIdx>;
template class SBC<Absolute>;
template class SBC<AbsoluteWithX>;
template class SBC<AbsoluteWithY>;
template class SBC<ZpIdxIndirect>;
template class SBC<ZpIndirectIdxWithY>;

} /* namespace cpu */
