/*
 * Debugger.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: domahony
 */

#include "Debugger.h"

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sstream>
#include <fstream>

#include <poll.h>
#include <cstring>

#include "json.hpp"
#include <functional>

#include "DBGCommand.h"
#include "CPU.h"
#include <cstdlib>

#define LISTENER_FD (pfd[0].fd)
#define DATA_FD (pfd[1].fd)

namespace dbg {

using namespace std;
using json = nlohmann::json;

static string cmd_fname;

static void cleanup() {
	unlink(cmd_fname.c_str());
}

Debugger::Debugger(cpu::CPU* cpu) : cpu(cpu), state(DBGState::stopped) {

	// TODO Auto-generated constructor stub

	pid_t pid = getpid();

	std::stringstream dbg_cmd;

	mkdir("/tmp/dbg", 0700);

	dbg_cmd << "/tmp/dbg/cmd_" << pid;

	auto info_fd = open("/tmp/dbg/info", O_TRUNC|O_CREAT|O_WRONLY, 0600);

	json jinfo;
	jinfo["cmd"] = dbg_cmd.str();
	jinfo["rom"] = {
			{"path", cpu->get_rom_path()},
			{"offset", cpu->get_rom_offset()}
	};

	auto tmp = jinfo.dump(1);

	cout << tmp << endl;

	if (write(info_fd, tmp.c_str(), tmp.length()) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	close(info_fd);

	cmd_fname = dbg_cmd.str();

	struct sockaddr_un addr;
	if ((LISTENER_FD = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	pfd[1].fd = -1;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, cmd_fname.c_str(), sizeof(addr.sun_path)-1);

	if (bind(LISTENER_FD, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	if (listen(LISTENER_FD, 5) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	cout << "FD's created!" << endl;

	atexit(cleanup);
}

void Debugger::
handle_cmd()
{

	char cmd[256];
	bool ret = false;
	cout << "Data ready to read" << endl;
	int nread = read(DATA_FD, cmd, sizeof(cmd) - 1);

	cout << "Read: " << nread << " bytes" << endl;

	if (nread < 0) {
		cerr << strerror(errno) << endl;
		return;
	}

	if (nread == 0) {
		return;
	}

	cmd[nread] = 0;

	auto jcmd = json::parse(cmd);

	cout << "Read: '" << jcmd.dump(1) << "'" << endl;

	if (jcmd["cmd"] == "run") {
		state = DBGState::running;
	} else if (jcmd["cmd"] == "stop") {
		state = DBGState::stopped;
	} else if (jcmd["cmd"] == "step") {
		stop_conditions.push_back(std::shared_ptr<StopCondition>(new PCCount(1)));
		state = DBGState::running;
	}
}

void Debugger::
write_state()
{
	json jdata;
	jdata["registers"] =
			{
					{"ACC", cpu->getAccumulator()},
					{"X", cpu->getX()},
					{"Y", cpu->getY()},
					{"FLAGS", cpu->getFlags()},
					{"PC", cpu->getPC()},
					{"SP", cpu->getSP()},
			};

	stringstream data;
	data << jdata.dump(1);

	cout << "About to write '" << data.str() << "' " << data.str().length() << endl;

	int nwrote = write(DATA_FD, data.str().c_str(), data.str().length());

	cout << "Wrote nbytes: " << nwrote << endl;
}

bool Debugger::
pump_stop_conditions()
{
	bool ret = false;
	cout << "Here!!" << endl;
	for (auto i = stop_conditions.begin(); i != stop_conditions.end(); ++i) {
		(*i)->cycle();

		if ((*i)->check()) {
			state = DBGState::stopped;
			ret = true;
		}

		if ((*i)->expired()) {
			i = stop_conditions.erase(i);
		}
		cout << "Iter!" << endl;
	}

	return ret;
}

bool Debugger::
execute()
{

	switch (state) {
	case DBGState::running:

		if (!cpu->execute()) {
			cout << "TICK" << endl;
			return false;
		}
		// to next CPU cycle

		if (pump_stop_conditions()) { // update state based on any stop conditions
			write_state();
		}

		read_cmd(); //update state based on any new commands

		break;

	case DBGState::stopped:

		read_cmd(); //update state and/or stop condition based on any new commands;
		break;
		/*
		 * workflow for STEP
		 * new stop condition is execute 1 instruction
		 * state is running
		 * next loop iteration, cpu->execute() is called (1 instruction)
		 * pump_stop_condition() causes the 1 instruction condition to match -> state goes to stop; call changeToStop();
		 * changeToStop() should write state back to dbg controller
		 *
		 * workflow for RUN cmd
		 * set state to running
		 * no new stop condition
		 * * execute
		 * * pump
		 *  * read_cmd
		 *
		 *  workflow for STOP cmd (assumming already running)
		 *  * execute a cycle
		 *  * pump() (nothing triggers)
		 *  * read_cmd() -> call changeToStop()
		 */

	}
	return true;
}

void Debugger::
read_cmd()
{
	pfd[0].events = POLLIN;
	pfd[1].events = POLLIN;

	char cmd[256];

	if (pfd[1].fd > 0) {
		pfd[0].fd = abs(pfd[0].fd) * -1;
	}

	bool ret = false;

	//cout << "Checking for data" << endl;
	int nready = poll(pfd, sizeof(pfd)/sizeof(struct pollfd), 0);

	if (nready) {

		cout << hex << pfd[1].revents << endl;
		cout << "nready: " << nready << endl;

		if (pfd[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
			cerr << strerror(errno) << endl;
			state = DBGState::stopped;
			//exit(-1);
			return;
		}

		if (pfd[1].revents & (POLLERR | POLLHUP | POLLNVAL)) {

			close(pfd[1].fd);
			pfd[1].fd = -1 * abs(pfd[0].fd);
			pfd[0].fd = abs(pfd[0].fd);
			state = DBGState::stopped;

		}

		if (pfd[0].revents & POLLIN) {

			cout << "Here??" << endl;
			pfd[1].fd = accept(pfd[0].fd, nullptr, nullptr);
			handle_cmd();

		}

		if (pfd[1].revents & POLLIN) {
			handle_cmd();
		}
	}
}

Debugger::~Debugger() {
	// TODO Auto-generated destructor stub
}

} /* namespace dbg */
