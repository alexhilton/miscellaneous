/**
 * vamacro.c
 * variable arguments list macro
 */
#include <stdio.h>

/* variable arguments list */
#define my_printf( ... ) fprintf( stderr, __VA_ARGS__ )
#define make_em_a_string( ... ) #__VA_ARGS__

int main( int argc, char **argv ) {
  my_printf( "x is 0x%x\n", 0x01 );
  my_printf( "%s\n", make_em_a_string( a, b, c, d ) );
  return 0;
}
