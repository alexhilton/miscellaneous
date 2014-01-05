/*
 * getchar.c
 * get a character from streams without hitting enter key.
 */
#include <stdio.h>
#include <stdlib.h>
int main() {
  int c;
  /* the terminal driver is in its ordinary line-at-a-time mode */
  system( "stty raw" );
  /* now the terminal driver is in character-at-a-time mode */
  c = getchar();
  system( "stty cooked" );
  /* the terminal driver is back in line-at-a-time mode */
  return 0;
}
