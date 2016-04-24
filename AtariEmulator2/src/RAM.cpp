/*
 * RAM.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: domahony
 */

#include "RAM.h"
#include <fstream>
#include <iostream>
#include <cstring>


namespace address {

RAM::RAM() {
	// TODO Auto-generated constructor stub

}

RAM::~RAM() {
	// TODO Auto-generated destructor stub
}

void RAM::
dump(const std::string& fname) const
{
	std::ofstream output(fname, std::ofstream::binary);

	if (!output.good()) {
		std::cerr << "Not Good!!" << std::endl;
		std::cerr << "Error: " << strerror(errno);
	}

	std::cout << "Stream size: " << ram.size() << std::endl;

	for (auto i = ram.begin(); i!= ram.end(); ++i) {
		output.put(*i);
	}

	output.flush();

	output.close();
}

} /* namespace address */
