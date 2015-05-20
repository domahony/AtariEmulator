/*
 * RAM.h
 *
 *  Created on: Mar 5, 2015
 *      Author: domahony
 */

#ifndef RAM_H_
#define RAM_H_

#include <vector>

namespace address {

class RAM {
public:
	RAM(int size) : ram() {
		ram.resize(size);
	}
	virtual ~RAM();

	unsigned char read(unsigned short addr) const {
		return ram.at(addr);
	}

	void write(unsigned short addr, unsigned char val) {
		ram[addr] = val;
	}

private:
	RAM();

private:
	std::vector<unsigned char> ram;
};

} /* namespace address */

#endif /* RAM_H_ */
