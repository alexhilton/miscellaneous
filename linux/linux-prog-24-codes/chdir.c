/*
 * chdir.c
 *
 * learn the trick how to change directory.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

void help();
void version();

int main( int argc, char *argv[] ) {
  int cmd_x;
  char optstring[] = "hv";
  char optch;
  struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { NULL, 0, 0, 0 }
  };

  while ( (optch = getopt_long(argc, argv, optstring, long_opts, &cmd_x))
	  != EOF ) {
    switch ( optch ) {
    case 'h':
      help();
      return 0;
    case 'v':
      version();
      return 0;
    default:
      printf( "-%c: Unkown option\n", optch );
      break;
    }
  }

  if ( argc - optind < 1 ) {
    printf( "Incomplete input\n" );
    return 0;
  } else if ( argc - optind > 1 ) {
    printf( "Too much inputs\n" );
    return 0;
  }

  if ( chdir( argv[ optind ] ) != 0 ) {
    perror( argv[ optind ] );
    return 0;
  }

  return 0;
}

void help() {
  printf( "change directory\n"
	  "-h|--help for help\n"
	  "-v|--version to get version infor\n" );
}


void version() {
  printf( "chdir version 1.0\nHitlion King\n" );
}
