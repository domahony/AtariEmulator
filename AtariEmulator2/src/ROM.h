/*
 * ROM.h
 *
 *  Created on: Jan 30, 2015
 *      Author: domahony
 */

#ifndef ROM_H_
#define ROM_H_

#include <iostream>
#include <vector>
#include <string>

namespace address {

using std::string;
using std::vector;

class ROM {
public:
	ROM(const string&);
	virtual ~ROM();

	unsigned char read(unsigned short addr) const {
		return rom.at(addr & mask);
	}

	void write(unsigned short addr, unsigned char val) {

	}

	std::string get_path() const {
		return path;
	}

private:
	vector<unsigned char> rom;
	unsigned int mask;
	std::string path;
};

} /* namespace address */

#endif /* ROM_H_ */
