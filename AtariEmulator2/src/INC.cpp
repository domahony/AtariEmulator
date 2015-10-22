/*
 * INC.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: domahony
 */

#include "INC.h"
#include "CPU.h"
#include <sstream>

namespace cpu {

template <class T> int INC<T>::
operator()(CPU* cpu) {

/*
  M = (M - 1) & $FF
  P.N = M.7
  P.Z = (M==0) ? 1:0
 */

	unsigned char M = this->read(cpu);
	M = (M + 1) & 0xFF;
	cpu->N = (M >> 7);
	cpu->Z = (M == 0);
	this->write(cpu, M);

	return 3 + this->_tcount;
}

template <class T> std::string INC<T>::
mnemonic() {
	std::stringstream ret;

	ret << "INC " << this->address_mode << " " << std::hex << this->addr;
	return ret.str();
}

int INX::
operator()(CPU* cpu) {

/*
  M = X
  M = (M - 1) & $FF
  P.N = M.7
  P.Z = (M==0) ? 1:0
 */

	unsigned char M = cpu->X;
	M = (M + 1) & 0xFF;
	cpu->N = (M >> 7);
	cpu->Z = (M == 0);
	cpu->X = M;

	return 2;
}

int INY::
operator()(CPU* cpu) {

/*
  M = Y
  M = (M - 1) & $FF
  P.N = M.7
  P.Z = (M==0) ? 1:0
 */

	unsigned char M = cpu->Y;
	M = (M + 1) & 0xFF;
	cpu->N = (M >> 7);
	cpu->Z = (M == 0);
	cpu->Y = M;

	return 2;
}

template class INC<ZeroPage>;
template class INC<ZeroPageWithXIdx>;
template class INC<Absolute>;
template class INC<AbsoluteWithX>;

} /* namespace cpu */
