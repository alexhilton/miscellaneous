/*
 * filename.c
 * $Header$
 *
 * descriptions pre-conditions. post-conditions and arguments, reurn value
 * etc.
 * 
 * Author: Hitlion Warrior King
 *
 * Date: $Date$
 *
 * Revision Log:
 * $Log$
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* RCS id */ 
static const char rcsid[] = "$Id$";

int main() {
  int pid = getpid();
  printf( "the process ID is %d\n", pid );

  return 0;
}

/* End of $Source$ */
