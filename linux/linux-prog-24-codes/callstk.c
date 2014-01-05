/*
 * $Header$
 *
 * Hitlion.Warrior.King				$Date$
 *
 * callstk.c - illustrate traversing the call stack with GDB.
 *
 * Revision History
 * $Log$
 */
static const char rcsid[] = "$Id$";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int make_key( void );
int get_key_num( void );
int number( void );

int main( int argc, char **argv )
{
  int ret = make_key();
  printf( " make_key returns %d\n", ret );
  exit( EXIT_SUCCESS );
}

int make_key( 
  void 
) {
  int ret = get_key_num();
  return ( ret );
}

int get_key_num(
  void
) {
  int ret = number();
  return ( ret );
}

int number(
  void 
) {
  return ( 10 );
}
/* End $Source$ */
