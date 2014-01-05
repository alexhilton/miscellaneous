/*
 * implementation of getline.h
 * 
 * read a whole line from FILE in, return the length of read string.
 */
#include <stdio.h>

int getline( FILE *in, char s[ ], int lim ) {
  char ch;
  int i;
  for ( i = 0; i < lim && (ch = fgetc(in)) != EOF; i++ ) {
    if ( ch == '\n' ) {
      s[ i++ ] = '\0';
      return i;
    } else {
      s[ i ] = ch;
    }
  }
  s[ i ] = '\0';
  return i;
}
