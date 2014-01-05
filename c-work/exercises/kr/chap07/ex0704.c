/**
 * ex0704.c
 * solution to ex0704
 * a bare bone implementation of scanf, here is called miniscanf.
 */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int miniscanf( char *fmt, ... );
char getword( char *word, int limit );
char getch();
void ungetch( char ch );
char buf[ 128 ];
int bufp = 0;

int main( int argc, char **argv ) {
  printf( "integer, double, string and char \n" );
  int val;
  miniscanf( "%d", &val );
  printf( "case 1: integer is %d\n", val );
  double dval;
  miniscanf( "%f", &dval );
  printf( "case 2: double is %g\n", dval );
  char buf[ 128 ];
  miniscanf( "%s", buf );
  printf( "case 3: string is %s\n", buf );
  char ch;
  miniscanf( "%c", &ch );
  printf( "case 4: char is %c\n", ch );
  printf( "together\n" );
  miniscanf( "%d %f %s %c", &val, &dval, buf, &ch );
  printf( "int: %d f: %g str: %s ch: %c\n", val, dval, buf, ch );
  return 0;
}

int miniscanf( char *fmt, ... ) {
  va_list ap;
  int *ival, *ch, rt = 0;
  double *dval;
  char word[ 128 ], *str, *p;

  va_start( ap, fmt );
  for ( p = fmt; *p != '\0'; p++ ) {
    if ( *p == '%' ) {
      rt++;
      getword( word, 128 );
      if ( !isalnum( *word ) ) {
	continue;
      }
      switch ( *++p ) {
      case 'd':
	ival = va_arg( ap, int * );
	*ival = atoi( word );
	break;
      case 'f':
	dval = va_arg( ap, double * );
	*dval = atof( word );
	break;
      case 'c':
	ch = va_arg( ap, int * );
	*ch = *word;
	break;
      case 's':
	str = va_arg( ap, char * );
	strcpy( str, word );
	break;
      default:
	break;
      }
    }
  }
  printf( "return value of miniscanf is %d\n", rt );
  va_end( ap );
  return rt;
}

/* get next word from input stream. */
char getword( char *word, int limit ) {
  char ch;
  char *w = word;

  while ( isspace( ch = getch() ) )
    ;
  if ( ch != EOF ) {
    *w++ = ch;
  }

  if ( !isalnum( ch ) && ch != '.' ) {
    *w = '\0';
    return ch;
  }

  for ( ; --limit > 0; w++ ) {
    if ( !isalnum( *w = getch() ) && *w != '.' ) {
      ungetch( *w );
      break;
    }
  }
  *w = '\0';
  return *word;
}

char getch() {
  return bufp > 0 ? buf[ --bufp ] : getchar();
}

void ungetch( char ch ) {
  if ( bufp >= 128 ) {
    printf( "error: pushing too many chars back\n" );
  } else {
    buf[ bufp++ ] = ch;
  }
}
