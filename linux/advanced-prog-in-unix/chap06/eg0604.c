/*
 * eg0604.c
 * implementation of getpwnam.
 * Using getpwent, setpwent and endpwent.
 */
#include <stdio.h>
#include <pwd.h>
#include <string.h>

int main( int argc, char **argv ) {
  struct passwd *p;
  while ( --argc > 0 ) {
    /* rewind the passwd entry file, just in case someone left it open */
    setpwent();
    argv++;
    while ( (p = getpwent()) != NULL ) {
      if ( strcmp( p->pw_name, *argv ) == 0 ) {
	/* match found */
	printf( "%s, %d, %d, %s, %s, %s\n", p->pw_name, p->pw_uid, p->pw_gid, p->pw_gecos,
	    p->pw_dir, p->pw_shell );
	break;
      }
    }
    endpwent();
  }
  return 0;
}
