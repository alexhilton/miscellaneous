/**
 * ex0706.c
 * solution to ex0706
 * implementation of find
 */
#include <stdio.h>
#include <string.h>

#define MAX_LINE 128 /* max length of a line */

int main( int argc, char **argv ) {
  char line[ MAX_LINE ];
  long lineno = 0;
  char *pattern;
  char ch;
  int except = 0, number = 0;
  FILE *fp;

  while ( --argc > 0 && *(*++argv) == '-' ) {
    while ( (ch =  *++(*argv)) != '\0' ) {
      switch ( ch ) {
      case 'x':
	except = 1;
	break;
      case 'n':
	number = 1;
	break;
      default:
	fprintf( stderr, "find: illeagal option %c\n", ch );
	break;
      }
    }
  }
  if ( argc-- < 2 ) {
    fprintf( stderr, "usage: find -x -n pattern file1 [file2 ...]\n" );
    return 0;
  }
  pattern = *argv;
  printf( "argc is %d, pattern is '%s'\n", argc, pattern );
  while ( argc-- > 0 ) {
    if ( (fp = fopen( *++argv, "r" )) == NULL ) {
      fprintf( stderr, "error opening file %s\n", *argv );
      continue; /* go find next file */
    }
    while ( fgets( line, sizeof( line ), fp ) != NULL ) {
      lineno++;
      /*
       * it is a little bit complicated about the following conditional
       * expression.
       * it will print:
       *    # if pattern is in line and except is 0
       *    # if pattern is not in line and except is 1
       * it is equal to:
       * if ( (p = strstr(line, pattern)) != NULL && except == 0 || p == NULL && except == 1 ) {
       * 	do print
       * }
       * it is expertise program, but takes a little time to comprehend.
       */
      if ( (strstr( line, pattern ) != NULL) != except ) {
	if ( number ) {
	  fprintf( stdout, "%ld ", lineno );
	}
	fprintf( stdout, "%s: %s", *argv, line );
      }
    }
    fclose( fp );
  }
  return 0;
}
