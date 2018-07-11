include ../Makefile.Conf

all:: 

LIBCFLAGS := $(CFLAGS) -fpic
ARCFLAGS := $(CFLAGS) -static

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
LIBNAME = liblxrad
LIBSHBASENAME = $(LIBNAME).so
LIBSHLIBNAME = $(LIBNAME).so.$(LIBVER)
LIBSTLIBNAME = $(LIBNAME).a
LIBSHSONAME := $(LIBNAME).so.$(LIBMAINVER)

LIBTARGETS := $(LIBSHLIBNAME) $(LIBSHSONAME) $(LIBSHBASENAME)

LIBSHOBJECTS := capplication.lo cbutton.lo cedit.lo cdraw.lo cdialog.lo cfiledialog.lo cpen.lo cpaint.lo cobject.lo ccontrol.lo citemmenu.lo cmenu.lo cpmenu.lo clabel.lo ctext.lo cwindow.lo cmessage.lo cinput.lo cbox.lo ccheckbox.lo ctoolbutton.lo cxpmbutton.lo ctimer.lo clist.lo cscroll.lo cfilelist.lo ccombodialog.lo ccombo.lo medit.lo chint.lo mstring.lo cutils.lo
LIBSTOBJECTS := capplication.ao cbutton.ao cedit.ao cdraw.ao cdialog.ao cfiledialog.ao cpen.ao cpaint.ao cobject.ao ccontrol.ao citemmenu.ao cmenu.ao cpmenu.ao clabel.ao ctext.ao cwindow.ao cmessage.ao cinput.ao cbox.ao ccheckbox.ao ctoolbutton.ao cxpmbutton.ao ctimer.ao clist.ao cscroll.ao cfilelist.ao ccombodialog.ao ccombo.ao medit.ao chint.ao mstring.ao cutils.ao

#LIBHEADERFILES := ../include/class.h ../include/controls.h 

# How to create the shared library
$(LIBSHLIBNAME): $(LIBSHOBJECTS)
	$(CC) -shared -nostdlib -Wl,-soname,$(LIBSHSONAME) -o $@ $^   -lXpm -lX11 -lpthread 

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
all :: all-lib
static :: $(LIBSTLIBNAME) 

clean-lib:
	$(RM) *.ld *.ad
	$(RM) *.lo *.ao *.a
	$(RM) $(LIBTARGETS) $(LIBEXTRACLEAN)
clean :: clean-lib

install: all
	$(CP) -dvf $(LIBNAME)* ${libdir}

uninstall:
	$(RM) ${libdir}/$(LIBNAME)* 

