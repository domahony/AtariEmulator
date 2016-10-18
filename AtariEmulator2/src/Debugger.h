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
#include <list>
#include <memory>

namespace cpu {
	class CPU;
}

namespace dbg {

template <class T> class SC {
	void cycle() {
		condition.cycle();
	}

	bool check() {
		return condition.check();
	}

	bool expired() {
		return condition.expired();
	}

private:
	T condition;
};

class StopCondition {
public:
	virtual void cycle() = 0;
	virtual bool check() = 0;
	virtual bool expired() = 0;

	virtual ~StopCondition() {

	}
};

class PCCount : public StopCondition {

public:
	PCCount(int cnt =1) : cnt(cnt) { }

	void cycle() {
		--cnt;
	}

	bool check() {
		return cnt <= 0;
	}

	bool expired() {
		return cnt <= 0;
	}

private:
	int cnt;
};

class DBGCommand;

enum class DBGState {
	stopped,
	running,
};

class Debugger {
public:
	Debugger(cpu::CPU* cpu);
	virtual ~Debugger();

	std::unique_ptr<DBGCommand> get_command();

	bool execute();
	void write_state();

private:

	void read_cmd();
	void handle_cmd();
	bool pump_stop_conditions();

	struct pollfd pfd[2];
	DBGState state;
	cpu::CPU* cpu;

	std::list<std::shared_ptr<StopCondition>> stop_conditions;

};

} /* namespace dbg */

#endif /* DEBUGGER_H_ */
