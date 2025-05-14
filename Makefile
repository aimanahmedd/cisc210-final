CC = gcc
CFLAGS = -Wall -g -I$(HOME)/include
LDFLAGS = -L$(HOME)/lib -lsense -lm
OBJS = main.o input.o output.o

all: etch

etch: $(OBJS)
	$(CC) $(CFLAGS) -o etch $(OBJS) $(LDFLAGS)

run: etch
	./etch

%.o: %.c project.h

	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o etch
