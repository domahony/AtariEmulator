/*
 * JMP.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: domahony
 */

#include "JMP.h"
#include "CPU.h"

namespace cpu {

template <class T> int JMP<T>::
operator()(CPU* cpu)
{
	cpu->setPC(this->read(cpu));
	return this->_tcount;
}

template <class T> int JSR<T>::
operator()(CPU* cpu)
{
	//  t = PC - 1
	unsigned short t = cpu->getPC() - 1;
	//  bPoke(SP,t.h)
	//  SP = SP - 1
	cpu->push(static_cast<unsigned char>(t >> 8));

	//  bPoke(SP,t.l)
	//  SP = SP - 1
	cpu->push(static_cast<unsigned char>(t && 0xFF));


	cpu->setPC(this->read(cpu));
	 return this->_tcount + 3;
}

template class JMP<Absolute>;
template class JMP<Indirect>;
template class JSR<Absolute>;

} /* namespace cpu */
