/*
 * ANTIC.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef ANTIC_H_
#define ANTIC_H_

#include <iostream>
#include <vector>

namespace video {
 class Video;
}

namespace address {

class AddressSpace;

class ANTIC {
public:
	ANTIC(video::Video*);
	virtual ~ANTIC();

	unsigned char read(unsigned short addr) const;

	void write(unsigned short addr, unsigned char val);

	bool NMI();

	void tick(AddressSpace*);


private:
	int vcount;
	int vcount_acc;
	int tcount;

	enum Reg {
		DMACTL = 0x00,
		CHACTL = 0x01,
		DLISTL = 0x02,
		DLISTH = 0x03,
		HSCROL = 0x04,
		VSCROL = 0x05,
		PMBASE = 0x07,
		CHBASE = 0x09,
		WSYNC  = 0x0A,
		VCOUNT = 0x0B,
		PENH   = 0x0C,
		PENV   = 0x0D,
		NMIEN  = 0x0E,
		NMIRES = 0x0F,
		NMIST  = 0x0F,
	};

	std::vector<unsigned char> r_reg;
	std::vector<unsigned char> w_reg;

	unsigned char nmi_trigger;
	bool vblank;

	void do_dma(AddressSpace *);

	void do_char(unsigned char, AddressSpace *, int, int, std::vector<unsigned short>&, int&);

	video::Video *video;

};

} /* namespace address */

#endif /* ANTIC_H_ */
