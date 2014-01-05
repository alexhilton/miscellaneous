/**
 * tokenmerge.c
 * show you how to use preprocessor command ## to merge two tokens
 */
#include <stdio.h>

/* use preprocessor merge to create some automatical naming methods. */
/**
 * Note:
 * ## will make two actual args into one token. It won't recognize variables,
 * either. And the result is not a string, it is a C identifier or token. Thus,
 * if you combine any two things, undefined result will be given to you and that
 * might cause an error.
 * 	autoname( tag, num ) tag ## num -- tagnum
 * 	autoname( 234, 56 ) -- 23456
 */
#define autoname( tag, num ) tag ## num

/**
 * Make a comparision:
 * Use anothe way to implement token merging.
 * There is no second way to do so.
 */
#define autoname2( tag, num ) tag num

int main( int argc, char **argv ) {
  int window1 = 1;
  float box2 = 2.f;
  double button3 = 3.f;
  char tree4 = 0x041;
  printf( "int window: autoname( window ) -- '%d'\n", autoname( window, 1 ) );
  printf( "float box: autoname( box ) -- '%g'\n", autoname( box, 2 ) );
  printf( "double button: autonae( button ) -- '%g'\n", autoname( button, 3 ) );
  printf( "char tree: autoname( tree ) -- '%c'\n", autoname( tree, 4 ) );
  printf( "autoname( 2345, 6789 ) -- '%d'\n", autoname( 2345, 6789 ) );

  /*
  printf( "int window: autoname2( window ) -- '%d'\n", autoname2( window, 1 ) );
  printf( "float box: autoname2( box ) -- '%g'\n", autoname2( box, 2 ) );
  printf( "double button: autonae2( button ) -- '%g'\n", autoname2( button, 3 ) );
  printf( "char tree: autoname2( tree ) -- '%c'\n", autoname2( tree, 4 ) );
  printf( "autoname2( 2345, 6789 ) -- '%d'\n", autoname2( 2345, 6789 ) );
  */
  return 0;
}
