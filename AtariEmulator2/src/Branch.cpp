/*
 * BCC.cpp
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#include "CPU.h"
#include "Branch.h"

namespace cpu {

int BCC::
operator()(CPU* cpu)
{
	char offset = cpu->getRelative();
	int ret = 2;
	bit = cpu->C;

	addr = cpu->getPC();
	if (!cpu->C) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		addr = npc;
		cpu->setPC(npc);
	}

	return ret;
}

int BCS::
operator()(CPU* cpu)
{
	offset = cpu->getRelative();
	int ret = 2;
	bit = cpu->C;

	addr = cpu->getPC();
	if (cpu->C) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		addr = npc;
		cpu->setPC(npc);
	}

	return ret;
}

int BEQ::
operator()(CPU* cpu)
{
	offset = cpu->getRelative();
	int ret = 2;

	bit = cpu->Z;
	addr = cpu->getPC();
	if (cpu->Z) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		addr = npc;
		cpu->setPC(npc);
	}

	return ret;
}

int BMI::
operator()(CPU* cpu)
{
	offset = cpu->getRelative();
	int ret = 2;

	bit = cpu->N;
	addr = cpu->getPC();
	if (cpu->N) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		addr = npc;
		cpu->setPC(npc);
	}

	return ret;
}

int BNE::
operator()(CPU* cpu)
{
	offset = cpu->getRelative();
	int ret = 2;

	bit = cpu->Z;
	addr = cpu->getPC();
	if (!cpu->Z) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		addr = npc;
		cpu->setPC(npc);
	}

	return ret;
}

int BPL::
operator()(CPU* cpu)
{
	char offset = cpu->getRelative();
	int ret = 2;

	bit = cpu->N;
	addr = cpu->getPC();
	if (!cpu->N) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		cpu->setPC(npc);
	}

	return ret;
}

int BVC::
operator()(CPU* cpu)
{
	char offset = cpu->getRelative();
	int ret = 2;

	bit = cpu->V;
	addr = cpu->getPC();
	if (!cpu->V) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		cpu->setPC(npc);
	}

	return ret;
}

int BVS::
operator()(CPU* cpu)
{
	char offset = cpu->getRelative();
	int ret = 2;

	bit = cpu->V;
	addr = cpu->getPC();
	if (cpu->V) {
		ret++;
		unsigned short opc = addr;
		unsigned short npc = opc + offset;

		if ((opc >> 8) != (npc >> 8)) {
			ret++;
		}

		cpu->setPC(npc);
	}

	return ret;
}

BranchOp::
~BranchOp()
{

}

} /* namespace cpu */
