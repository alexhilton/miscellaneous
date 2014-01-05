/*
 * ex0706.c
 * examine whether arrays of longs allocated by alloc will be initialized to 0,
 * what about array of pointers.
 * From this program's output, we can see that calloc does initialize the memory
 * allocated by it.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  long *long_arr;
  long **long_ptr;
  int size = 32;
  long_arr = (long *) calloc( size, sizeof( long ) );
  long_ptr = (long **) calloc( size, sizeof( long * ) );
  int i;
  for ( i = 0; i < size; i++ ) {
    printf( "#%02d, long_arr= %ld, long_ptr= %s\n", i+1, long_arr[i], 
	long_ptr[i] == NULL ? "null" : "non-null" );
  }
  free( long_arr );
  free( long_ptr );
  return 0;
}
