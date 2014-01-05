/*
 * ex0501.c
 * implement setbuf with setvbuf.
 */
#include <stdio.h>
#include "../com/comhdr.h"

static void mysetbuf( FILE *fp, char *buf );

int main( int argc, char **argv ) {
  char buf[ BUFSIZ ];
  mysetbuf( stdin, buf );
  return 0;
}

static void mysetbuf( FILE *fp, char *buf ) {
  if ( fp == NULL ) {
    setvbuf( fp, NULL, _IONBF, (size_t) 0 );
  } else {
    setvbuf( fp, buf, _IOFBF, BUFSIZ );
  }
}
