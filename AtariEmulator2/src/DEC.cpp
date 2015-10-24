/*
 * DEC.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: domahony
 */

#include "DEC.h"
#include "CPU.h"
#include <sstream>

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
	this->value = M;
	cpu->write(this->addr, this->value);

	return 3 + this->_tcount;
}

template <class T> std::string DEC<T>::
mnemonic() {
	std::stringstream ret;

	ret << "DEC " << this->address_mode << " " << std::hex << this->addr << " " << this->value;
	return ret.str();
}

int DEX::
operator()(CPU* cpu) {

/*
  M = X
  M = (M - 1) & $FF
  P.N = M.7
  P.Z = (M==0) ? 1:0
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
  M = Y
  M = (M - 1) & $FF
  P.N = M.7
  P.Z = (M==0) ? 1:0
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
