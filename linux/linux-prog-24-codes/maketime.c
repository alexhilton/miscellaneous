/*
 * maketime.c
 *
 * write a small program to translate a time_t number into its
 * corresponding time.
 * with options capable.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>

void help();
void version();

int main( int argc, char *argv[] ) {
  int i;
  time_t time;
  char *ep;
  int cmd_x = 0;
  char stropts[] = "htfv";
  int optch;
  int cmd_t = 0;
  int cmd_f = 0;
  struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { "time", 0, 0, 't' },
    { "format", 0, 0, 'f' },
    { NULL, 0, 0, 0 }
  };

  while ( (optch = getopt_long(argc, argv, stropts, long_opts,
			       &cmd_x)) != EOF ) {
    switch ( optch ) {
    case 'h':
      help();
      return 0;
    case 'v':
      version();
      return 0;
    case 't':
      cmd_t = 1;
      break;
    case 'f':
      cmd_f = 0;
      break;
    default:
      printf( "Unkown option, try -h or --help for help.\n" );
      break;
    }
  }

  if ( argc - optind < 1 ) {
    printf( "Missing input arguments\n" );
    return 0;
  }

  if ( cmd_t ) {
    printf( "option -t specified\n" );
  }
  if ( cmd_f ) {
    printf( "option -f specified\n" );
  }

  for ( i = optind; i < argc; i++ ) {
    errno = 0;
    time = strtoul( argv[ i ], &ep, 10 );
    if ( errno ) {
      perror( argv[ i ] );
      continue;
    }
    printf( "%s", ctime( &time ) );
  }
  return 0;
}

void help() {
  printf( "translator from long type time into time format\n" );
  printf( "\t -h|--help for help\n" );
  printf( "\t -v|--version for version\n" );
}

void version() {
  printf( "maketime 1.0\n"
	  "Hitlion King\n" );
}
