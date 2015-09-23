AM_CXXFLAGS=-std=c++11 $(SDL_CFLAGS)

bin_PROGRAMS=ae
ae_SOURCES=AtariEmulator2.cpp Video.cpp CPU.cc Clock.cpp Clock2.cpp ADC.cpp OpCode.cpp CMP.cpp AND.cpp AddressSpace.cpp \
ROM.cpp RAM.cpp Pokey.cpp PIA.cpp ASL.cpp Branch.cpp BIT.cpp BRK.cpp SetFlags.cpp DEC.cpp EOR.cpp INC.cpp JMP.cpp LDA.cpp \
Shift.cpp NOP.cpp ORA.cpp PHA.cpp RTI.cpp RTS.cpp SBC.cpp STA.cpp
ae_LDFLAGS=$(SDL_LDFLAGS) $(GL_LDFLAGS)
ae_LDADD=$(SDL_LDFLAGS) $(GL_LDFLAGS)
