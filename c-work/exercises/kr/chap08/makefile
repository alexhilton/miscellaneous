# makefile for C
.phony:	all run debug clean

CC=	gcc
CFLAGS=	-Wall -g -ansi -std=c99
CLIBS=	-lm
MAIN=	ex0808
OBJS=	$(MAIN).c mm.c

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
