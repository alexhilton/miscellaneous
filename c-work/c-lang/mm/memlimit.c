/*
 * memlimit.c
 * find out how many menory you can allocate from the system.
 */
#include <stdio.h>
#include <stdlib.h>

int main( void ) {
	int mb = 0;
	while ( malloc( 1 << 20 ) ) {
		mb++;
	}
	printf( "you've allocated %d bytes of memory\n", mb );
	return 0;
}
