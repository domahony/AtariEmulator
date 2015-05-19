/*
 * Video.cpp
 *
 *  Created on: May 1, 2015
 *      Author: domahony
 */

#include <iostream>
#include "Video.h"
#include <SDL.h>
#include <SDL_opengl.h>

namespace video {

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Video::Video() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	//Create window
	gWindow = SDL_CreateWindow( "SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	gContext =  SDL_GL_CreateContext( gWindow );

	SDL_GL_SetSwapInterval( 1 );

	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

	refresh_rate = mode.refresh_rate;
	std::cout << "HZ: " << mode.refresh_rate << std::endl;
}

Video::~Video() {
	// TODO Auto-generated destructor stub
}

} /* namespace video */
