/*
 * CMP.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "CMP.h"
#include <sstream>

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

template <class T> std::string CMP<T>::
mnemonic() {
	std::stringstream ret;

	ret << "CMP " << this->address_mode << std::hex << " " << this->addr;
	return ret.str();
}

template <class T> int CPX<T>::
operator()(CPU* cpu) {

	/*
  t = A - M
  P.N = t.7
  P.C = (A>=M) ? 1:0
  P.Z = (t==0) ? 1:0
	 */

	unsigned char M = this->read(cpu);
	unsigned char t = cpu->X - M;

	cpu->N = (t >> 7);
	cpu->C = (cpu->X >= M);
	cpu->Z = (t == 0);

	return 1 + this->_tcount;
}

template <class T> std::string CPX<T>::
mnemonic() {
	std::stringstream ret;

	ret << "CPX " << this->address_mode;
}

template <class T> int CPY<T>::
operator()(CPU* cpu) {

	/*
  t = A - M
  P.N = t.7
  P.C = (A>=M) ? 1:0
  P.Z = (t==0) ? 1:0
	 */

	unsigned char M = this->read(cpu);
	unsigned char t = cpu->Y - M;

	cpu->N = (t >> 7);
	cpu->C = (cpu->Y >= M);
	cpu->Z = (t == 0);

	return 1 + this->_tcount;
}

template <class T> std::string CPY<T>::
mnemonic() {
	std::stringstream ret;

	ret << "CPY " << this->address_mode;
}

template class CMP<Immediate>;
template class CMP<ZeroPage>;
template class CMP<ZeroPageWithXIdx>;
template class CMP<Absolute>;
template class CMP<AbsoluteWithX>;
template class CMP<AbsoluteWithY>;
template class CMP<ZpIdxIndirect>;
template class CMP<ZpIndirectIdxWithY>;

template class CPX<Immediate>;
template class CPX<ZeroPage>;
template class CPX<Absolute>;

template class CPY<Immediate>;
template class CPY<ZeroPage>;
template class CPY<Absolute>;

} /* namespace cpu */
