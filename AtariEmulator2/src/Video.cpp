/*
 * Video.cpp
 *
 *  Created on: May 1, 2015
 *      Author: domahony
 */

#include "types.h"
#include <iostream>
#include <vector>
#include "Video.h"
#include <SDL.h>
#include <SDL_opengl.h>

namespace video {

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static GLuint
init_vbo(std::vector<GLshort>& buf) {

	GLuint b;
	glGenBuffers(1, &b);
	glBindBuffer(GL_ARRAY_BUFFER, b);

	/*
	/*
	buf.push_back(0);
	buf.push_back(0);
	buf.push_back(10);
	buf.push_back(10);
	buf.push_back(20);
	buf.push_back(20);
	*/

	glBufferData(GL_ARRAY_BUFFER, buf.size() * sizeof(GLshort), &buf[0], GL_DYNAMIC_DRAW);
	glVertexPointer(2, GL_SHORT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	*/

	return b;
}

static GLuint
init_vao() {

	GLuint b;
	glGenVertexArrays(1, &b);

	return b;
}

Video::Video() : buffer_size(0), vao(0), buf(640 * 480) {

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

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	vbo = init_vbo(buf);
	/*
	vao = init_vao();
	*/

	SDL_GL_SetSwapInterval( 1 );

	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

	refresh_rate = mode.refresh_rate;
	std::cout << "HZ: " << mode.refresh_rate << std::endl;
}

void Video::
set_frame_buffer(int size, unsigned short* buf)
{
	//glColor3b(0xff, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferSubData(GL_ARRAY_BUFFER, 0, size * sizeof(GLshort) * 2, buf);

	glEnableClientState(GL_VERTEX_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1, 1, 0);
	glScalef(1.f/320, -1.f/240, 1);
	glDrawArrays(GL_POINTS, 0, size);


	/*
	glBegin(GL_POINTS);
		glColor3f(1,1,1);
		glVertex2f(630, 470);
		glColor3f(1,0,0);
		glVertex2f(1, 1);
	glEnd();
	*/

	/*
	glBegin(GL_POINTS);
	glColor3f(1,1,1);
	glVertex2f(.5, .5);
	glColor3f(0,1,1);
	glVertex2f(.1, .1);
	glColor3f(1,0,0);
	glVertex2f(.9, .1);
	glVertex2f(.99, .1);
	glVertex2f(.99, .5);
	glVertex2f(.99, .8);
	glColor3f(0,1,0);
	glVertex2f(.99, -.8);
	glEnd();
	*/
	//glFlush();

	SDL_GL_SwapWindow(gWindow);

	/*
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, buf);
	*/
}

Video::~Video() {
	// TODO Auto-generated destructor stub
}

} /* namespace video */
