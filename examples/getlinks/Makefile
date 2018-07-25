CC = g++
FLAGS = -Wall -O2 `lxrad_SDL2-config --cxxflags`

OBJS = pgetlinks.o getlinks1.o  


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -ogetlinks `lxrad_SDL2-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./getlinks

install:

clean:
	rm -f getlinks *.o core
