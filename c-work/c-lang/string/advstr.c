/*
 * advstr.c
 * advanced string library function practices.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( void ) {
  char src[ 128 ], dst[ 128 ];
  char flag = 'y';
  while ( flag != 'n' ) { 
    printf( "input the first string source string\n" );
    /*cut off the newline speicifier*/
    fgets( src, sizeof( src ), stdin );
    printf( "input the second string destenation string\n" );
    scanf( "%*c" );
    fgets( dst, sizeof( dst ), stdin );
    printf( "============================================================\n" );
    printf( "strspn of src and dst is:\n" );
    printf( "\t %d\n", strspn( src, dst ) );
    printf( "strcspn of src and dst is:\n" );
    printf( "\t %d\n", strcspn( src, dst ) );
    printf( "============================================================\n" );
    printf( "strtok function:\n" );
    printf( "src and dst partitioning by ' ':\n" );
    printf( "\t %s\t%s\n", strtok( src, " " ), strtok( dst, " " ) );
    printf( "============================================================\n" );
    printf( "Continue or not?(y/n):" );
    scanf( " %c%*c", &flag );
  }
  return 0;
}
