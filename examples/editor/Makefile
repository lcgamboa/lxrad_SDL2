CC = g++
FLAGS = -Wall -O2 `lxrad_X11-config --cxxflags`

OBJS = peditor.o editor1.o  


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -oeditor `lxrad_X11-config --libs`

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./editor

install:

clean:
	rm -f editor *.o core
