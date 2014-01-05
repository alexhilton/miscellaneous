/*
 * sizede.c
 * sizeof determintation exercises.
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct Node {
  int data;
  struct Node *next;
} *Node;

typedef struct Point {
  int x;
  int y;
} *Point_t;

int main( int argc, char **argv ) {
  char *a, b[ 128 ];
  Point_t tmp;
  int *c, d;
  void *e;
  printf( "the size of b[128] is %d\n", sizeof( b ) );
  a = malloc( 128 );
  printf( "the sizeof a = malloc( 128 ) is %d\n", sizeof( a ) );
  printf( "the sizeof *a is %d\n", sizeof( *a ) );
  printf( "the sizeof struct Point_t is %d\n", sizeof( Point_t ) );
  printf( "the sizeof struct *Point_t is %d\n", sizeof( *tmp ) );
  printf( "the sizeof int *c is %d\n", sizeof( c ) );
  printf( "the sizeof *c is %d\n", sizeof( *c ) );
  printf( "the sizeof int d is %d\n", sizeof( d ) );
  printf( "the sizeof int *e is %d\n", sizeof( e ) );
  printf( "the sizeof *e is %d\n", sizeof( *e ) );
  Node tmp1;
  printf( "the sizeof struct Node is %d\n", sizeof( Node ) );
  printf( "the sizeof struct *Node is %d\n", sizeof( *tmp1 ) );
  int i[ 10 ];
  printf( "the sizeof i[ 10 ] is %d\n", sizeof( i ) );
  printf( "the test of arrays of array, strings of string\n" );
  int **intarr1;
  int *intarr2[ 10 ];
  char **str1;
  char *str2[ 10 ];
  intarr1 = ( int ** ) malloc(  SIZE * sizeof( int * ) );
  str1 = ( char ** ) malloc( SIZE * sizeof( char * ) );
  int k = 0;
  for ( k = 0; k < SIZE; k++ ) {
    intarr1[ k ] = ( int * ) malloc( SIZE * sizeof( int ) );
    str1[ k ] = ( char * ) malloc( SIZE * sizeof( char ) );
  }
  for ( k = 0; k < 10; k++ ) {
    intarr2[ k ] = ( int * ) malloc( SIZE * sizeof( int ) );
    str2[ k ] = ( char * ) malloc( SIZE * sizeof( char ) );
  }
  printf( "sizeof intarr1 is %d\n", sizeof( intarr1 ) );
  printf( "sizeof *intarr1 is %d\n", sizeof( *intarr1 ) );
  printf( "sizeof intarr2 is %d\n", sizeof( intarr2 ) );
  printf( "sizeof *intarr2 is %d\n", sizeof( *intarr2 ) );
  printf( "sizeof intarr2[ 0 ] is %d\n", sizeof( intarr2[ 0 ] ) );
  printf( "sizeof str1 is %d \n", sizeof( str1 ) );
  printf( "sizeof *str1 is %d \n", sizeof( *str1 ) );
  printf( "sizeof str2 is %d \n", sizeof( str2 ) );
  printf( "sizeof *str2 is %d \n", sizeof( *str2 ) );
  printf( "sizeof str2[ 0 ] is %d \n", sizeof( str2[ 0 ] ) );
  return 0;
}
