/*
 * Clock.h
 *
 *  Created on: May 2, 2015
 *      Author: domahony
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <ctime>
#include <iostream>

namespace emulator {

class Clock {
public:
	Clock(long hz) :
		hz(hz),
		control_rate(1.L/hz),
		last_tick(clock()),
		tick_time(0.),
		t0(last_tick),
		ticks(0)
	{
		using namespace std;
		cout.precision(10);
		cout << fixed << "Control Rate: "  << control_rate << endl;
	}

	bool tick() {
		auto cur_tick = clock();
		auto delta = static_cast<double>(cur_tick - last_tick) / CLOCKS_PER_SEC;

		tick_time += delta;
		last_tick = cur_tick;

		if (tick_time < (control_rate)) {
			return false;
		}

		tick_time -= control_rate;
		if (!(++ticks % 100000)) {
			std::cout << "HZ: " << static_cast<double>(ticks)/(static_cast<double>(clock() - t0) / CLOCKS_PER_SEC) << std::endl;
		}

		return true;
	}

	double ticks_per_second() {

			return static_cast<double>(ticks)/(static_cast<double>(clock() - t0) / CLOCKS_PER_SEC);
	}

	virtual ~Clock()
	{

	}

private:
	long hz;
	double control_rate;
	clock_t last_tick;
	double tick_time;
	long ticks;
	clock_t t0;
};

} /* namespace emulator */

#endif /* CLOCK_H_ */
