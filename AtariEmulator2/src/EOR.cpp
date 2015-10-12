/*
 * EOR.cpp
 *
 *  Created on: Jul 11, 2015
 *      Author: domahony
 */

#include "EOR.h"
#include "CPU.h"
#include <sstream>

namespace cpu {

template <class T> int EOR<T>::
operator()(CPU* cpu) {
/*
	Logic:
	  A = A ^ M
	  P.N = A.7
	  P.Z = (A==0) ? 1:0
*/

	cpu->ACC = cpu->ACC ^ this->read(cpu);
	cpu->N = cpu->ACC >> 7;
	cpu->Z = cpu->ACC == 0;

	return 1 + this->_tcount;
}

template <class T> std::string EOR<T>::
mnemonic() {
	std::stringstream ret;

	ret << "EOR " << this->address_mode;
	return ret.str();
}

template class EOR<Immediate>;
template class EOR<ZeroPage>;
template class EOR<ZeroPageWithXIdx>;
template class EOR<Absolute>;
template class EOR<AbsoluteWithX>;
template class EOR<AbsoluteWithY>;
template class EOR<ZpIdxIndirect>;
template class EOR<ZpIndirectIdxWithY>;

} /* namespace cpu */
