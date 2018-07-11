include ../Makefile.Conf

FLAGS = $(CFLAGS) -D_SHARE=\"${datadir}/lxrad/icons\" 

OBJS = playout.o controlsdef.o layout1.o layout2.o layout3.o layout4.o layout5.o layout6.o layout7.o layout8.o layout9.o layout10.o

LINK= -L../lib -llxrad -lX11
SLINK= -static -L../lib -llxrad -lXpm -lX11 -lpthread  

all: $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -olayout $(LINK)

static: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -olayout $(SLINK)
	
install: all
	$(CP) -dvf layout ${bindir}

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

uninstall:
	$(RM) ${bindir}/layout 

clean:
	rm -f layout *.o core
