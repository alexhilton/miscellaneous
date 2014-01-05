/*
 * boom.c -- abort in action.
 */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv )
{
  puts( "About to abort...\n" );

  abort();
  /* never get here */
  puts( " i reckon it worked.\n" );

  exit( EXIT_SUCCESS );
}
