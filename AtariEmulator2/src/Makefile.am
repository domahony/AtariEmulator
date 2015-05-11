AM_CXXFLAGS=-std=c++11 $(SDL_CFLAGS)

bin_PROGRAMS=ae
ae_SOURCES=AtariEmulator2.cpp Video.cpp CPU.cc Clock.cpp Clock2.cpp ADC.cpp

ae_LDFLAGS=$(SDL_LDFLAGS) $(GL_LDFLAGS)
ae_LDADD=$(SDL_LDFLAGS) $(GL_LDFLAGS)