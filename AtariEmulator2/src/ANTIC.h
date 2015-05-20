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

};

} /* namespace address */

#endif /* ANTIC_H_ */
