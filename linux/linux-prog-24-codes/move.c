/*
 * move.c
 *
 * Implementation of move (mv) command.
 */
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

void help();
void version();

int main( int argc, char *argv[] ) {
  int cmd_x;
  char ch;
  char optstring[] = "vh";
  struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { NULL, 0, 0, 0 }
  };

  while ( (ch = getopt_long(argc, argv, optstring, long_opts, &cmd_x) )
	  != EOF ) {
    switch ( ch ) {
    case 'h':
      help();
      return 0;
    case 'v':
      version();
      return 0;
    default:
      printf( "-%c: unkown option\n", ch );
      break;
    }
  }

  if ( argc - optind < 1 ) {
    printf( "Missing input arguments\n" );
    return 0;
  } else if ( argc - optind > 2 ) {
    printf( "too many input files\n" );
    return 0;
  }

  if ( link( argv[ optind ], argv[ optind+1 ] ) != 0 ) {
    perror( argv[ optind ] );
    perror( argv[ optind+1 ] );
    return 0;
  }
  if ( unlink( argv[ optind ] ) != 0 ) {
    perror( argv[ optind ] );
    return 0;
  }
  return 0;
}

void help() {
  printf( "Program to move file from one path to another\n"
	  "-h|--help for help\n"
	  "-v|--version for version information\n" );
  printf( "You must specify original file first, then specify the\n"
	  " destinaiton file name (full path).\n" );
}

void version() {
  printf( "move version 1.0\n"
	  "Hitlion King\n" );
}
