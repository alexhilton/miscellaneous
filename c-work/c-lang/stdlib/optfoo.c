/*
 * optfoo.c
 * a function to practice how to dealing with options.
 */
#include <stdio.h>
#include <unistd.h>
int getopt( int argc, char **argv, char *optstr );
extern char *optarg;
extern int optind, opterr, optopt;

int main( int argc, char **argv ) {
  int oc;
  char *b_opt_arg;

  while ( ( oc = getopt( argc, argv, "ab:" ) ) != -1 ) {
    switch ( oc ) {
    case 'a':
      printf( "options 'a' has been processed\n" );
      break;
    case 'b':
      printf( "options 'b' has been processed\n" );
      b_opt_arg = optarg;
      break;
    case ':':
      fprintf( stderr, "Invalide option %c", oc );
      break;
    case '?':
    default:
      fprintf( stderr, "invalide option %c", oc );
      break;
    }
  }
  return 0;
}
