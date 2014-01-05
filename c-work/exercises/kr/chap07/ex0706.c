/**
 * ex0706.c
 * solution to ex0706
 */
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 128

static void compare( FILE *fp1, FILE *fp2 );

int main( int argc, char **argv ) {
  if ( argc != 3 ) {
    fprintf( stderr, "usage: ex0706 file1 file2\n" );
    return 0;
  }
  FILE *fp1, *fp2;
  if ( (fp1 = fopen( *++argv, "r" )) != NULL && (fp2 = fopen( *++argv, "r" )) != NULL ) {
    compare( fp1, fp2 );
  } else {
    fprintf( stderr, "error opening files\n" );
  }
  fclose( fp1 );
  fclose( fp2 );
  return 0;
}

static void compare( FILE *fp1, FILE *fp2 ) {
  char str1[ MAX_SIZE ], str2[ MAX_SIZE ], *p, *q;
  str1[ 0 ] = '\0';
  str2[ 0 ] = '\0';
  p = str1, q = str2;

  while ( strcmp( str1, str2 ) == 0 ) {
    if ( p == NULL ) {
      return;
    }
    p = fgets( str1, sizeof( str1 ), fp1 );
    q = fgets( str2, sizeof( str2 ), fp2 );
  }
  fprintf( stdout, "< %s\n", str1 );
  fprintf( stdout, "> %s\n", str2 );
}
