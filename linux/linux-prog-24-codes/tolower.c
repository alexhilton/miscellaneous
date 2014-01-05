/*
 * tolower.c
 *
 * convert a ASCII into lower format.
 *
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

static void cleanup() {
  if ( tf_path != NULL ) {
    unlink( tf_path );
    free( tf_path );
  }
}

int main( int argc, char *argv[] ) {
  int cmd_x; /* command index */
  static char optstring[] = "hv";
  struct option long_opts[] = {
    { "help", 0, 0, 'h' },
    { "version", 0, 0, 'v' },
    { NULL, 0, 0, 0 }
  };
  char optch;
  int i;

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
      printf( "-%c: unkown option\n", optch );
      break;
    }
  }

  if ( argc - optind < 1 ) {
    printf( "Missing input file(s)\n" );
    return 0;
  }

  for ( i = optind; i < argc; i++ ) {
    if ( tolowercase( argv[ i ] ) != 0 ) {
      continue;
    }
  }

  return 0;
}

void help() {
  printf( "Program to convert ASCII file into lower format\n"
	  "\t-h|--help for help\n"
	  "\t-v|--version for version information\n" );
}

void version() {
  printf( "tolower version 1.0\nHitlion King\n" );
}

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
