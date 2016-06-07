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
#include <vector>

namespace video {

class Video {
public:
	Video();
	virtual ~Video();

	void swapWindow() {

		glClear( GL_COLOR_BUFFER_BIT );
		SDL_GL_SwapWindow(gWindow);
	}

	void resize(int x, int y);

	int get_refresh_rate() const {
		return refresh_rate;
	}

	void set_frame_buffer(int, unsigned short*);

private:
	SDL_Window* gWindow;
	SDL_GLContext gContext;
	int refresh_rate;

	std::vector<GLshort> buf;

	GLuint vbo;
	GLuint vao;
	unsigned int buffer_size;
	int size_x;
	int size_y;
};

} /* namespace video */

#endif /* VIDEO_H_ */
