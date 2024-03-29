include ../Makefile.Conf


datadir=/assets

CFLAGS= -D_ONEWIN  -Werror -O2 -flto -D_Longlong="long long" -s USE_ZLIB=1 -s \
	USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png","bmp"]' -s USE_SDL_TTF=2 \
	-I ../teste/zlib-master/contrib/ -s USE_SDL_GFX=2
#CFLAGS+=-s USE_PTHREADS=1 -s PTHREAD_POOL_SIZE=2
LIBS =  -lSDL2_ttf  -lSDL2_image  -lSDL2 -lSDL2_gfx

CFLAGS+= -I../../lunasvg/include/

CC=em++
AR=emar

all:: 

LIBCFLAGS := $(CFLAGS) -fpic -D_SHARE=\"${datadir}/lxrad_SDL2/\" 
ARCFLAGS := $(CFLAGS) -static -D_SHARE=\"${datadir}/lxrad_SDL2/\" 

# .ao files are used for static archives
%.ao: %.cc
	$(CC) $(ARCFLAGS) -c $< -o $@

# .lo files are used for shared libraries
%.lo: %.cc
	$(CC) $(LIBCFLAGS) -c $< -o $@

# The main and minor version of the library
LIBMAINVER := ${MAINVER}
LIBMINORVER := ${MINORVER}
LIBVER := ${VERSION}

# The static lib name, the shared lib name, and the internal ('so') name of
# the shared lib.
LIBNAME = liblxrad_SDL2_js
LIBSHBASENAME = $(LIBNAME).so
LIBSHLIBNAME = $(LIBNAME).so.$(LIBVER)
LIBSTLIBNAME = $(LIBNAME).a
LIBSHSONAME := $(LIBNAME).so.$(LIBMAINVER)

LIBTARGETS := $(LIBSHLIBNAME) $(LIBSHSONAME) $(LIBSHBASENAME)

LIBSHOBJECTS := lxaudio.lo cspin.lo capplication.lo cbutton.lo cedit.lo cdraw.lo cdialog.lo cfiledialog.lo cpen.lo cpaint.lo cobject.lo ccontrol.lo citemmenu.lo cmenu.lo cpmenu.lo clabel.lo ctext.lo cwindow.lo cmessage.lo cinput.lo cbox.lo ccheckbox.lo ctoolbutton.lo cxpmbutton.lo ctimer.lo clist.lo cscroll.lo cfilelist.lo ccombodialog.lo ccombo.lo medit.lo chint.lo chtml.lo ctogglebutton.lo cgauge.lo cstatusbar.lo cspind.lo ccolordialog.lo cthread.lo mstring.lo lxutils.lo newcontrolbycname.lo third/SDL2_gfx_extra.lo

LIBSTOBJECTS := lxaudio.ao cspin.lo capplication.ao cbutton.ao cedit.ao cdraw.ao cdialog.ao cfiledialog.ao cpen.ao cpaint.ao cobject.ao ccontrol.ao citemmenu.ao cmenu.ao cpmenu.ao clabel.ao ctext.ao cwindow.ao cmessage.ao cinput.ao cbox.ao ccheckbox.ao ctoolbutton.ao cxpmbutton.ao ctimer.ao clist.ao cscroll.ao cfilelist.ao ccombodialog.ao ccombo.ao medit.ao chint.ao chtml.ao ctogglebutton.ao cgauge.ao cstatusbar.ao cspind.ao ccolordialog.ao cthread.ao mstring.ao lxutils.ao newcontrolbycname.ao third/SDL2_gfx_extra.ao
#LIBHEADERFILES := ../include/class.h ../include/controls.h 

# How to create the shared library
$(LIBSHLIBNAME): $(LIBSHOBJECTS)
	$(CC) -flto -shared -Wl,-soname,$(LIBSHSONAME) -o $@ $^  -lpthread  -lSDL2_ttf  -lSDL2_image  -lSDL2

$(LIBSHSONAME): $(LIBSHLIBNAME)
	$(RM) $@
	$(LN) $(LIBSHLIBNAME) $(LIBSHSONAME)

$(LIBSHBASENAME): $(LIBSHLIBNAME)
	$(RM) $@ 
	$(LN) $(LIBSHLIBNAME) $(LIBSHBASENAME)

# And the static library
$(LIBSTLIBNAME): $(LIBSTOBJECTS) 
	$(RM) $@
	$(AR) rcvs $(LIBSTLIBNAME) $^

# Include all dependency files
#INCLUDEFILES += $(LIBCSOURCES:.c=.ld) $(LIBCSOURCES:.c=.ad)

all-lib: $(LIBTARGETS)
all :: static
static :: $(LIBSTLIBNAME) 

clean-lib:
	$(RM) *.ld *.ad
	$(RM) *.lo *.ao $(LIBNAME).a
	$(RM) $(LIBTARGETS) $(LIBEXTRACLEAN)
clean :: clean-lib

install: all
	$(CP) -dvf $(LIBNAME)* ${libdir}

uninstall:
	$(RM) ${libdir}/$(LIBNAME)* 

