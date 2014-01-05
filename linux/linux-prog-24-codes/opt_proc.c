/*
 * $Header$
 *
 * Hitlion.Warrior.King				$Date$
 *
 * program to process options.
 *
 * Revision History
 * $Log$
 */
static const char rcsid[] = "$Id$";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char **argv )
{
  int optch;
  static char optstring[] = "gW;c";

  while ( ( optch = getopt( argc, argv, optstring ) ) != -1 ) {
    switch ( optch ) {
      case 'c':
	puts( "-c processed" );
	break;
      case 'g':
	puts( "-g processed" );
	break;
      case 'W':
	printf( "-W '%s' processd\n", optarg );
	break;
      default:
	puts( "unkown option" );
	break;
    } 
  } 
  for ( ; optind < argc; ++optind ) {
    printf( "argv[ %d ] = '%s'\n", optind, argv[ optind ] );
  }

  return ( 0 );
}
/* End $Source$ */
