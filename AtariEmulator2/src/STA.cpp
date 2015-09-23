/*
 * STA.cpp
 *
 *  Created on: Sep 22, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "STA.h"

namespace cpu {

template <class T> int STA<T>::
operator()(CPU *cpu)
{
	this->write(cpu, cpu->ACC);
	return this->_tcount;
}

template <class T> int STX<T>::
operator()(CPU *cpu)
{
	this->write(cpu, cpu->X);
	return this->_tcount;
}

template <class T> int STY<T>::
operator()(CPU *cpu)
{
	this->write(cpu, cpu->Y);
	return this->_tcount;
}

template class STA<ZeroPage>;
template class STA<ZeroPageWithXIdx>;
template class STA<Absolute>;
template class STA<AbsoluteWithX>;
template class STA<AbsoluteWithY>;
template class STA<ZpIdxIndirect>;
template class STA<ZpIndirectIdxWithY>;

template class STX<ZeroPage>;
template class STX<ZeroPageWithYIdx>;
template class STX<Absolute>;

template class STY<ZeroPage>;
template class STY<ZeroPageWithXIdx>;
template class STY<Absolute>;

} /* namespace cpu */
