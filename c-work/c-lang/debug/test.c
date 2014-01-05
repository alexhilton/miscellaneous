#include <stdio.h>
#include "debug.h"

int main( int argc, char **argv ) {
  log_debug( "this is main function\n" );
  log_debug( "this is a string '%s'\n", "abcdefg" );
  return 0;
}
