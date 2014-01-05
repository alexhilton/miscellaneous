#include <stdio.h>

extern char **environ;

int main( int argc, char *argv[], char *envp[] ) {
  int i;
  freopen( "output.dat", "w", stdout );
  printf( "\t\tCheck out what is in envp string\n" );
  for ( i = 0; envp[ i ] != NULL; i++ ) {
    printf( "%s\n", envp[ i ] );
  }
  /*
   * let's check out what in environ is.
   */
  printf( "\t\tThings in environ\n" );
  for ( i = 0; environ[ i ] != NULL; i++ ) {
    printf( "%s\n", environ[ i ] );
  }
  return 0;
}
