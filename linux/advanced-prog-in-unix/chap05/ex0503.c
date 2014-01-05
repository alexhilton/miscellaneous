/*
 * ex0503.c
 * check out the return codes of printf and analyze what happened if return code
 * is 0.
 * So, you see, return code of printf is the number of bytes output.
 * As a result, 0 will be returned by printf( "" ), which outputs nothing, zero
 * byte.
 */
#include <stdio.h>

int main( int argc, char **argv ) {
  int rc;
  rc = printf( "hello\n" );
  rc = printf( "rc is %d\n", rc );
  rc = printf( "last rc is %d\n", rc );
  printf( "last rc is %d\n", rc );
  rc = printf( "" );
  printf( "last rc is %d\n", rc );
  return 0;
}
