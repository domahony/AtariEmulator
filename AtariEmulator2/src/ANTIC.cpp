/*
 * ANTIC.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#include "ANTIC.h"

namespace address {

ANTIC::ANTIC() : vcount(0), vcount_acc(0), r_reg(15, 0), w_reg(15, 0), nmi_trigger(false)
{
	// TODO Auto-generated constructor stub

}

bool ANTIC::
NMI()
{
	// only trigger nmi once...
	bool ret = nmi_trigger;
	nmi_trigger = false;

	return ret;
}

void ANTIC::
tick()
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

		if ((w_reg[Reg::NMIEN] >> 6) & 0x1) {
			r_reg[Reg::NMIST] |= (1 << 6);
			nmi_trigger = true;
		}
	}

	vcount_acc %= 1790000;
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
		case Reg::NMIEN :
			w_reg[Reg::NMIEN] = val;
			break;
		case Reg::NMIRES :
			r_reg[Reg::NMIST] &= val;
			break;
		default:
			;
		}

}

} /* namespace address */
