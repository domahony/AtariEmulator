/*
 * Shift.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "Shift.h"

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

template class LSR<Accumulator>;
template class LSR<ZeroPage>;
template class LSR<ZeroPageWithXIdx>;
template class LSR<Absolute>;
template class LSR<AbsoluteWithX>;

} /* namespace cpu */
