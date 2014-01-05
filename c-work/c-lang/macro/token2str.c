/**
 * token2str.c
 * show you how to use preprocess command to convert a 'thing' to string, that
 * is, make is double quoted after macro expansion.
 */
#include <stdio.h>

/* convert a into a string, make it double quoted */
/**
 * Note:
 * this macro or (#command) cannot make a variable double quoted.
 * it will put exactly the thing provided as actual arg into double quotes.
 * say: tostring( 2345 ) yields "2345";
 * 	tostring( a ) yields "a", though a is a variable.
 * 	tostring( main ) yields "main"
 */
#define tostring( a ) #a

/**
 * Make a comparision
 * Use a macro make it quoted explictly
 * This does not work, of course.
 */
#define tostr( a ) "a"

int main( int argc, char **argv ) {
  int a = 349;
  printf( "tostring( 23456 ): '%s'\n", tostring( 23456 ) );
  printf( "tostring( a )(int a = 349): '%s'\n", tostring( a ) );
  printf( "tostring( main ): '%s'\n", tostring( main ) );
  printf( "tostring( printf ): '%s'\n", tostring( printf ) );
  printf( "tostr( 23456 ): '%s'\n", tostr( 23456 ) );
  printf( "tostr( a )(int a = 349): '%s'\n", tostr( a ) );
  printf( "tostr( main ): '%s'\n", tostr( main ) );
  printf( "tostr( printf ): '%s'\n", tostr( printf ) );
  return 0;
}
