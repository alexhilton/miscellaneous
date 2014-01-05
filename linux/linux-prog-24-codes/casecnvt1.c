/*
 * casecnvrt1.c
 *
 * another version of implementation of utility case conversion.
 * with option capable.
 * Bonus point:
 * 	when switching between multiple variables or functions we
 * 	can use pointer.
 * 	as illustrated in this example.
 */
#include <stdio.h>
#include <getopt.h>
#include <errno.h>
#include <ctype.h>

static char (*conv)( const char ch );

void help();
void version();
char tolowercase( char ch );
char touppercase( char ch );
int convert( const char *fname );

int main( int argc, char *argv[] ) {
  int cmd_x;
  int i;
  int opt_u = 0;
  int opt_l = 0;
  static char optstring[] = "hvul";
  static struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { "lower", 0, 0, 'l' },
    { "upper", 0, 0, 'u' },
    { NULL, 0, 0, 0 }
  };
  char optch;

  while ( (optch = getopt_long(argc, argv, optstring, long_opts, &cmd_x))
	  != EOF ) {
    switch ( optch ) {
    case 'h':
      help();
      return 0;
    case 'v':
      version();
      return 0;
    case 'l':
      opt_l = 1;
      break;
    case 'u':
      opt_u = 1;
      break;
    default:
      printf( "-%c: unkown option\n", optch );
      break;
    }
  }

  if ( argc - optind < 1 ) {
    printf( "Missing input file(s).\n" );
    return 1;
  }

  /* to lowercase is default option */
  conv = tolowercase;
  if ( opt_u ) {
    conv = touppercase;
  }

  for ( i = optind; i < argc; i++ ) {
    if ( convert( argv[ i ] ) != 0 ) {
      continue;
    }
  }

  return 0;
}

void help() {
  printf( "Program to converting case\n"
	  "\t-h|--help to get help\n"
	  "\t-v|--version to get version infor\n"
	  "\t-l|--lower convert into lowercase\n"
	  "\t-u|--upper convert to uppercase\n" );
}

void version() {
  printf( "casecnvt1 version 1.0\nHitlion King\n" );
}

int convert( const char *fname ) {
  FILE *tin; /* for temporary file */
  FILE *in; /* for input file */
  char ch;

  if ( (tin = tmpfile()) == NULL ) {
    perror( "tmpfile()" );
    return -1;
  }

  /*
   * here you cannot use mode 'w+', then it will cause
   * file data loss.
   * "r+": open text file for update( reading and writing ).
   * "w+": create text file for update, discard previous contents, 
   * 	if any.
   * "a+": append, open or create text file for update, writing at end.
   */
  if ( (in = fopen( fname, "r+" )) == NULL ) {
    perror( fname );
    return -1;
  }

  while ( (ch = fgetc( in )) != EOF ) {
    ch = conv( ch );
    fputc( ch, tin );
  }

  /* fclose( in ); */
  /* this is much more effective */
  rewind( in );
  rewind( tin );

  /*if ( (in = fopen( fname, "w" )) == NULL ) {
    perror( fname );
    return -1;
  }*/

  while ( (ch = fgetc( tin )) != EOF ) {
    fputc( ch, in );
  }

  fclose( in );
  fclose( tin );

  return 0;
}

char tolowercase( char ch ) {
  if ( isupper( ch ) ) {
    ch = tolower( ch );
  }
  return ch;
}

char touppercase( char ch ) {
  if ( islower( ch ) ) {
    ch = toupper( ch );
  }
  return ch;
}
