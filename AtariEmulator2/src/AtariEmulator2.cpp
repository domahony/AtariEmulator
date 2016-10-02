/*
 ============================================================================
 Name        : AtariEmulator.cpp
 Author      : Dave O'Mahony
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */

#include <iostream>
#include "Video.h"
#include "CPU.h"
#include "Logging.h"
#include "Debugger.h"
#include "DBGCommand.h"


int main(int argc, char **argv)
{
	video::Video video;
	//cpu::CPU cpu(2 * 1000 * 1000 * 20, video.get_refresh_rate(), &video);
	cpu::CPU cpu(1790000, video.get_refresh_rate(), &video);
	bool quit = false;

	dbg::Debugger dbg = dbg::Debugger(&cpu);

	LOG::init();

	while( !quit ) {

		if (dbg.execute())
			cpu.execute();

		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 )
		{

			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
					video.resize(e.window.data1, e.window.data2);
				break;
			}
		}

		//std::cout << std::fixed << "Ticks Per Second: " << cpu.ticks_per_second() << std::endl;
		//video.swapWindow();
	}

	//std::cout << std::fixed << "Ticks Per Second: " << cpu.ticks_per_second() << std::endl;
}
