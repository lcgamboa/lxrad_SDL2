CC = g++
FLAGS = -Wall -O2 `lxrad_X11-config --cxxflags`

OBJS = pgetlinks.o getlinks1.o  


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -ogetlinks `lxrad_X11-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./getlinks

install:

clean:
	rm -f getlinks *.o core
