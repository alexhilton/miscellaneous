# makefile for OpenGL programming or development
# we try to make this makefile as formal as possible
.phony:	all clean run debug

MAIN= rasonly
OBJS=	$(MAIN).c
CFLAGS=	-g -Wall -ansi -std=c99
CLIBS=	-L/usr/X11R6/lib -lglut -lGLU -lGL -lX11 -lXext -lXmu -lm

all:
	gcc $(OBJS) -o $(MAIN) \
		$(CFLAGS) \
		$(CLIBS)


run:
	./$(MAIN)

debug:
	gdb $(MAIN)

clean:
	rm *~ $(MAIN)

# end of makefile
