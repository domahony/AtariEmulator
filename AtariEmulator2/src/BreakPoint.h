/*
 * BreakPoint.h
 *
 *  Created on: Sep 19, 2016
 *      Author: domahony
 */

#ifndef SRC_BREAKPOINT_H_
#define SRC_BREAKPOINT_H_

#include "CPU.h"

namespace dbg {

class BreakPoint {
public:
	BreakPoint() :lineno(0), enabled(false) {

	}

	bool check(cpu::CPU* cpu) {
		if (enabled && cpu->getPC() == lineno) {
			return true;
		} else {
			return false;
		}
	}

	virtual ~BreakPoint();

private:
	unsigned short lineno;
	bool enabled;
};

} /* namespace dbg */

#endif /* SRC_BREAKPOINT_H_ */
