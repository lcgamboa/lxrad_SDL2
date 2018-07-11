CC = gcc
FLAGS = -Wall -O5
OBJS = pmultthread.o multthread1.o

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -omultthread -llxrad

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./multthread

install:

clean:
	rm -f multthread *.o core