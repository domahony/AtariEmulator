/*
 * CPX.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "CPX.h"

namespace cpu {

template <class T> int CPX<T>::
operator()(CPU* cpu) {

	/*
  t = X - M
  P.N = t.7
  P.C = (X>=M) ? 1:0
  P.Z = (t==0) ? 1:0
	 */

	unsigned char M = this->read(cpu);
	unsigned char t = cpu->X - M;

	cpu->N = (t >> 7);
	cpu->C = (cpu->X >= M);
	cpu->Z = (t == 0);

	return 1 + this->_tcount;
}

template class CPX<Immediate>;
template class CPX<ZeroPage>;
template class CPX<Absolute>;


} /* namespace cpu */
