dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(AtariEmulator2, 1.0)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

SDL_CFLAGS=`sdl2-config --cflags`
SDL_LDFLAGS=`sdl2-config --libs`
AC_SUBST([SDL_LDFLAGS])
AC_SUBST([SDL_CFLAGS])

GL_LDFLAGS=`pkg-config --libs gl`
AC_SUBST([GL_LDFLAGS])

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT
