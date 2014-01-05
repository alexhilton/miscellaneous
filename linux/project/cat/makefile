# makefile for C
.phony:	all run debug clean

CC=	gcc
CFLAGS=	-Wall -g
MAIN=	cat
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
