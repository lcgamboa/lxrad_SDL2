include Makefile.Conf

SUBDIRS= lib include share docs layout utils
.PHONY: $(SUBDIRS) 

all:$(SUBDIRS) 

static:$(SUBDIRS) 

install:$(SUBDIRS)
	
clean:$(SUBDIRS)

uninstall:$(SUBDIRS)
	
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)


