CC = g++
FLAGS = -Wall -O2 `lxrad_X11-config --cxxflags`

OBJS = psimple.o simple1.o  


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -osimple `lxrad_X11-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./simple

install:

clean:
	rm -f simple *.o core
