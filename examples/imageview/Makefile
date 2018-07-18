CC = g++
FLAGS = -Wall -O2 `lxrad_X11-config --cxxflags`

OBJS = pimageview.o imageview1.o  


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -oimageview `lxrad_X11-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./imageview

install:

clean:
	rm -f imageview *.o core
