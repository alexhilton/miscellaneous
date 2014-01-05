/*
 * makedir.c
 *
 * learn to make directory.
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
  mode_t mode;
  int opt_a = 0;
  char *ep; /* for strtol usage */
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
  } else if ( argc - optind > 2 ) {
    printf( "too many inputs\n" );
    return 0;
  }

  errno = 0;
  mode = strtol( argv[ optind ], &ep, 8 );
  if ( errno ) {
    perror( argv[ optind ] );
    return 0;
  }

  /* 
   * option -a or --all specify full access for every user
   */
  if ( opt_a == 1 ) {
    mode = 0777;
  }

  if ( mkdir( argv[ optind+1 ], mode ) != 0 ) {
    perror( argv[ optind+1 ] );
    return 0;
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
