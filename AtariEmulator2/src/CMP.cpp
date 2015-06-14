/*
 * CMP.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "CMP.h"

namespace cpu {

template <class T> int CMP<T>::
operator()(CPU* cpu) {

	/*
  t = A - M
  P.N = t.7
  P.C = (A>=M) ? 1:0
  P.Z = (t==0) ? 1:0
	 */

	unsigned char M = this->read(cpu);
	unsigned char t = cpu->ACC - M;

	cpu->N = (t >> 7);
	cpu->C = (cpu->ACC >= M);
	cpu->Z = (t == 0);

	return 1 + this->_tcount;
}

template class CMP<Immediate>;
template class CMP<ZeroPage>;
template class CMP<ZeroPageWithXIdx>;
template class CMP<Absolute>;
template class CMP<AbsoluteWithX>;
template class CMP<AbsoluteWithY>;
template class CMP<ZpIdxIndirect>;
template class CMP<ZpIndirectIdxWithY>;

} /* namespace cpu */
