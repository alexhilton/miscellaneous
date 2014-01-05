/**
 * ex0806.c
 * solution to exercise 0806
 */
#include <stdio.h>
#include <string.h>
#include "mm.h"

static void *mycalloc( unsigned n, unsigned size );

int main( int argc, char **argv ) {
  /* 4 * 16 */
  char *p = (char *) mycalloc( 4, 16 );
  printf( "p is:\n'%s'\n", p );
  myfree( p );
  return 0;
}

static void *mycalloc( unsigned n, unsigned size ) {
  void *p = mymalloc( n * size );
  memset( p, 0, n * size );
  return p;
}
