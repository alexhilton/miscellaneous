/*
 * eg0813.c
 * get your login name
 */
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  printf( "your login name is: '%s'\n", getlogin() );
  return 0;
}
