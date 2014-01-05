/*
 * implement a function that read the whole line into a string,
 * same to gets but safer.
 * Comparision of fgets and our getline:
 * 	#1: they can read a whole line untill RETURN is encountered.
 * 	#2: they can check the overflow problem, when input is exceed
 * 	    the length of buffer designated, error will report.
 * 	#3: getline will discard '\n', and change it into '\0'
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getline( char *str, int len, FILE *in );

int main( int argc, char *argv[] ) {
  char line[ 20 ];
  printf( "input a line\n" );
  getline( line, sizeof( line ), stdin );
  printf( "the line youhave just input is \n'%s'\n", line );
  printf( "and its size is: %d\n", strlen( line ) );
  printf( "\t comparision with fgets:\n" );
  printf( "input a line\n" );
  fgets( line, sizeof( line ), stdin );
  printf( "the line is '%s'\n", line );
  printf( "its length is %d\n", strlen( line ) );
  return 0;
}

int getline( char str[], int len, FILE *in ) {
  int i = 1;
  while ( (*str = fgetc( in )) != EOF ) {
    if ( i > len ) {
      *str = '\0';
      fprintf( stderr, "Error: Buffer overflow\n" );
      return -1;
    }
    if ( *str == '\n' ) {
      *str = '\0';
      return 0;
    }
    str++;
    i++;
  }
  return -1;
}
