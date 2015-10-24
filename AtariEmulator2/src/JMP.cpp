/*
 * JMP.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: domahony
 */

#include "JMP.h"
#include "CPU.h"
#include <sstream>

namespace cpu {

template <class T> int JMP<T>::
operator()(CPU* cpu)
{
	cpu->setPC(this->get_address(cpu));
	return this->_tcount;
}

template <class T> std::string JMP<T>::
mnemonic() {
	std::stringstream ret;

	ret << "JMP " << this->address_mode << std::hex << " " << this->addr;
	return ret.str();
}

int JSR::
operator()(CPU* cpu)
{
	//  t = PC - 1
	addr = cpu->absoluteAddress();
	return_addr = cpu->getPC() - 1;
	//  bPoke(SP,t.h)
	//  SP = SP - 1
	cpu->push(static_cast<unsigned char>(return_addr >> 8));

	//  bPoke(SP,t.l)
	//  SP = SP - 1
	cpu->push(static_cast<unsigned char>(return_addr & 0xFF));

	cpu->setPC(addr);
	return 6;
}

std::string JSR::
mnemonic() {
	std::stringstream ret;

	ret << "JSR " << std::hex << addr << " Return Addr: " << return_addr;
	return ret.str();
}

template class JMP<Absolute>;
template class JMP<Indirect>;

} /* namespace cpu */
