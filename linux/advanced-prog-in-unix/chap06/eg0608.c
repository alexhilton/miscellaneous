/*
 * eg0608.c
 * implementation of getgruid.
 * Using getgrent, setgrent and endgrent.
 */
#include <stdio.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  struct group *p;
  int gid;
  while ( --argc > 0 ) {
    gid = atoi( *++argv );
    setgrent();
    while ( (p = getgrent()) != NULL ) {
      if ( gid == p->gr_gid ) {
	printf( "%s, %s, %d\n", p->gr_name, p->gr_passwd, p->gr_gid );
	while ( *p->gr_mem != NULL ) {
	  printf( "\t\t%s\n", *p->gr_mem++ );
	}
	break;
      }
    }
    endgrent();
  }
  return 0;
}
