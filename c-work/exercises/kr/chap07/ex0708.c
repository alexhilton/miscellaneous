/**
 * ex0708.c
 * solution to ex0708
 */
#include <stdio.h>

#define PAGE_SIZE 24 /* lines of each page */
static int pagecount = 0;
#define MAX_LINE 128 /* max length of line */

static void printfile( const char *filename );

int main( int argc, char **argv ) {
  while ( --argc > 0 ) {
    printfile( *++argv );
  }
  return 0;
}

static void printfile( const char *filename ) {
  FILE *fp;
  char line[ MAX_LINE ];
  int linecount = 0;
  if ( (fp = fopen( filename, "r" )) == NULL ) {
    fprintf( stderr, "error on opening file %s\n", filename );
  } else {
    pagecount++;
    fprintf( stdout, "File: %s, Page: %d, sizeof( fp ) %d\n", filename, pagecount, sizeof(*fp) );
    while ( (fgets( line, sizeof( line ), fp )) != NULL ) {
      if ( ++linecount > PAGE_SIZE ) {
	pagecount++;
	linecount -= PAGE_SIZE;
      }
      fprintf( stdout, "%s", line );
    }
  }
  fclose( fp );
}
