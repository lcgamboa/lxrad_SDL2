include ../Makefile.Conf

all:
static:
install:
	mkdir -p ${datadir}/lxrad/docs
	cp -v *.* ${datadir}/lxrad/docs
	cp -v README ${datadir}/lxrad/docs
	chmod 644 -R ${datadir}/lxrad/docs/*
	chmod 755 ${datadir}/lxrad/docs

clean:
uninstall:
	rm -f -R ${datadir}/lxrad/docs
