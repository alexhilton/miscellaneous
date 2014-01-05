/*
 * hello.c
 * If you compile this program and run it, test the exit code in shell with
 * 'echo $?' you will get 6, what is it? it is the length of the string you
 * printed. It is said that a non-exit code main program will return the value
 * in the registers. So we can guess, when output, the length of string is
 * calculated and kept in the registers, so it is returned as the exit code. 
 */
#include <stdio.h>
/* #include <string.h> */

void main() {
  printf( "hello\n" );
  /* printf( "%d\n", strlen( "Hello, world of linux\n" ) ); */
}
