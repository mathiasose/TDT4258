CC = arm-cortexm3-uclinuxeabi-gcc
CFLAGS += -O2 -g -W -Wall -std=c99
LDFLAGS += -lm

OBJECTS = graphics.o font.o

all: game

game: ${OBJECTS}
	${CC} ${CFLAGS} game.c ${OBJECTS}  -o game ${LDFLAGS}

clean:
	-rm -f game *.o

install:

.PHONY: all install clean
