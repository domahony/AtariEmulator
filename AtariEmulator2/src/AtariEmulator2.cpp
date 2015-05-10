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

int main(int argc, char **argv)
{
	video::Video video;
	cpu::CPU cpu;
	bool quit = false;

	while( !quit ) {

		if (!cpu.execute()) {

			SDL_Event e;
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			video.swapWindow();
		}
	}

	std::cout << std::fixed << "Ticks Per Second: " << cpu.ticks_per_second() << std::endl;
}
