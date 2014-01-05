/*
 * $Header$
 *
 * Hitlion.Warrior.King				$Date$
 *
 * debugmen.c - Poorly wirtten program to debug.
 *
 * Revision History
 * $Log$
 */
static const char rcsid[] = "$Id$";

#include <stdio.h>
#include <stdlib.h>
#define BIGNUM 5000

void index_to_the_moon( int a[] );

int main( int argc, char **argv )
{
  int intary[ 100 ];
  index_to_the_moon( intary );
  exit( EXIT_SUCCESS );

}

void index_to_the_moon( 
  int a[] 
) {
  int i;

  for ( i = 0; i < BIGNUM; ++i ) {
    a[ i ] = i;
  }
}
/* End $Source$ */
