/*
 * ORA.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ORA.h"
#include <sstream>

namespace cpu {

template <class T> int ORA<T>::
operator()(CPU* cpu) {

	unsigned char arg = this->read(cpu);
	cpu->ACC = cpu->ACC | (arg & 0xFF);
	cpu->N = (cpu->ACC >> 7) & 0x1;
	cpu->Z = (cpu->ACC == 0);

	return 1 + this->_tcount;
}

template <class T> std::string ORA<T>::
mnemonic() {
	std::stringstream ret;

	ret << "ORA " << this->address_mode;
	return ret.str();
}

template class ORA<Immediate>;
template class ORA<ZeroPage>;
template class ORA<ZeroPageWithXIdx>;
template class ORA<Absolute>;
template class ORA<AbsoluteWithX>;
template class ORA<AbsoluteWithY>;
template class ORA<ZpIdxIndirect>;
template class ORA<ZpIndirectIdxWithY>;

} /* namespace cpu */
