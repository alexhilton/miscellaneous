# Makefile for C programming exercises.

MAIN=	main
OBJS=	$(MAIN).c book.c bookmark.c

all:
	gcc -Wall -g -lm $(OBJS) -o $(MAIN)

run:
	./$(MAIN)

debug:
	gdb $(MAIN)

clear:
	rm -f $(MAIN).exe *~

# end of Makefile
