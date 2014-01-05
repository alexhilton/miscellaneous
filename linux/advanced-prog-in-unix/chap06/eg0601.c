/*
 * eg0601.c
 * implementation of getpwuid.
 * Using getpwent, setpwent and endpwent.
 */
#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
  struct passwd *p;
  int uid;
  while ( --argc > 0 ) {
    uid = atoi( *++argv );
    p = getpwuid( uid );
    printf( "%s, %d, %d, %s, %s, %s\n", p->pw_name, p->pw_uid, p->pw_gid, p->pw_gecos,
	p->pw_dir, p->pw_shell );
  }
  return 0;
}
