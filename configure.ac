# Process this file with autoconf to produce a configure script.
AC_INIT(lxrad_SDL2, 0.7, lcgamboa@yahoo.com)
AC_PREREQ([2.50])
AC_CONFIG_SRCDIR([lib/capplication.cc])
AC_CONFIG_HEADER([config.h])
#AC_PREFIX_DEFAULT (/usr/local)

# Checks for programs.
AC_PROG_CC()
AC_PROG_CXX()
CFLAGS="-Wall -D_LX_SDL2 `sdl2-config --cflags`"
LIBS=""

# Checks for libraries.
AC_CHECK_LIB([SDL2], [SDL_CreateWindow],
cat >>confdefs.h <<_ACEOF
#define HAVE_LIBSDL2 1
_ACEOF
LIBS+=" -lSDL2",
AC_MSG_ERROR([SDL2 Not Found!]))

AC_CHECK_LIB([SDL2_image], [IMG_Init],
cat >>confdefs.h <<_ACEOF
#define HAVE_LIBSDL2_IMAGE 1
_ACEOF
LIBS=" -lSDL2_image $LIBS",
AC_MSG_ERROR([SDL2 image Not Found!]))

AC_CHECK_LIB([SDL2_gfx], [thickLineRGBA],
cat >>confdefs.h <<_ACEOF
#define HAVE_LIBSDL2_GFX 1
_ACEOF
LIBS=" -lSDL2_gfx $LIBS",
AC_MSG_ERROR([SDL2 gfx Not Found!]))


AC_CHECK_LIB([SDL2_ttf], [TTF_Init],
cat >>confdefs.h <<_ACEOF
#define HAVE_LIBSDL2_TTF 1
_ACEOF
LIBS=" -lSDL2_ttf $LIBS",
AC_MSG_ERROR([SDL2 ttf Not Found!]))

AC_CHECK_LIB([minizip], [zipOpen],
cat >>confdefs.h <<_ACEOF
#define HAVE_LIBMINIZIP 1
_ACEOF
LIBS=" -lminizip $LIBS",
AC_MSG_ERROR([minizip Not Found!]))

AC_CHECK_LIB([pthread], [pthread_create],
cat >>confdefs.h <<_ACEOF
#define HAVE_LIBPTHREAD 1
_ACEOF
LIBS="-lpthread $LIBS"
CFLAGS="$CFLAGS -D_REENTRANT",
AC_MSG_WARN([libpthread Not Found!]))

# Checks for libraries.
AC_CHECK_LIB([openal], [alGenSources],
cat >>confdefs.h <<_ACEOF
#define HAVE_OPENAL 1
_ACEOF
LIBS="-lopenal $LIBS",
AC_MSG_WARN([libopenal Not Found!]))

# Checks for header files.
AC_PATH_X
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([locale.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([mkdir setlocale strerror strrchr strstr])


AC_SUBST(PACKAGE,`sed -ne 's/PACKAGE=//p' VERSION`)
AC_SUBST(VERSION,`sed -ne 's/VERSION=//p' VERSION`)
AC_SUBST(MAINVER,`sed -ne 's/MAINVER=//p' VERSION`)
AC_SUBST(MINORVER,`sed -ne 's/MINORVER=//p' VERSION`)
AC_SUBST(HOSTOS,`uname -sr || echo unknown`)
AC_SUBST(HOSTCPU,`uname -m || echo unknown`)

AC_SUBST(LIBS)

AC_SUBST(PREFIX)
AC_SUBST(BINDIR)
AC_SUBST(LIBDIR)

AC_OUTPUT([Makefile
           Makefile.Conf
           docs/Makefile
           include/Makefile
           layout/Makefile
           lib/Makefile
           share/Makefile
           utils/Makefile
           utils/lxrad_SDL2-config])

