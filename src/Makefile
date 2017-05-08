IDIR =../include
CC=gcc
CFLAGS=-g -O0 -Wall -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

lib: ring_buffer.o
	$(AR) rcs librb.a ring_buffer.o

.PHONY: clean all

all: lib

clean:
	rm -f *.o librb.a