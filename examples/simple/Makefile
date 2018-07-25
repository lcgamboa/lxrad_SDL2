CC = g++
FLAGS = -Wall -O0 -ggdb `lxrad_SDL2-config --cxxflags`

OBJS = psimple.o simple1.o  


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -osimple `lxrad_SDL2-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./simple

install:

clean:
	rm -f simple *.o core
