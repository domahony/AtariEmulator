/*
 * Clock2.h
 *
 *  Created on: May 9, 2015
 *      Author: domahony
 */

#ifndef CLOCK2_H_
#define CLOCK2_H_

#include <iostream>
#include <ctime>

#define BILLION (1000000000L)

namespace emulator {

class Clock2 {
public:
	Clock2(long hz) :
		hz(hz),
		control_rate(1.L/hz),
		ticks(0),
		tick_time(0)
	{
		clock_gettime(CLOCK_MONOTONIC, &t0);
		last_tick = t0;
	}

	bool tick() {

		/*
		++ticks;
		return true;
		*/

		struct timespec cur_tick;
		clock_gettime(CLOCK_MONOTONIC, &cur_tick);

		double delta = ((cur_tick.tv_sec - last_tick.tv_sec) * BILLION) + (cur_tick.tv_nsec - last_tick.tv_nsec);

		delta /= BILLION;

		std::cout.precision(10);
		//auto delta = cur_tick.tv_sec + static_cast<double>(cur_tick.tv_nsec) / (1000 * 1000 * 1000) - last_tick.tv_sec + static_cast<double>(last_tick.tv_nsec) / (1000 * 1000 * 1000);
		//std::cout << "Delta: " << std::fixed << delta << std::endl;

		tick_time += delta;
		last_tick = cur_tick;

		if (tick_time < control_rate) {
			return false;
		}
		tick_time -= control_rate;

		if (!(++ticks % 500000)) {

			auto total = cur_tick.tv_sec
					+ (static_cast<double>(cur_tick.tv_nsec) / (BILLION))
					- t0.tv_sec + (static_cast<double>(t0.tv_nsec) / (BILLION));
			std::cout << "HZ: " << std::fixed << static_cast<double>(ticks) / total << std::endl;
		}

		return true;
	}

	double ticks_per_second() {
			struct timespec cur_tick;
			clock_gettime(CLOCK_MONOTONIC, &cur_tick);
			auto total = cur_tick.tv_sec + static_cast<double>(cur_tick.tv_nsec) / (1000 * 1000 * 1000) - t0.tv_sec + static_cast<double>(t0.tv_nsec) / (1000 * 1000 * 1000);
			return static_cast<double>(ticks) / total;
	}

	long getHZ() const {
		return hz;
	}

private:
	long hz;
	double control_rate;
	struct timespec last_tick;
	double tick_time;
	long ticks;
	struct timespec t0;
};

} /* namespace emulator */

#endif /* CLOCK2_H_ */
