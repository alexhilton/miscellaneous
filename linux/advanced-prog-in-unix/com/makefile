# makefile for C
.phony:	all run debug clean

CC=	gcc
#std=c99 and -ansi conflict with -D__USE_BSD
CFLAGS=	-Wall -g -D__USE_BSD #-ansi -std=c99
CLIBS=	-lm
MAIN=	eg0407
OBJS=	$(MAIN).c ../com/comhdr.c

all:
	$(CC) $(CFLAGS) $(CLIBS) \
		-o $(MAIN) $(OBJS)

run:
	./$(MAIN)

debug:
	gdb $(MAIN)

clean:
	rm -fr *~ $(MAIN)

# end of makefile
