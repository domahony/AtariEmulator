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

int main(int argc, char **argv)
{
	video::Video video;
	//cpu::CPU cpu(2 * 1000 * 1000 * 20, video.get_refresh_rate(), &video);
	cpu::CPU cpu(1790000, video.get_refresh_rate(), &video);
	bool quit = false;

	LOG::init();

	while( !quit ) {

		cpu.execute();
		SDL_Event e;
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		std::cout << std::fixed << "Ticks Per Second: " << cpu.ticks_per_second() << std::endl;
		//video.swapWindow();
	}

	std::cout << std::fixed << "Ticks Per Second: " << cpu.ticks_per_second() << std::endl;
}
