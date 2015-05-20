/*
 * GTIA.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef GTIA_H_
#define GTIA_H_

namespace address {

class GTIA {
public:
	GTIA();
	virtual ~GTIA();

	unsigned char read(unsigned short addr) const {

	}

	void write(unsigned short addr, unsigned char val) {

	}

};

} /* namespace address */

#endif /* GTIA_H_ */
