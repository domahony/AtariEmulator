/*
 * Video.h
 *
 *  Created on: May 1, 2015
 *      Author: domahony
 */

#ifndef VIDEO_H_
#define VIDEO_H_

#include <SDL.h>
#include <SDL_opengl.h>

namespace video {

class Video {
public:
	Video();
	virtual ~Video();

	void swapWindow() {

		glClear( GL_COLOR_BUFFER_BIT );
		SDL_GL_SwapWindow(gWindow);
	}

private:
	SDL_Window* gWindow;
	SDL_GLContext gContext;
};

} /* namespace video */

#endif /* VIDEO_H_ */
