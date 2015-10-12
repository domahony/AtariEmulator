/*
 * Transfer.cpp
 *
 *  Created on: Oct 6, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "Transfer.h"
#include <sstream>

namespace cpu {

int TAX::
operator()(CPU* cpu)
{
	cpu->X = cpu->ACC;
	cpu->N = (cpu->X >> 7) & 0x1;
	cpu->Z = (cpu->X == 0);
	/*
	Logic:
	  X = A
	  P.N = X.7
	  P.Z = (X==0) ? 1:0
	 */
	  return 2;
}

std::string TAX::
mnemonic()
{
	return "TAX";
}

int TAY::
operator()(CPU* cpu)
{
	cpu->Y = cpu->ACC;
	cpu->N = (cpu->Y >> 7) & 0x1;
	cpu->Z = (cpu->Y == 0);
	return 2;
}

std::string TAY::
mnemonic()
{
	return "TAY";
}

int TSX::
operator()(CPU* cpu)
{
	/*
	Logic:
	  X = SP
	  P.N = X.7
	  P.Z = (X==0) ? 1:0
	*/
	cpu->X = cpu->SP;
	cpu->N = (cpu->X >> 7) & 0x1;
	cpu->Z = (cpu->X == 0);
	return 2;
}

std::string TSX::
mnemonic()
{
	return "TSX";
}

int TXA::
operator()(CPU* cpu)
{
	/*
Logic:
  A = X
  P.N = A.7
  P.Z = (A==0) ? 1:0
	*/
	cpu->ACC = cpu->X;
	cpu->N = (cpu->ACC >> 7) & 0x1;
	cpu->Z = (cpu->ACC == 0);
	return 2;
}

std::string TXA::
mnemonic()
{
	return "TXA";
}

int TXS::
operator()(CPU* cpu)
{
	/*
Logic:
  SP = X
	*/
	cpu->SP = cpu->X;
	return 2;
}

std::string TXS::
mnemonic()
{
	std::stringstream ret;
	ret << "TXS";

	return ret.str();
}

int TYA::
operator()(CPU* cpu)
{
	/*
Logic:
  A = Y
  P.N = A.7
  P.Z = (A==0) ? 1:0
	*/
	cpu->ACC = cpu->Y;
	cpu->N = (cpu->ACC >> 7) & 0x1;
	cpu->Z = (cpu->ACC == 0);
	return 2;
}


std::string TYA::
mnemonic()
{
	std::stringstream ret;
	ret << "TYA";

	return ret.str();
}

}

