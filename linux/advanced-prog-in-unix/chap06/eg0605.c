/*
 * eg0605.c
 * implementation of getspnam.
 * using getspent, setspent and endspent.
 */
#include <stdio.h>
#include <string.h>
#include <shadow.h>
#include <errno.h>

int main( int argc, char **argv ) {
  struct spwd *p;
  while ( --argc > 0 ) {
    if ( (p = getspnam( *++argv )) == NULL ) {
      fprintf( stderr, "getspnam failed: %s\n", strerror( errno ) );
      continue;
    }
    printf( "%s, %s\n", p->sp_namp, p->sp_pwdp );
  }
  return 0;
}
