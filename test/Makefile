IDIR =../include
CC=gcc
CFLAGS=-g -O0 -I$(IDIR)

ODIR=obj
LDIR =../src

LIBS=-lrb

test: test.c
	gcc  -o test test.c $(CFLAGS) -L$(LDIR) $(LIBS)

.PHONY: clean all

all: test

clean:
	rm -f *.o test