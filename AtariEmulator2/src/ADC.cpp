/*
 * ADC.cpp
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "ADC.h"

namespace cpu {

//template <class T> int ADC<T>::
template <class T> int ADC<T>::
operator()(CPU* cpu) {

		unsigned char arg = this->read(cpu);

		unsigned short val = cpu->ACC + arg + (cpu->C ? 1 : 0);

		cpu->V = ((val >> 7) != (cpu->ACC >> 7));
		cpu->N = (cpu->ACC >> 7) & 0x1;
		cpu->Z = (val == 0);

		if (cpu->D) {
			val = cpu->BCD(cpu->ACC) + cpu->BCD(arg) + (cpu->C ? 1 : 0);
			cpu->C = val > 99;
		} else {
			cpu->C = val > 255;
		}

		cpu->ACC = val & 0xFF;

		return 2 + this->tcount();
}

template class ADC<Immediate>;

} /* namespace cpu */

