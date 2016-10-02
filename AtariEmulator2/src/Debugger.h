/*
 * Debugger.h
 *
 *  Created on: Sep 18, 2016
 *      Author: domahony
 */

#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#include <memory>
#include <poll.h>

namespace cpu {
	class CPU;
}

namespace dbg {

class DBGCommand;

class Debugger {
public:
	Debugger(cpu::CPU* cpu);
	virtual ~Debugger();

	std::unique_ptr<DBGCommand> get_command();

	bool execute();

private:
	struct pollfd pfd[2];
	bool running;
	cpu::CPU* cpu;

};

} /* namespace dbg */

#endif /* DEBUGGER_H_ */
