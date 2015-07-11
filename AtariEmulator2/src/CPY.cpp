/*
 * CPY.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "CPY.h"

namespace cpu {

template <class T> int CPY<T>::
operator()(CPU* cpu) {

	/*
  t = Y - M
  P.N = t.7
  P.C = (Y>=M) ? 1:0
  P.Z = (t==0) ? 1:0
	 */

	unsigned char M = this->read(cpu);
	unsigned char t = cpu->Y - M;

	cpu->N = (t >> 7);
	cpu->C = (cpu->Y >= M);
	cpu->Z = (t == 0);

	return 1 + this->_tcount;
}

template class CPY<Immediate>;
template class CPY<ZeroPage>;
template class CPY<Absolute>;

} /* namespace cpu */
