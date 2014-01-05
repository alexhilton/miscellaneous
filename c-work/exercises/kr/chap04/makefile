# makefile for C
.phony:	all run debug clean

CC=	gcc
CFLAGS=	-Wall -g -ansi
CLIBS=	-lm
MAIN=	ex0410
OBJS=	$(MAIN).c

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
