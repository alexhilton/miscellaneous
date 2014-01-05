# makefile for C programming.

MAIN=	string
OBJS=	$(MAIN).c

all:	$(OBJS)
	gcc -Wall -g -lm $(OBJS) -o $(MAIN)

run:
	./$(MAIN)

debug:	app
	gdb $(MAIN)

clrtmp:
	rm -f *~

clear:	clrtmp
	rm -f $(MAIN)

# end of makefile
