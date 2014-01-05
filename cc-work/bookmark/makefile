# Makefile for C++ programming language

.PHONY=	all run clear debug

MAIN=	main
OBJS=	$(MAIN).cc bookmark.cc book.cc

all:	$(OBJS)
	g++ -Wall -g -ansi -lm $(OBJS) -o $(MAIN)

run:
	./$(MAIN)

debug:
	gdb $(MAIN)

clear:
	rm -f $(MAIN) *~

# end of Makefile
