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

	}

	void write(unsigned short addr, unsigned char val) {

	}

	void tick() const {

		// 29.97 fps * 262.5 lines
		// 7867.125 lps
		// 2,000,000 tps
		// cpu / lps

		int acc = 0;
		int lps = 29.97 * 262.5;
		int vcount = 0;

		acc += lps;

		if (acc >= 2000000) {
			vcount++;
		}

		acc %= 2000000;
	}

};

} /* namespace address */

#endif /* ANTIC_H_ */
