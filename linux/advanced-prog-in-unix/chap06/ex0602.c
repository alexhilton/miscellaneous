/*
 * eg0606.c
 * implementation of getspnam.
 * using getspent, setspent and endspent.
 */
#include <stdio.h>
#include <string.h>
#include <shadow.h>

int main( int argc, char **argv ) {
  struct spwd *p;
  while ( --argc > 0 ) {
    setspent();
    argv++;
    while ( (p = getspent()) != NULL ) {
      if ( strcmp( p->sp_namp, *argv ) == 0 ) {
	/* match found */
	printf( "%s, %s\n", p->sp_namp, p->sp_pwdp );
	break;
      }
    }
    endspent();
  }
  return 0;
}
