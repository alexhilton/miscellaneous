/*
 * option processing demostration.
 * optpro.c
 */
#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  char optch; /* option character */
  static char optstring[] = "gW:c";

  while ( ( optch = getopt( argc, argv, optstring ) ) != -1 ) {
    switch ( optch ) {
    case 'c':
      printf( "-c processed\n" );
      break;
    case 'g':
      printf( "-g processed\n" );
      break;
    case 'W':
      printf( "-W processed\n" );
      break;
    default:
      printf( "Unknown options!\n" );
      break;
    }
  }
  for ( ; optind < argc; optind++ ) {
    printf( "argv[ %d ] = '%s'\n", optind, argv[ optind ] );
  }
  return 0;
}
