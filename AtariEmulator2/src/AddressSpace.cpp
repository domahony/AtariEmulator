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
#include "Pokey.h"

namespace address {

using std::shared_ptr;

AddressSpace::AddressSpace() :
		os(new ROM("/home/domahony/Projects/atariROMs/new/REVBNTSC.ROM")),
		cartridgeA(new ROM("/home/domahony/Projects/atariROMs/REVA.ROM")),
		ram(new RAM(0xA000)),
		ramB(new RAM(0x8000)),
		pokey(new Pokey()),
		antic(new ANTIC())
{


}

AddressSpace::~AddressSpace() {

}

void AddressSpace::
dump_ram()
{
	ram->dump("/tmp/ram1.bin");
	ramB->dump("/tmp/ramB.bin");

}

unsigned char AddressSpace::read(const unsigned short addr) const {

	unsigned char ret;
	unsigned short a = addr;
	std::string chip;

	if (addr >= 0xD800) {

		ret = os->read(addr - 0xD800);
		chip = "OS ROM";
		//a -= 0xD800;

	} else if (addr >= 0xD400) {

		ret = antic->read(addr - 0xD400);
		chip = "CHIP ANTIC";
		//a -= 0xd400;

	} else if (addr >= 0xD300) {

		ret = pia->read(addr - 0xD300);
		chip = "CHIP PIA";
		//a -= 0xd300;

	} else if (addr >= 0xD200) {

		ret = pokey->read(addr - 0xD200);
		chip = "CHIP POKEY";
		//a -= 0xd200;

	} else if (addr >= 0xD000) {

		ret = gtia->read(addr - 0xD000);
		chip = "CHIP GTIA";
		//a -= 0xd000;
	} else if (addr >= 0xC000)	 {
		return 0x0;
	} else if (addr >= 0xA000) {

		ret = cartridgeA->read(addr - 0xA000); //!!!!!CONSIDER SHIFTING this up by 0x1000 (4K)
		chip = "CHIP CARTA";
		//a -= 0xa000;

	} else if (addr >= 0x8000) {

		if (cartridgeB) {

			ret = cartridgeB->read(addr - 0x8000);
			chip = "CHIP CARTB";
			//a -= 0x8000;

		} else {

			ret = ramB->read(addr - 0x8000);
			chip = "RAMB";
			//a -= 0x8000;
		}


	} else {
		ret = ram->read(addr);
		chip = "RAM";
	}

	std::cout << chip << " READ: " << std::hex << a << " " << static_cast<unsigned short>(ret) << std::endl;
	return ret;
}

void AddressSpace::write(unsigned short addr, unsigned char val) {

	std::string chip;

	if (addr >= 0xD800) {
		chip = "OS ROM";
		os->write(addr - 0xD800, val);
		//addr -= 0xd800;
	} else if (addr >= 0xD400) {
		antic->write(addr - 0xD400, val);
		chip = "CHIP ANTIC";
		//addr -= 0xd400;
	} else if (addr >= 0xD300) {
		pia->write(addr - 0xD300, val);
		chip = "CHIP PIA";
		//addr -= 0xd300;
	} else if (addr >= 0xD200) {
		pokey->write(addr - 0xD200, val);
		chip = "CHIP POKEY";
		//addr -= 0xd200;
	} else if (addr >= 0xD000) {
		gtia->write(addr - 0xD000, val);
		chip = "CHIP GTIA";
		//addr -= 0xd000;
	} else if (addr >= 0xC000) {

	} else if (addr >= 0xA000) {
		cartridgeA->write(addr - 0xA000, val);
		chip = "CHIP CARTA";
		//addr -= 0xa000;
	} else if (addr >= 0x8000) {

		if (cartridgeB) {
			cartridgeB->write(addr - 0x8000, val);
			chip = "CHIP CARTB";
			//addr -= 0x8000;
		} else {
			ramB->write(addr - 0x8000, val);
			chip = "RAMB";
			//addr -= 0x8000;
		}

	} else {
		ram->write(addr, val);
		chip = "RAM";
	}
	std::cout << chip << " WRITE: " << std::hex << addr << " " << static_cast<unsigned short>(val) << std::endl;
}

} /* namespace address */
