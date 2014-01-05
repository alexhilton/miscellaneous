/**
 * eg0201.c
 * Fig 0213 on book.
 * Print all possible sysconf and pathconf values.
 * sysconf retrieve limits about system.
 * pathconf and fpathconf retrieve limits about a file.
 * all of them returning -1 indicates error and set errno as EINVAL.
 * if returning -1 and do not set errno, then means this entry is not defined by
 * current implementation.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "../com/comhdr.h"

static void pr_sysconf( char *msg, int name );
static void pr_pathconf( char *msg, char *path, int name );

int main( int argc, char **argv ) {
  if ( argc != 2 ) {
    err_quit( "usage: prog <dirname>" );
  }
#ifdef ARG_MAX
  /* i cannot imagine why it has '+0' down there */
  printf( "ARG_MAX defined to be %d\n", ARG_MAX+0 );
#else
  printf( "no symbol for ARG_MAX\n" );
#endif
#ifdef _SC_ARG_MAX
  pr_sysconf( "ARG_MAX = ", _SC_ARG_MAX );
#else
  printf( "no symbol for _SC_ARG_MAX\n" );
#endif

#ifdef MAX_CANON
  printf( "MAX_CANON defined to be %d\n", MAX_CANON+0 );
#else
  printf( "no symbol for MAX_CANON\n" );
#endif
#ifdef _PC_MAX_CANON
  pr_pathconf( "MAX_CANON=", argv[ 1 ], _PC_MAX_CANON );
#else
  printf( "no symbol for _PC_MAX_CANON\n" );
#endif
  return 0;
}

static void pr_sysconf( char *mesg, int name ) {
  long val;
  fputs( mesg, stdout );
  errno = 0;
  if ( (val = sysconf( name )) < 0 ) {
    if ( errno != 0 ) {
      if ( errno == EINVAL ) {
	fputs( " (not supported)\n", stdout );
      } else {
	err_sys( "sysconf error" );
      }
    } else {
      fputs( " (no limits)\n", stdout );
    }
  } else {
    printf( " %ld\n", val );
  }
}

static void pr_pathconf( char *mesg, char *path, int name ) {
  long val;
  fputs( mesg, stdout );
  errno = 0;
  if ( (val = pathconf( path, name )) < 0 ) {
    if ( errno != 0 ) {
      if ( errno == EINVAL ) {
	fputs( " (not supported)\n", stdout );
      } else {
	err_sys( "pathconf error, path = %s", path );
      }
    } else {
      fputs( " (no limit)\n", stdout );
    }
  } else {
    printf( " %ld\n", val );
  }
}
