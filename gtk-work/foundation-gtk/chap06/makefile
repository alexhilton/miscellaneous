# makefile for GTK+2.0 programming
.phony:	all run debug clean

MAIN=	more_ex0601
OBJS=	$(MAIN).c

CFLAGS=	-Wall -g -ansi -std=c99
INCLUDE=	-I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 \
		-I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 \
	       	-I/usr/lib/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 \
	       	-I/usr/include/libpng12  
CLIBS=	-lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lgdk_pixbuf-2.0 \
       	-lpangocairo-1.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lglib-2.0  

all:
	gcc $(CFLAGS) $(OBJS) -o $(MAIN) \
		$(INCLUDE) \
		$(CLIBS)

run:
	./$(MAIN)

debug:
	gdb $(MAIN)

clean:
	rm -f *~ $(MAIN)

# end of makefile
