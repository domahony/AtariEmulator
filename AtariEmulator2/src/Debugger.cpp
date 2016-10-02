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


namespace dbg {

using namespace std;
using json = nlohmann::json;

static string cmd_fname;

static void cleanup() {
	unlink(cmd_fname.c_str());
}

Debugger::Debugger(cpu::CPU* cpu) : cpu(cpu), running(false) {

	// TODO Auto-generated constructor stub

	pid_t pid = getpid();

	std::stringstream dbg_cmd;

	mkdir("/tmp/dbg", 0700);

	dbg_cmd << "/tmp/dbg/cmd_" << pid;

	auto info_fd = open("/tmp/dbg/info", O_TRUNC|O_CREAT|O_WRONLY, 0600);

	json jinfo;
	jinfo["cmd"] = dbg_cmd.str();

	auto tmp = jinfo.dump(1);

	cout << tmp << endl;

	write(info_fd, tmp.c_str(), tmp.length());
	close(info_fd);

	cmd_fname = dbg_cmd.str();

	struct sockaddr_un addr;
	if ((pfd[0].fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	pfd[1].fd = -1;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, cmd_fname.c_str(), sizeof(addr.sun_path)-1);

	if (bind(pfd[0].fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	if (listen(pfd[0].fd, 5) == -1) {
		cerr << strerror(errno) << endl;
		exit(-1);
	}

	cout << "FD's created!" << endl;

	atexit(cleanup);
}

static bool read_cmd(int fd, cpu::CPU* cpu)
{

	char cmd[256];
	bool ret = false;
	cout << "Data ready to read" << endl;
	int nread = read(fd, cmd, sizeof(cmd) - 1);

	cout << "Read: " << nread << " bytes" << endl;

	if (nread < 0) {
		cerr << strerror(errno) << endl;
		return ret;
	}

	if (nread == 0) {
		return ret;
	}

	cmd[nread] = 0;

	auto jcmd = json::parse(cmd);

	cout << "Read: '" << jcmd.dump(1) << "'" << endl;

	if (jcmd["cmd"] == "run") {
		ret = true;
	} else if (jcmd["cmd"] == "stop") {
		ret = false;
	}

	json jdata;
	jdata["registers"] =
			{
					{"ACC", cpu->getAccumulator()},
					{"X", cpu->getX()},
					{"Y", cpu->getX()},
					{"FLAGS", cpu->getFlags()},
					{"PC", cpu->getPC()},
					{"SP", cpu->getSP()},
			};

	stringstream data;
	data << jdata.dump(1);

	cout << "About to write '" << data.str() << "' " << data.str().length() << endl;

	int nwrote = write(fd, data.str().c_str(), data.str().length());

	cout << "Wrote nbytes: " << nwrote << endl;

	return ret;
}

bool Debugger::
execute()
{
	pfd[0].events = POLLIN;
	pfd[1].events = POLLIN;

	char cmd[256];

	if (pfd[1].fd > 0) {
		pfd[0].fd = abs(pfd[0].fd) * -1;
	}

	//cout << "Checking for data" << endl;
	int nready = poll(pfd, sizeof(pfd)/sizeof(struct pollfd), 0);

	bool ret = running;

	if (nready) {

		cout << hex << pfd[1].revents << endl;

		cout << "nready: " << nready << endl;

		if (pfd[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
			cerr << strerror(errno) << endl;
			exit(-1);
		}

		if (pfd[1].revents & (POLLERR | POLLHUP | POLLNVAL)) {

			close(pfd[1].fd);
			pfd[1].fd = -1 * abs(pfd[0].fd);
			pfd[0].fd = abs(pfd[0].fd);
			return ret;
		}

		if (pfd[0].revents & POLLIN) {

			cout << "Here??" << endl;
			pfd[1].fd = accept(pfd[0].fd, nullptr, nullptr);

			ret = read_cmd(pfd[1].fd, cpu);

		}

		if (pfd[1].revents & POLLIN) {
			ret = read_cmd(pfd[1].fd, cpu);
		}
	}

	running = ret;
	return running;
}

Debugger::~Debugger() {
	// TODO Auto-generated destructor stub
}

} /* namespace dbg */
