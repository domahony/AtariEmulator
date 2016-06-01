/*
 * ANTIC.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#include "ANTIC.h"
#include "AddressSpace.h"
#include "Video.h"

namespace address {


ANTIC::ANTIC(video::Video* v) : vcount(0), vcount_acc(0), r_reg(16, 0), w_reg(16, 0), nmi_trigger(0), vblank(false), video(v)
{
	// TODO Auto-generated constructor stub

}

bool ANTIC::
NMI()
{
	// only trigger nmi once...

	bool ret = (nmi_trigger & 0x1);
	nmi_trigger = nmi_trigger >> 1;

	return ret;
}

void ANTIC::
tick(AddressSpace *address_space)
{
	// 29.97 fps * 262.5 lines
	// 7867.125 lps
	// 2,000,000 tps
	// cpu / lps
	// 59.94005994


	int lps = 29.97 * 2 * 131.25;
	tcount++;

	/*
	if (tcount > 28933) {
		std::cout << std::endl;
		std::cout << "VERTICAL BLANK!!!" << std::endl;
		std::cout << std::endl;
		tcount = 0;
	}
	*/


	vcount_acc += lps;

	if (vcount_acc >= 1790000) {
		vcount++;
	}

	if (vcount > 130) {

		std::cout << std::endl;
		std::cout << "VERTICAL BLANK!!! " << std::dec << tcount << std::endl;
		std::cout << std::endl;
		tcount = 0;
		vcount = 0;
		vblank = true;

		if ((w_reg[Reg::DMACTL] >> 5) & 0x1) {
			//DMA is enabled
			do_dma(address_space);
		}
		//the code needs figure out what to draw at this point, and update the opengl context
		//the code needs to trigger an opengl screen swap too

		if ((w_reg[Reg::NMIEN] >> 6) & 0x1) {
			r_reg[Reg::NMIST] |= (1 << 6);
			nmi_trigger = 1; //trigger nmi on the next tick, for 1 tick
		}
	}

	vcount_acc %= 1790000;
}

void ANTIC::
do_dma(AddressSpace* as)
{
	unsigned short addr = (w_reg[Reg::DLISTH] << 8) | w_reg[Reg::DLISTL];

	unsigned short addrl = w_reg[Reg::DLISTL];
	unsigned short addrh = w_reg[Reg::DLISTH];

	std::cout << "Display List ADDR: " << addr << std::endl;

	std::vector<std::vector<unsigned char>> screen;

	unsigned short mem_pc;

	//need some way to break out of this loop

	int lineno = 0;
	while (true) {

		unsigned char val = as->read(addr);
		bool wait_for_vblank = false;
		unsigned char data = 0x0;

		std::cout << "DL VAL: " << std::hex << static_cast<unsigned short>(val) << std::endl;

		if ((val & 0xF) == 0) {

			// blank
			unsigned short num_blank_lines = (val >> 4) & 0x7;
			++addr;

		} else if ((val & 0xF) == 1) {

			unsigned char l = as->read(++addr);
			unsigned char h = as->read(++addr);
			addr = (h << 8) | l;

			wait_for_vblank = (val >> 6) & 0x1;


		} else {

			unsigned short mode = (val & 0xF);
			bool hscroll = (val >> 4) & 0x1;
			bool vscroll = (val >> 5) & 0x1;

			std::cout << "SCREEN MODE: " << std::hex << mode;

			if ((val >> 6) & 0x1) {

				unsigned char l = as->read(++addr);
				unsigned char h = as->read(++addr);
				mem_pc = (h << 8) | l;
				std::cout << " LMS: " << std::hex
						<< static_cast<unsigned short>(l) << " "
						<< static_cast<unsigned short>(h) << " "
						<< mem_pc << std::endl;
				++addr;

			} else {

				std::cout << std::endl;
				++addr;

			}

			std::vector<unsigned char> line;

			std::cout << "LINE NO: " << std::dec << lineno++ << std::endl;
			for (int i = 0; i < 40; i++) {
				std::cout << "LINE MEM: " << std::hex << mem_pc;
				auto data = as->read(mem_pc++);
				std::cout << " " << std::hex << static_cast<unsigned short>(data) << std::endl;

				line.push_back(data);
			}

			screen.push_back(line);
		}


		if (wait_for_vblank) {
			break;
		}

	}

	std::vector<unsigned short> buf;
	int npixels = 0;
	//return;
	std::cout << "SCREEN BEGIN" << std::endl;
	int y = 0;
	for (auto i = screen.begin(); i != screen.end(); ++i) {

		int x = 0;
		std::cout << std::dec << y << ": ";
		for (auto j = i->begin(); j != i->end(); ++j) {

			std::cout << std::hex << static_cast<unsigned short>(*j) << " ";
			if (*j) {
				do_char(*j, as, x, y, buf, npixels);
			}

			x += 8;
		}
		std::cout << std::endl;
		y += 8;
	}

	video->set_frame_buffer(buf.size(), &buf[0]);

	std::cout << "SCREEN END" << std::endl;

}

void ANTIC::
do_char(unsigned char c, AddressSpace* as, int x, int y, std::vector<unsigned short>& buf, int& npixels)
{
	unsigned short chbase = (w_reg[Reg::CHBASE] << 8);
	chbase += (c * 8);

	std::cout << std::hex << "Char Base: " << chbase << std::endl;
	std::cout << std::dec << "Starting Char at X: " << x << std::endl;

	for (unsigned short i = 0; i < 8; i++) {

		auto line = as->read(chbase + i);

		for (int j = 0; j < 8; j++) {
			std::cout << ((line & 0x80) ? "X" : " ");

			if (line & 0x80) {
				buf.push_back(x + j);
				buf.push_back(y + i);
				//buf.push_back(0xFF);
				//buf.push_back(0xFF);
				//buf.push_back(0xFF);
			}

			line = line << 1;
		}
		std::cout << std::endl;
	}
}

ANTIC::~ANTIC() {
	// TODO Auto-generated destructor stub
}

unsigned char ANTIC::
read(unsigned short addr) const
{

		unsigned char ret = 0;

		switch (addr) {
		case Reg::VCOUNT :
			ret = vcount;
			break;
		case Reg::NMIST :
			ret = r_reg[Reg::NMIST];
			break;
		default:
			;
		}

		return ret;
	}

void ANTIC::
write(unsigned short addr, unsigned char val)
{

	switch (addr) {
	case DMACTL:
		std::cout << "ANTIC Writing DMACTL " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case CHACTL:
		std::cout << "ANTIC Writing CHACTL " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case DLISTL:
		std::cout << "ANTIC Writing DLISTL " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case DLISTH:
		std::cout << "ANTIC Writing DLISTH " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case HSCROL:
		std::cout << "ANTIC Writing HSCROL " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case VSCROL:
		std::cout << "ANTIC Writing VSCROL " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case PMBASE:
		std::cout << "ANTIC Writing PMBASE " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case CHBASE:
		std::cout << "ANTIC Writing CHBASE " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case WSYNC:
		std::cout << "ANTIC Writing WSYNC " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case VCOUNT:
		std::cout << "ANTIC Writing VCOUNT " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case PENH:
		std::cout << "ANTIC Writing PENH " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case PENV:
		std::cout << "ANTIC Writing PENV " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[addr] = val;
		break;
	case Reg::NMIEN :
		std::cout << "ANTIC Writing NMIEN " << std::hex << static_cast<unsigned short>(val) << std::endl;
		w_reg[Reg::NMIEN] = val;
		break;
	case Reg::NMIRES :
		std::cout << "ANTIC Writing NMIRES " << std::hex << static_cast<unsigned short>(val) << std::endl;
		//r_reg[Reg::NMIST] &= val;
		r_reg[Reg::NMIST] = 0;
		break;
	default:
		;
	}
}

} /* namespace address */
