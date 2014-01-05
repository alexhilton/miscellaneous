/*
 * filefch.c -- using __LINE__and__FILE__
 */
#include <stdio.h>
#include "filefch.h"

int open_file(
  FILE **fp,
  char *fname,
  char *mode,
  int line,
  char *file
) {
  if ( ( *fp = fopen( fname, mode ) ) == NULL ) {
    fprintf( stderr, "[%s:%d] open_file() failed\n", 
      file, line );
  }

  return ( 0 );
}
