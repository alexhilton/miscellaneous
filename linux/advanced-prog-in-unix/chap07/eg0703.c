/*
 * eg0703.c
 * use setjmp and longjmp to switch between functions.
 */
#include <stdio.h>
#include <setjmp.h>
#include "../com/comhdr.h"

static void f1( int, int, int, int );
static void f2();

static jmp_buf jmpbuffer;
static int globval;

int main( int argc, char **argv ) {
  int autoval;
  volatile int volval;
  static int statval;
  register int regval;

  globval = 1;
  autoval = 2;
  regval = 3;
  volval = 4;
  statval = 5;
  if ( setjmp( jmpbuffer ) != 0 ) {
    printf( "after longjmp:\nglobval= %d, autoval= %d, regval= %d, volval= %d, statval= %d\n",
	globval, autoval, regval, volval, statval );
    return 0;
  }

  globval = 95;
  autoval = 96;
  regval = 97;
  volval = 98;
  statval = 99;
  f1( autoval, regval, volval, statval );
  return 0;
}

static void f1( int autoval, int regval, int volval, int statval ) {
  printf( "in f1():\nglobval= %d, autoval= %d, regval= %d, volval= %d, statval= %d\n",
      globval, autoval, regval, volval, statval );
  f2();
}


static void f2() {
  longjmp( jmpbuffer, 1 );
}
