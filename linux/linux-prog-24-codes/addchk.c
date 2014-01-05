/*
 * Linux platform memory address checking program.
 * addchk.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static const int s = 23; /* static variable */

/* 
 * prototype of main progra, first time meeting, eye-opening.
 */
extern int main( int argc, char *argv[], char *envp[] );

/*
 * Dump item's address to be sorted 
 */
void dumpAddr( FILE *p, const char *desc, const void *addr ) {
  fprintf( p, "0x%08lX %-32s\t%lu\n",
	   (long) addr, desc, (unsigned long) addr );
}

/*
 * Splat out unprintable characters.
 */
static void mkPrintable( char *buf ) {
  for ( ; *buf; buf++ ) {
    if ( *buf <= ' ' || *buf >= 0x7f ) {
      *buf = '@';
    }
  }
}

/*
 * Test (static) Function 2:
 */
static void fun2( FILE *p ) {
  int f2;
  dumpAddr( p, "&f2", &f2 );
}

/*
 * Test ( extern ) Function 1;
 */
void fun1( FILE *p ) {
  int f1;
  dumpAddr( p, "&f1", &f1 );
  fun2( p );
}

/*
 * Dump the environment + various selected addresses:
 * ARGUMENTS:
 *     envp      pointer to the argument(from main)
 *     heading   display heading comment
 */
void dump( char *envp[], const char *heading ) {
  int i;
  char *cp;
  char buf[ 32 ];
  FILE *p = NULL;

  /*
   * Open a pipe to sort all address by decreasing address, so that the
   * last displayed address will be the lowest addressed item.
   */
  /* popen -- open a pipe, equally, pclose, close a pipe */
  if ( !( p = popen( "sort -n -r -k3", "w" ) ) ) {
    fprintf( stderr, "%s: popen('sort ...');\n", strerror( errno ) );
    exit( 13 ); /* what this stands for */
  }

  /* 
   * display a heading.
   */
  printf( "\n%s\n\n", heading );
  fflush( stdout );

  /*
   * Display environment variables:
   */
  for ( i = 0; envp[ i ] != NULL; i++ ) {
    buf[ 0 ] = '&';
    /* 
     * sizeof( buf ) = strlen( buf ) + 1
     * buf[0] is '&', buf[ strlen(buf) ] is '\0'
     * so we should copy sizeof( buf ) - 2, which means
     * copying strlen(buf+1) chars into buf+1.
     */
    strncpy( buf+1, envp[i], sizeof(buf)-2 );
    /* or: buf[ strlen(buf) ] = '\0' */
    buf[ sizeof(buf)-1 ] = '\0'; /* make sure it ends properly */
    mkPrintable( buf );
    dumpAddr( p, buf, envp[ i ] );

    /*
     * Special test for TERM variable:
     * Here we discard the '=' and what follows.
     */
    if ( ( cp = strchr( buf, '=' ) ) != 0 ) {
      *cp = 0;
    } /* kick out character '='.*/

    /*
     * Test if envp[ i ] is the "TERM" entry:
     */
    /* note that buf[0] is '&' */
    /*
     * TERM=abcd is a environment variable, TERM is name and abcd is
     * its value. cp = getenv( "TERM" ) return a pointer to "abcd",
     * or cp = "abcd". while envp[i] is "TERM=abcd", thus, cp is 
     * envp[i]+5.
     */
    if ( !strcmp( buf+1, "TERM" ) && (cp = getenv( "TERM" )) != 0
	 && cp != envp[ i ] + 5 ) { /* why plussing 5, what is it */
      strcpy( buf, "@TERM=" );
      /*
       * first six chars have been copied, see 'strcpy(buf,"@TERM=" )
       * so we need to copy remaining sizeof(buf)-7 or strlen(buf)-6 into
       * buf+6.
       */
      strncpy( buf+6, cp, sizeof( buf ) - 7 );
      buf[ sizeof( buf ) - 1 ] = '\0';
      mkPrintable( buf );
      dumpAddr( p, buf, cp );
    }
  }

  /* begin dumping */
  dumpAddr( p, "&envp[ 0 ]", &envp[ 0 ] );
  sprintf( buf, "&envp[%u]", i );
  dumpAddr( p, buf, &envp[ i ] );

  dumpAddr( p, "&s", &s );
  dumpAddr( p, "&i", &i );

  fun1( p ); /* Call upon fun1() */

  dumpAddr( p, "stderr", stderr );
  dumpAddr( p, "stdout", stdout );
  dumpAddr( p, "stdin", stdin );

  dumpAddr( p, "fprintf", fprintf );
  dumpAddr( p, "main", main );
  dumpAddr( p, "dump", dump );
  dumpAddr( p, "fun1", fun1 );
  dumpAddr( p, "fun2", fun2 );

  /* if there is environment variable called NVAR! and NVAR2 */
  if ( (cp = getenv( "NVAR1" )) != NULL ) {
    dumpAddr( p, "&NVAR1", cp );
  }
  if ( (cp = getenv( "NVAR2" )) != NULL ) {
    dumpAddr( p, "&NVAR2", cp );
  }

  /*
   * By closing this pipe now, we'll start sort on its merry way,
   * sorting our results. The sort output will be sent to standard
   * output.
   */
  pclose( p );
} /* end of dump function */

/*
 * The main program
 */
int main( int argc, char *argv[], char *envp[] ) {
  /*
   * This dump() call will dump our unmodified
   * environment.
   */
  dump( envp, "INITIAL ENVIRONMENT:" );

  /*
   * Here we will create two new environment vairables NVAR1 and NVAR2.
   */
  if ( putenv( "NVAR1=New Variable" ) == -1 ) {
    fprintf( stderr, "%s: putenv()\n", strerror( errno ) );
    exit( 13 ); /* here is again */
  }

  if ( putenv( "NVAR2=New Variable 2" ) == -1 ) {
    fprintf( stderr, "%s: putenv()\n", strerror( errno ) );
    exit( 13 );
  }

  /*
   * Here we change the value of our TERM variable, to see
   * what changes take place for an existing exported environment
   * variable here:
   */
  if ( putenv( "TERM=oink-term" ) == -1 ) {
    fprintf( stderr, "%s: putenv()\n", strerror( errno ) );
    exit( 13 );
  }

  /* 
   * Now that we have modified our environment, let us see what
   * have we wreaked;
   */
  dump( envp, "MODIFIED ENVIRONMENT:" );
  sleep( 1 ); /* wait for the sort output */

  /*
   * this simple test just proves that the new value for
   * TERM has been changed.
   */
  printf( "\ngetenv('TERM') = '%s';\n", getenv("TERM") );

  return 0;
}
