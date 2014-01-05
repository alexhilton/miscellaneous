/*
 * adventure more advanced topics of string library.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main( int argc, char *argv[] ) {
  char str1[ 128 ], str2[ 128 ];
  char *p;
  /* step 1: more comparision functions */
  printf( "Step 1: more string comparision functions\n" );
  printf( "Input two strings:\n" );
  printf( "?: " );
  scanf( "%s", str1 );
  printf( "?: " );
  scanf( "%s", str2 );
  printf( "strcasecmp(%s, %s) is %d\n", str1, str2, 
	  strcasecmp( str1, str2 ) );

  /* step 2: strdup() function */
  printf( "Step 2: strdup() function\n" );
  printf( "Input a string: " );
  scanf( "%s", str1 );
  p = strdup( str1 );
  printf( "str2 = strdup( %s ) is %s\n", str1, p );
  free( p ); /* this is very necessary, otherwise memory leak occurs */

  /* step 3: strpbrk() function */
  printf( "strpbrk( '12-31-1999', '/-' ) = '%s'\n", 
	  strpbrk( "12-31-1999", "/-" ) );

  /* step 4: strspn() and strcspn() functions */
  printf( "strspn('12/31/1999', '/-') is %d\n",
	  strspn( "12/31/1999", "/-" ) );
  printf( "strcspn('12/31/1999', '0123456789') is %d\n",
	  strcspn( "12/31/1999", "!@#$" ) );
  return 0;
}
