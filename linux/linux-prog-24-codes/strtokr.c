/*
 * venture strtok_r() function.
 */
#include <string.h>
#include <stdio.h>

int main( int argc, char *argv[] ) {
  char *my_argv[ 64 ]; /* collected argv[] */
  int my_argc; 
  char *svptr; /* strtok_r() updates this */
  char *s; /* returned strtok_r() pointer */
  char buf[ 256 ]; /* command buffer */

  int i;
  static const char delim[] = " \n"; /* delimiters */

  strcpy( buf, "rm -fr core d\n" );

  s = strtok_r( buf, delim, &svptr );
  my_argc = 0;

  while ( s != NULL ) {
    my_argv[ my_argc++ ] = s;
    s = strtok_r( NULL, delim, &svptr );
  }

  my_argv[ my_argc ] = NULL;

  /* print out collected values */
  for ( i = 0; i <= my_argc; i++ ) {
    if ( my_argv[ i ] != NULL ) {
      printf( "argv[%d] = '%s';\n", i, my_argv[i] );
    } else {
      printf( "argv[%d] = NULL;\n", i );
    }
  }
  return 0;
}
