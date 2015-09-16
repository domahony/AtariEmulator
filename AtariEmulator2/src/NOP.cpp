/*
 * NOP.cpp
 *
 *  Created on: Sep 15, 2015
 *      Author: domahony
 */

#include "NOP.h"

namespace cpu {

int NOP::
operator()(CPU* cpu)
{
	return 2;
}

} /* namespace cpu */
