/*
 * $Header$
 *
 * Hitlion.Warrior.King				$Date$
 *
 * badptr.c -- testing assert.
 *
 * Revision History
 * $Log$
 */
static const char rcsid[] = "$Id$";

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Private functions prototype(s) */

/* Main program */
int main( int argc, char **argv )
{
  FILE *fp;

  /* this should work */
  fp = fopen( "foo_bar", "w" );
  assert( fp );
  fclose( fp );

  /* this should fail */
  fp = fopen( "bar_baz", "r" );
  assert( fp );
  /* should never get here */
  fclose( fp );

  exit( EXIT_SUCCESS );
}
/* End $Source$ */
