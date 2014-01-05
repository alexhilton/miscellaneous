/**
 * fold.c
 * fold a long line into shorter ones with word wrapped.
 */
#include <stdio.h>
#include <string.h>

#define SIZE 256
#define TAB 8
#define COLUMN 20

int smartfold( char line[], char wrap[], int limit );
int barefold( char line[], char wrap[], int limit );
int dealtab( char line[], int limit );

int main( int argc, char **argv ) {
  char ch; /* for parse options */
  int (*func)( char *, char *, int ); /* use to select one of functions */
  func = barefold; /* barefold by default */
  while ( --argc > 0 && *(*++argv) == '-' ) {
    while ( (ch = *++(*argv)) != '\0' ) {
      switch ( ch ) {
	case 's':
	  /* option for smart fold */
	  func = smartfold;
	  break;
	case 'b':
	  /* option for barefold */
	  func = barefold;
	  break;
	default:
	  break;
      }
    }
  }

  char line[ SIZE ];
  char wrap[ 2 * SIZE ];
  int i;
  printf( "Input a very long line\n" );
  fgets( line, sizeof( line ), stdin );
  if ( dealtab( line, sizeof( line ) ) != 0 ) {
    printf( "error when deal with tab\n" );
    return 0;
  }
  printf( "after dealing tab:\n%s", line );
  for ( i = 0; i < COLUMN; i++ ) {
    putchar( '=' );
  }
  putchar( '\n' );
  if ( func( line, wrap, SIZE ) != 0 ) {
    printf( "error while folding\n" );
    return 0;
  } else {
    printf( "%s", wrap );
  }
  for ( i = 0; i < COLUMN; i++ ) {
    putchar( '=' );
  }
  putchar( '\n' );
  return 0;
}

int smartfold( char line[], char wrap[], int limit ) {
  int i, j, k, pos;
  for ( i = j = pos = 0; line[i] != '\0'; i++, j++ ) {
    if ( pos >= COLUMN ) {
      /* all troubles are here */
      if ( line[i] != ' ' && line[i] != '\n' ) {
	/* find last ' ' or '\n' in this section */
	k = i;
	while ( line[ k ] != ' ' && line[ k ] != '\n' ) {
	  k--;
	}
	/* now line[ k ] is ' ' or '\n' */
	j -= ( i - k );
	i = k;
      }
      wrap[ j ] = '\n';
      pos -= COLUMN;
    } else {
      wrap[ j ] = line[ i ];
      pos++;
    }
    if ( j >= limit ) {
      return -1;
    }
  }
  wrap[ j ] = '\0';
  return 0;
}


int barefold( char line[], char wrap[], int limit ) {
  int i, j, pos;
  for ( i = j = pos = 0; line[ i ] != '\0'; i++, j++ ) {
    if ( pos >= COLUMN ) {
      /* time for fold */
      wrap[ j ] = '\n'; 
      if ( line[i] != '\n' && line[i] != ' ' ) {
        i--; /* we cannot increment i this time */
      }
      pos -= COLUMN;
    } else {
      wrap[ j ] = line[ i ];
      pos++;
    }
    if ( j >= limit ) {
      return -1;
    }
  }
  wrap[ j ] = '\0';
  return 0;
}

int dealtab( char line[], int limit ) {
  int i, j, k, nextstop, nextcol;
  char tmp[ 256 ]; /* use dynamic allocation might be a better design */
  for ( i = j = 0; line[ i ] != '\0'; i++ ) {
    if ( line[ i ] == '\t' ) {
      nextstop = i + TAB - i % TAB;
      nextcol = nextstop + (COLUMN - nextstop % COLUMN) - COLUMN;
      printf( "nextstop=%d, nextcol=%d: %s\n", nextstop, nextcol, __func__ );
      if ( nextstop > nextcol ) {
	/* we need to expand this tab into corresponding blanks */
	printf( "get any: %s\n", __func__ );
	for ( k = i; k < nextstop; k++ ) {
	  tmp[ j++ ] = ' ';
	}
      } else {
	tmp[ j++ ] = line[ i ];
      }
    } else {
      tmp[ j++ ] = line[ i ];
    }
    if ( j >= limit ) {
      return -1;
    }
  }
  tmp[ j ] = '\0';
  strcpy( line, tmp );
  return 0;
}
