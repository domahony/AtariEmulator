/*
 * ADC.cpp
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "AND.h"

namespace cpu {

template <class T> int AND<T>::
operator()(CPU* cpu) {

	unsigned char arg = this->read(cpu);
	cpu->ACC = cpu->ACC & (arg & 0xFF);
	cpu->N = (cpu->ACC >> 7) & 0x1;
	cpu->Z = (cpu->ACC == 0);

	return 1 + this->_tcount;
}

template class AND<Immediate>;
template class AND<ZeroPage>;
template class AND<ZeroPageWithXIdx>;
template class AND<Absolute>;
template class AND<AbsoluteWithX>;
template class AND<AbsoluteWithY>;
template class AND<ZpIdxIndirect>;
template class AND<ZpIndirectIdxWithY>;

} /* namespace cpu */

