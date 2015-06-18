/*
 * DEC.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "DEC.h"

namespace cpu {

template <class T> int DEC<T>::
operator()(CPU* cpu) {

	/*
  M = (M - 1) & $FF
  P.N = M.7
  P.Z = (M==0) ? 1:0
	 */

	unsigned char M = this->read(cpu);
	M = (M - 1) & 0xFF;

	cpu->N = (M >> 7);
	cpu->Z = (M == 0);

	this->write(cpu, M);

	return 3 + this->_tcount;

}

int DEX::
operator()(CPU* cpu) {

	/*
  X = X - 1
  P.Z = (X==0) ? 1:0
  P.N = X.7
	 */

	unsigned char M = cpu->X;
	M = (M - 1) & 0xFF;

	cpu->N = (M >> 7);
	cpu->Z = (M == 0);

	cpu->X = M;

	return 2;

}

int DEY::
operator()(CPU* cpu) {

	/*
  Y = Y - 1
  P.Z = (Y==0) ? 1:0
  P.N = Y.7
	 */

	unsigned char M = cpu->Y;
	M = (M - 1) & 0xFF;

	cpu->N = (M >> 7);
	cpu->Z = (M == 0);

	cpu->Y = M;

	return 2;

}

template class DEC<ZeroPage>;
template class DEC<ZeroPageWithXIdx>;
template class DEC<Absolute>;
template class DEC<AbsoluteWithX>;

} /* namespace cpu */
