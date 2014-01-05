/*
 * constptr.c
 * a demonstration program about constant pointers and const 
 * qualifiers.
 */
#include <stdio.h>

void foo( const int a ) { }

int main( int argc, char *argv[] ) {
  const int limit = 10; /*upper limit of an array */
  int i = 8;
  const int *limitp = &limit; /* a constant pointer */
  int *p = &i; /*used to compare p and limitp*/
  char **str;
  const char **cstr;
  /*p = limitp;*/
  limitp = p;
  /*str = cstr;
  cstr = str;*/
  limitp = &i;
  int a = 10;
  const int ca = a;
  a = ca;
  foo( a );
  const int * const cpc = &limit;
  printf( "const int * const cpc = %d", *cpc );
  int * const *pcp; /* pcp is a pointer to const pointer-to-int */
  int ** const cpp; /* cpp is a const pointer to pointer-to-int */
  int * const cp = &i;
  pcp = &cp;

  return 0;
}
