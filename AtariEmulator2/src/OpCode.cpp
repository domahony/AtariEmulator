/*
 * OpCode.cpp
 *
 *  Created on: May 10, 2015
 *      Author: domahony
 */

#include "OpCode.h"
#include "CPU.h"

namespace cpu {

std::string OpCode::
to_string(CPU *cpu) {
	return mnemonic();
}

unsigned char Immediate::
read(CPU *cpu) {
	addr = cpu->readPCandInc();
	return addr;
}

unsigned char ZeroPage::
read(CPU* cpu) {
	addr = cpu->readPCandInc();
	return cpu->read(addr);
}

void ZeroPage::
write(CPU* cpu, unsigned char val) {
	addr = cpu->readPCandInc();
	value = val;
	return cpu->write(addr, value);
}

unsigned char ZeroPageWithXIdx::
read(CPU* cpu) {
	addr = cpu->zeroPageWithXIdx();
	return cpu->read(addr);
}

void ZeroPageWithXIdx::
write(CPU* cpu, unsigned char val) {
	value = val;
	addr = cpu->zeroPageWithXIdx();
	cpu->write(addr, value);
}

unsigned char ZeroPageWithYIdx::
read(CPU* cpu) {
	addr = cpu->zeroPageWithYIdx();
	return cpu->read(addr);
}

void ZeroPageWithYIdx::
write(CPU* cpu, unsigned char val) {
	addr = cpu->zeroPageWithYIdx();
	value = val;
	return cpu->write(addr, val);
}

unsigned char Absolute::
read(CPU* cpu) {
	addr = get_address(cpu);
	value = cpu->read(addr);
	return value;
}

unsigned short Absolute::
get_address(CPU *cpu) {
	addr = cpu->absoluteAddress();
	return addr;
}

void Absolute::
write(CPU* cpu, unsigned char val) {
	addr = cpu->absoluteAddress();
	value = val;
	cpu->write(addr, value);
}

unsigned char AbsoluteWithX::
read(CPU* cpu) {
	addr = cpu->absoluteAddressX(_tcount);
	value = cpu->read(addr);
	return value;
}

void AbsoluteWithX::
write(CPU* cpu, unsigned char val) {
	addr = cpu->absoluteAddressX(_tcount);
	value = val;
	cpu->write(addr, value);
}

unsigned char AbsoluteWithY::
read(CPU* cpu) {
	addr= cpu->absoluteAddressY(_tcount);
	return addr;
}

void AbsoluteWithY::
write(CPU* cpu, unsigned char val) {
	addr = cpu->absoluteAddressY(_tcount);
	value = val;
	cpu->write(addr, value);
}

unsigned char ZpIdxIndirect::
read(CPU* cpu) {
	addr = cpu->getZpIdxIndirect();
	return addr;
}

void ZpIdxIndirect::
write(CPU* cpu, unsigned char val) {
	 cpu->setZpIdxIndirect(val);
}

unsigned char ZpIndirectIdxWithY::
read(CPU* cpu)
{
	addr = cpu->getZpIndirectIdxWithY(_tcount);
	return cpu->read(addr);
}

void ZpIndirectIdxWithY::
write(CPU* cpu, unsigned char val)
{
	addr = cpu->getZpIndirectIdxWithY(_tcount);
	value = val;
	cpu->write(addr, val);
}

unsigned char Indirect::
read(CPU* cpu)
{
	addr = get_address(cpu);
	value = cpu->read(addr);
	return value;
}

unsigned short Indirect::
get_address(CPU* cpu) {
	addr = cpu->getIndirect();
	return addr;
}

unsigned char Accumulator::
read(CPU* cpu)
{
	return cpu->getAccumulator();
}

void Accumulator::
write(CPU* cpu, unsigned char val)
{
	return cpu->setAccumulator(val);
}


} /* namespace cpu */
