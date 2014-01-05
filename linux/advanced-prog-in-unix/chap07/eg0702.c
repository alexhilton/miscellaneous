/* 
 * eg0702.c
 * Print all command-line arguments.
 */
#include <stdio.h>

int main( int argc, char **argv ) {
  while ( argc-- > 0 ) {
    printf( "%s\n", *argv++ );
  }
  return 0;
}
