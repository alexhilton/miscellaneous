/*
 * eg0607.c
 */
#include <stdio.h>
#include <errno.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  struct group *p;
  int gid;
  while ( --argc > 0 ) {
    gid = atoi( *++argv );
    if ( (p = getgrgid( gid )) == NULL ) {
      fprintf( stderr, "getgruid failed: %s\n", strerror( errno ) );
      continue;
    }
    printf( "%s, %s, %d\n", p->gr_name, p->gr_passwd, p->gr_gid );
    while ( *p->gr_mem != NULL ) {
      printf( "\t\t%s\n", *p->gr_mem++ );
    }
  }
  return 0;
}
