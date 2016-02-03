/*
 * ANTIC.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef ANTIC_H_
#define ANTIC_H_

namespace address {

class ANTIC {
public:
	ANTIC();
	virtual ~ANTIC();

	unsigned char read(unsigned short addr) const {

		unsigned char ret = 0;

		switch (addr) {
		case 0xB :
			ret = vcount;
			break;
		default:
			;
		}

		return ret;
	}

	void write(unsigned short addr, unsigned char val) {

	}

	void tick() {

		// 29.97 fps * 262.5 lines
		// 7867.125 lps
		// 2,000,000 tps
		// cpu / lps

		int lps = 29.97 * 2 * 131.25;

		vcount_acc += lps;

		if (vcount_acc >= 2000000) {
			vcount++;
		}

		if (vcount > 130) {
			vcount = 0;
		}

		vcount_acc %= 2000000;
	}

private:
	int vcount;
	int vcount_acc;
};

} /* namespace address */

#endif /* ANTIC_H_ */
