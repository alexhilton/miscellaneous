/*
 * nulnull.c
 * a program to demonstrate nul or null specifiers.
 */
#include <stdio.h>

int main( void ) {
  char str[] = "you are a girl";
  char *p;
  printf( "can it end with 'nul' or '0' of its ASCII code\n" );
  for ( p = str; *p; p++ ) {
    putchar( *p );
  }
  printf( "\n\t*\t*\t*\n" );
  printf( "can it end with null\n" );
  int i = 0;
  for ( p = str; i < 20 && p != NULL; p++, i++ ) {
    putchar( *p );
  }
  printf( "\n\t*\t*\t*\t*\t*\n" );
  return 0;
}
