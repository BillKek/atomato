PKGS=sdl2

CFLAGS=-Wall -Wextra -Wno-missing-braces -std=c11 -pedantic $(shell pkg-config --cflags $(PKGS)) -g -O3
LIBS=$(shell pkg-config --libs $(PKGS)) -lm

: all: wireworld
all: rule110 gol seeds bb wireworld

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

cleanall:
	del *.exe *.o

