/*
 * LDA.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: domahony
 */

#include "LDA.h"
#include "CPU.h"

namespace cpu {

template <class T> int LDA<T>::
operator()(CPU* cpu) {

/*
	  A = M
	  P.N = A.7
	  P.Z = (A==0) ? 1:0
*/

	cpu->setAccumulator(this->read(cpu));
	unsigned char acc = cpu->getAccumulator();
	cpu->N = (acc >> 7);
	cpu->Z = acc == 0;

	return this->_tcount + 1;
}

template <class T> int LDX<T>::
operator()(CPU* cpu) {

/*
*/

	cpu->X = this->read(cpu);
	cpu->N = (cpu->X >> 7);
	cpu->Z = (cpu->X == 0);

	return this->_tcount + 1;
}

template <class T> int LDY<T>::
operator()(CPU* cpu) {

/*
*/

	cpu->Y = this->read(cpu);
	cpu->N = (cpu->Y >> 7);
	cpu->Z = (cpu->Y == 0);

	return this->_tcount + 1;
}

template class LDA<Immediate>;
template class LDA<ZeroPage>;
template class LDA<ZeroPageWithXIdx>;
template class LDA<Absolute>;
template class LDA<AbsoluteWithX>;
template class LDA<AbsoluteWithY>;
template class LDA<ZpIdxIndirect>;
template class LDA<ZpIndirectIdxWithY>;

template class LDX<Immediate>;
template class LDX<ZeroPage>;
template class LDX<ZeroPageWithYIdx>;
template class LDX<Absolute>;
template class LDX<AbsoluteWithY>;

template class LDY<Immediate>;
template class LDY<ZeroPage>;
template class LDY<ZeroPageWithYIdx>;
template class LDY<Absolute>;
template class LDY<AbsoluteWithY>;

} /* namespace cpu */
