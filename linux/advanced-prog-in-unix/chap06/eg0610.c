/*
 * eg0610.c
 * implementation of getgrnam.
 * Using getgrent, setgrent and endgrent.
 */
#include <stdio.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  struct group *p;
  while ( --argc > 0 ) {
    setgrent();
    argv++;
    while ( (p = getgrent()) != NULL ) {
      if ( strcmp( *argv, p->gr_name ) == 0 ) {
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
