SUBDIRS= simple sin getlinks editor imageview multthread
.PHONY: $(SUBDIRS)


all:$(SUBDIRS)

install:$(SUBDIRS)
	
clean:$(SUBDIRS)
	
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

