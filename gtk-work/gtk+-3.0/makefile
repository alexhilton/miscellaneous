.phony: all

CFLAGS= -Wall -std=c99 `pkg-config --cflags --libs gtk+-3.0` 
basic: basic.c
	gcc -o basic $^ $(CFLAGS)

drawing: drawing.c
	gcc -o drawing $^ $(CFLAGS)

interface: interface.c
	gcc -o interface $^ $(CFLAGS)
