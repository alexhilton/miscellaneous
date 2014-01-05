/**
 * mmdriver.c
 * test driver of interface mm
 */
#include <stdio.h>
#include <string.h>
#include "mm.h"

#define SIZE 64

int main( int argc, char **argv ) {
  char *p = (char *) mymalloc( SIZE );
  memset( p, 'a', SIZE );
  *(p + SIZE) = '\0';
  printf( "p is:\n'%s'\n", p );
  myfree( p );
  printf( "after free: p is '%s'\n", (p == NULL) ? "NULL" : "Not empty" );
  return 0;
}
