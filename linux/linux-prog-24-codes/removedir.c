/*
 * removedir.c
 *
 * learn to remove directory.
 */
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

void help();
void version();

int main( int argc, char *argv[] ) {
  int cmd_x;
  char optstring[] = "hva";
  int opt_a = 0;
  int i;
  char optch;
  struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { "all", 0, 0, 'a' },
    { NULL, 0, 0, 0 }
  };

  while ( (optch = getopt_long(argc, argv, optstring, long_opts,
			       &cmd_x)) != EOF ) {
    switch ( optch ) {
    case 'h':
      help();
      return 0;
    case 'v':
      version();
      return 0;
    case 'a':
      opt_a = 1;
      break;
    default:
      printf( "-%c: unkown option\n", optch );
      break;
    }
  }

  if ( argc - optind < 1 ) {
    printf( "Incomplete inputs\n" );
    return 0;
  } 

  for ( i = optind; i < argc; i++ ) {
    if ( rmdir( argv[ i ] ) != 0 ) {
      perror( argv[ i ] );
      continue;
    }
  }

  return 0;
}

void help() {
  printf( "make a new direcctory\n"
	  "-h|--help for help\n"
	  "=v|--version for version infor\n" );
}

void version() {
  printf( "makedir version 1.0\nHitlion King\n" );
}
