/*
 * ex0504.c
 * portability problem of character-based I/O: getc, putc, getchar and putchar
 * -------This is not the point--------
 * getchar and getc return an int rahter than char. So if there is an truncate
 * of int to covert int into char. In some platform, the higher byte are
 * higher addresses; on others, higher byte are at lower addresses. So results
 * will be different when truncate int  into char. Int is four bytes, char is
 * two bytes, so on some platform you will get lower two bytes; But on others,
 * you will get higher two bytes.
 * --------------The point is---------------------
 * return value of getchar is int, not char and EOF is defined as -1. So if char
 * is defined as signed, then nothing can go wrong. If char is defined as
 * unsigned, when EOF is returned by getchar, it will be converted and store
 * into unsigned char, which will lose its sign. As a result, the loop will
 * never terminates. Fortunately, seldom system use unsinged char.
 */
#include <stdio.h>

int main( int argc, char **argv ) {
  char ch;
  while ( (ch = getchar()) != EOF ) {
    putchar( ch );
  }
  return 0;
}
