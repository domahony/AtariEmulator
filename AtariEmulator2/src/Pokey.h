/*
 * Pokey.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef POKEY_H_
#define POKEY_H_

namespace address {

class Pokey {
public:
	Pokey();
	virtual ~Pokey();

	unsigned char read(unsigned short addr) const {

	}
	void write(unsigned short addr, unsigned char val) {

	}

};
} /* namespace address */

#endif /* POKEY_H_ */
