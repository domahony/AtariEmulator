AM_CXXFLAGS=-std=c++11 $(SDL_CFLAGS)

bin_PROGRAMS=ae
ae_SOURCES=AtariEmulator2.cpp Video.cpp CPU.cpp Clock.cpp Clock2.cpp ADC.cpp OpCode.cpp CMP.cpp AND.cpp AddressSpace.cpp \
ROM.cc RAM.cpp Pokey.cpp PIA.cpp ASL.cpp Branch.cpp BIT.cpp BRK.cpp SetFlags.cpp DEC.cpp EOR.cpp INC.cpp JMP.cpp LDA.cpp \
Shift.cpp NOP.cpp ORA.cpp PHA.cpp RTI.cpp RTS.cpp SBC.cpp STA.cpp Transfer.cpp ANTIC.cpp Logging.cpp Debugger.cpp DBGCommand.cpp BreakPoint.cpp
ae_LDFLAGS=$(SDL_LDFLAGS) $(GL_LDFLAGS) -lboost_system -lpthread -lboost_log -lboost_thread
ae_LDADD=$(SDL_LDFLAGS) $(GL_LDFLAGS) -lboost_system -lpthread -lboost_log -lboost_thread
