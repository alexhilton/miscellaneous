/**
 * ex0808.c
 * solution to ex0808
 * this is only a test, the implementation is in mm.c
 */
#include <stdio.h>
#include <string.h>
#include "mm.h"

#define SIZE 32

int main( int argc, char **argv ) {
  char *p = (char *) mymalloc( SIZE * sizeof( char ) );
  memset( p, 'a', SIZE );
  *(p + SIZE) = '\0';
  printf( "p is:\n'%s'\n", p );
  myfree( p );
  char str[ SIZE ];
  strcpy( str, p );
  bfree( str, SIZE );
  return 0;
}
