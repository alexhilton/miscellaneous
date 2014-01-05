/**
 * ex0703.c
 * solution to ex0703.
 * a bare bone implementation of printf, here we call it miniprintf.
 */
#include <stdio.h>
#include <stdarg.h>

int miniprintf( char *fmt, ... );

int main( int argc, char **argv ) {
  miniprintf( "test case 1: d and int: %d\n", 1234 );
  miniprintf( "test case 2: h and short: %h\n", 1234 );
  miniprintf( "test case 3: c and char: %c\n", 'a' );
  miniprintf( "test case 4: o and int: %o\n", 1234 );
  miniprintf( "test caes 5: x and int: 0x%x\n", 1234 );
  miniprintf( "test case 55: g and double: %g\n", 1234.03 );
  miniprintf( "test case 6: s and str: %s\n", "girl and sex" );
  miniprintf( "test case 7: all %d %h %c %o %x %s\n", 1234, 1234, 'a', 1234, 1234, "over" );
  return 0;
}

int miniprintf( char *fmt, ... ) {
  va_list ap;
  int rt = 0;
  char *p = fmt;

  double dval;
  int ival, oval, xval;
  short hval;
  char ch, *str;
  va_start( ap, *fmt );
  for ( p = fmt; *p != '\0'; p++ ) {
    if ( *p != '%' ) {
      //if ( *p == '\\' ) {
      putchar( *p );
    } else {
      rt++;
      switch ( *++p ) {
      case 'd':
	ival = va_arg( ap, int );
	printf( "%d", ival );
	break;
      case 'h':
	hval = va_arg( ap, int );
	printf( "%d", hval );
	break;
      case 'g':
	dval = va_arg( ap, double );
	printf( "%g", dval );
	break;
      case 'o':
	oval = va_arg( ap, int );
	printf( "%o", oval );
	break;
      case 'x':
	xval = va_arg( ap, int );
	printf( "%x", xval );
	break;
      case 'c':
	ch = va_arg( ap, int );
	putchar( ch );
	break;
      case 's':
	str = va_arg( ap, char * );
	printf( "%s", str );
	break;
      default:
	break;
      }
    }
  }
  va_end( ap );
  printf( "return of miniprintf is %d\n", rt );
  return rt;
}
