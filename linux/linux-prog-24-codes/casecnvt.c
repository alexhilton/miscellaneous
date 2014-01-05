/*
 * casecnvt.c
 *
 * convert a ASCII into lower or upper format.
 *
 * using option -l and -u to specify convert to lowercase or uppercase.
 * default option is -l
 * using temporary file, and make sure it will be deleted when
 * program terminat.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <errno.h>
#include <getopt.h>

static char *tf_path = NULL;
void help();
void version();
int tolowercase( const char *fname );
int touppercase( const char *fname );

static void cleanup() {
  if ( tf_path != NULL ) {
    unlink( tf_path );
    free( tf_path );
  }
}

int main( int argc, char *argv[] ) {
  int cmd_x; /* command index */
  static char optstring[] = "luhv";
  struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { "lower", 0, 0, 'l' },
    { "upper", 0, 0, 'u' },
    { NULL, 0, 0, 0 }
  };
  char optch;
  int i;
  int opt_l = 0; /* flag infor of option -l */
  int opt_u = 0; /* flag infor of option -u */
  static int (*conv)( const char *fname ); /* conv func ptr */

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
    printf( "Missing input file(s)\n" );
    return 0;
  }

  if ( opt_u ) {
    conv = touppercase;
  } else {
    conv = tolowercase;
  }

  for ( i = optind; i < argc; i++ ) {
    if ( conv( argv[ i ] ) != 0 ) {
      continue;
    }
  }

  return 0;
}

void help() {
  printf( "Program to convert ASCII file into lower format\n"
	  "\t-h|--help for help\n"
	  "\t-v|--version for version information\n"
	  "\t-l|--lower convert into lowercase\n"
	  "\t-u|--upper convert into uppercase\n" );
}

void version() {
  printf( "tolower version 1.0\nHitlion King\n" );
}

/*
 * function to convert into lowercase.
 */
int tolowercase( const char *fname ) {
  FILE *tin; /* for temporary file */
  FILE *in;
  char ch;

  if ( atexit( cleanup ) != 0 ) {
    perror( "atexit( cleanup )" );
    return -1;
  }

  if ( (tf_path = tempnam( "./my_tmp", "tmp-" )) == NULL ) {
    perror( tf_path );
    return -1;
  }

  if ( (tin = fopen( tf_path, "w+" )) == NULL ) {
    perror( tf_path );
    return -1;
  }

  if ( (in = fopen( fname, "r" )) == NULL ) {
    perror( fname );
    return -1;
  }

  while ( (ch = fgetc( in )) != EOF ) {
    ch = tolower( ch );
    fputc( ch, tin );
  }

  fclose( in );

  if ( (in = fopen( fname, "w" )) == NULL ) {
    perror( fname );
    return -1;
  }
  rewind( tin );

  while ( (ch = fgetc( tin )) != EOF ) {
    fputc( ch, in );
  }

  fclose( in );
  fclose( tin );

  return 0;
}

/*
 * function convert into uppercase.
 */
int touppercase( const char *fname ) {
  FILE *tin; /* for temporary file */
  FILE *in;
  char ch;

  if ( atexit( cleanup ) != 0 ) {
    perror( "atexit( cleanup )" );
    return -1;
  }

  if ( (tf_path = tempnam( "./my_tmp", "tmp-" )) == NULL ) {
    perror( tf_path );
    return -1;
  }

  if ( (tin = fopen( tf_path, "w+" )) == NULL ) {
    perror( tf_path );
    return -1;
  }

  if ( (in = fopen( fname, "r" )) == NULL ) {
    perror( fname );
    return -1;
  }

  while ( (ch = fgetc( in )) != EOF ) {
    ch = toupper( ch );
    fputc( ch, tin );
  }

  fclose( in );

  if ( (in = fopen( fname, "w" )) == NULL ) {
    perror( fname );
    return -1;
  }
  rewind( tin );

  while ( (ch = fgetc( tin )) != EOF ) {
    fputc( ch, in );
  }

  fclose( in );
  fclose( tin );

  return 0;
}
