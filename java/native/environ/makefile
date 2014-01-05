# makefile for Java native method
.phony:	all 

OBJS=	environ.c
CFLAGS=	-Wall -g -ansi -fPIC -shared
JAVA_HOME=	/usr/local/jdk1.6.0_14
LIBS=	-I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CC=	gcc
OBJECT=	libenviron.so

all:
	$(CC) $(CFLAGS) $(LIBS) -o $(OBJECT) $(OBJS)

# end of makefile
