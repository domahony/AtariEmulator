/*
 * AddressSpace.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#include <iostream>
#include "AddressSpace.h"
#include "ROM.h"
#include "RAM.h"

namespace address {

AddressSpace::AddressSpace() :
		os(new ROM("/home/domahony/Projects/atariROMs/new/REVBNTSC.ROM")),
		cartridgeA(new ROM("/home/domahony/Projects/atariROMs/REVA.ROM")),
		ram(new RAM(0xA000)),
		ramB(new RAM(0x8000)),
		antic(new ANTIC())
{


}

AddressSpace::~AddressSpace() {

}

unsigned char AddressSpace::read(const unsigned short addr) const {

	if (addr >= 0xD800) {
		return os->read(addr - 0xD800);
	} else if (addr >= 0xD400) {
		std::cout << "READ ANTIC: " << std::hex << addr - 0xd400 << std::endl;
		return antic->read(addr - 0xD400);
	} else if (addr >= 0xD300) {
		std::cout << "READ PIA: " << std::hex << addr - 0xd300 << std::endl;
		return pia->read(addr - 0xD300);
	} else if (addr >= 0xD200) {
		std::cout << "READ POKEY: " << std::hex << addr - 0xd200 << std::endl;
		return pokey->read(addr - 0xD200);
	} else if (addr >= 0xD000) {
		std::cout << "READ GTIA: " << std::hex << addr - 0xd000 << std::endl;
		return gtia->read(addr - 0xD000);
	} else if (addr >= 0xA000) {
		std::cout << "READ CARTA: " << std::hex << addr - 0xa000 << std::endl;
		return cartridgeA->read(addr - 0xA000);
	} else if (addr >= 0x8000) {

		if (cartridgeB) {
		std::cout << "READ CARTB: " << std::hex << addr - 0x8000 << std::endl;
			return cartridgeB->read(addr - 0x8000);
		} else {
		std::cout << "READ RAMB: " << std::hex << addr - 0x8000 << std::endl;
			return ramB->read(addr - 0x8000);
		}


	} else {
		std::cout << "READ RAM: " << std::hex << addr << std::endl;
		return ram->read(addr);
	}
}

void AddressSpace::write(unsigned short addr, unsigned char val) {

	if (addr >= 0xD800) {
		os->write(addr - 0xD800, val);
	} else if (addr >= 0xD400) {
		std::cout << "WRITE ANTIC: " << std::hex << addr - 0xd400 << std::endl;
		antic->write(addr - 0xD400, val);
	} else if (addr >= 0xD300) {
		std::cout << "WRITE PIA: " << std::hex << addr - 0xd300 << std::endl;
		pia->write(addr - 0xD300, val);
	} else if (addr >= 0xD200) {
		std::cout << "WRITE POKEY: " << std::hex << addr - 0xd200 << std::endl;
		pokey->write(addr - 0xD200, val);
	} else if (addr >= 0xD000) {
		std::cout << "WRITE GTIA: " << std::hex << addr - 0xd000 << std::endl;
		gtia->write(addr - 0xD000, val);
	} else if (addr >= 0xA000) {
		std::cout << "WRITE CARTA: " << std::hex << addr - 0xa000 << std::endl;
		cartridgeA->write(addr - 0xA000, val);
	} else if (addr >= 0x8000) {

		if (cartridgeB) {
			std::cout << "WRITE CARTB: " << std::hex << addr - 0x8000 << std::endl;
			cartridgeB->write(addr - 0x8000, val);
		} else {
			std::cout << "WRITE RAMB: " << std::hex << addr - 0x8000 << std::endl;
			ramB->write(addr - 0x8000, val);
		}


	} else {
		std::cout << "WRITE RAM: " << std::hex << addr << std::endl;
		ram->write(addr, val);
	}
}

} /* namespace address */
