/*
 * $Header$
 *
 * Hitlion.Warrior.King				$Date$
 *
 * a program detects environment.
 *
 * Revision History
 * $Log$
 */
static const char rcsid[] = "$Id$";

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static const int s = 23;	/* static var */
/* Private functions prototype(s) */
/*
 * Dump item's address to be sorted;
 */
void dump_addr(		/* this must be extern */
  FILE *p,		/* file pointer for outputing */
  const char *desc,	/* destination file name */
  const void *addr	/* address string */
);

/*
 * Splat out unprintable characters.
 */
static void mk_printable(
  char *buf		/* string to be printed */
);

/*
 * test (static) function2;
 */
static void fun2(
  FILE *p
);

/*
 * test (extern) function1;
 */
void fun1(
  FILE *p
);

/*
 * dump the environment + various selected
 * address.
 */
void dump(
  const char *envp[],
  const char *heading
);

/* Main program */
int main( int argc, char **argv, const char *envp[] )
{
  /*
   * This dump() call will dump our unmodified environment;
   */
  dump( envp, "INITIAL ENVIRONMENT: " );

  /*
   * Here we'll create two new environment variables
   * NVAR1 AND NVAR2
   */
  if ( putenv( "NVAR1=New Variable" ) == -1 ) {
    fprintf( stderr, "%s: putenv()\n", strerror( errno ) );
    exit( 13 );
  }
  if ( putenv( "NVAR2=New Variable 2" ) == -1 ) {
    fprintf( stderr, "%s: putenv()\n", strerror( errno ) );
    exit( 13 );
  }

  /*
   * Here we change the value of our TERM variable, to
   * see what changes take place for an existing exported
   * environment variable here;
   */
  if ( putenv( "TERM=oink-term" ) == -1 ) {
    fprintf( stderr, "%s: putenv()\n", strerror( errno ) );
    exit( 13 );
  }

  /*
   * Now that we've modified our environment, let us
   * see what havoc we wreaked;
   */
  dump( envp, "MODIFIED ENVIRONMENT:" );
  /* this waits for the sort output */
  sleep( 1 );

  /*
   * this simple test just proves that the new value
   * for TERM has been changed;
   */
  printf( "\ngetev( 'TERM' ) = '%s';\n", getenv( "TERM" ) );

  return ( 0 );
}

/*
 * function: dump_addr
 * usage;
 *
 * dump item's address to be sorted,
 */
void dump_addr(		
  FILE *p,
  const char *desc,
  const void *addr
) {
  fprintf( p, "0x%08lx %-32s\t%lu\n",
    ( long ) addr, desc, ( unsigned long ) addr );
}

/*
 * splat out unprintable character 
 */
static void mk_printable(
  char *buf
) {
  for ( ; *buf; buf++ ) {
    if ( *buf <= ' ' || *buf >= EOF ) {
      *buf = 0;
    }
  }
}


/*
 * function: fun2
 * 
 * test (static) function2
 */
static void fun2(
  FILE *p
) {
  int f2;

  dump_addr( p, "&f2", &f2 );
}


/*
 * function; fun1
 *
 * test ( extern ) function 1;
 */
void fun1(
  FILE *p
) {
  int f1;

  dump_addr( p, "&f1", &f1 );

  fun2( p );
}


/*
 * dump the environment + various selected addresses;
 */
void dump(
  const char *envp[],
  const char *heading
) {
  int x;		/* indexes envp[ x ] */
  char *cp;		/* work pointer */
  char buf[ 32 ];	/* local buffer */
  FILE *p = 0;		/* Pipe FILE pointer */

  /*
   * open a pipe to sort all address by decreasing
   * address, so that the last displayed address
   * will be the lowest addressed item;
   */
  if ( !( p = popen( "sort -n -r -k3", "w" ) ) ) {
    fprintf( stderr, "%s: popen( 'sort ...');\n",
      strerror( errno ) );
    exit( 13 );
  }

  /*
   * display a heading
   */
  printf( "\n%s\n\n", heading );
  fflush( stdout );

  /*
   * display environment variables:
   */
  for ( x = 0; envp[ x ] != 0; ++x ) {
    /* put '&' in first col */
    buf[ 0 ] = '&';
    strncpy( buf + 1, envp[ x ], sizeof( buf - 2 ) );
    /* make sure we have a null */
    buf[ sizeof( buf - 1 ) ] = 0;
    /* splat out special chars */
    mk_printable( buf );
    /* dump this var's address */
    dump_addr( p, buf, envp[ x ] );

    /*
     * special test for TERM variable
     * here we discard the '=' and what follows
     */
    if ( ( cp = strchr( buf, '=' ) ) != 0 ) {
      cp = 0;
    }

    /*
     * test if envp[x] is the "TERM" entry.
     */
    if ( !strcmp( buf + 1, "TERM" ) 	/* got "term" ? */
      && ( cp = getenv( "TERM" ) ) != 0 /* 'term' defined ? */
      && cp != envp[ x ] + 5 ) {	/* ptrs mismatch? */

      strcpy( buf, "@TERM=" );		/* yes, mark this */
      /* copy new val. */
      strncpy( buf + 6, cp, sizeof( buf - 7 ) );
      buf[ sizeof( buf - 1 ) ] = 0;	/* enforce nul byte */
      mk_printable( buf );		/* splat out */
      dump_addr( p, buf, cp );		/* dump this entry */
    }
  } /* end of for */

  /* start of envp[] */
  dump_addr( p, "&envp[0]", &envp[ 0 ] );
  sprintf( buf, "&envp[ %u ]", x );
  /* dump end of envp[] */
  dump_addr( p, buf, &envp[ x ] );

  /* dump static &s addr */
  dump_addr( p, "&s", &s );
  /* dump auto &x addr */
  dump_addr( p, "&x", &x );

  fun1( p );			

  dump_addr( p, "stderr", stderr );	/* dump stderr address */
  dump_addr( p, "stdout", stdout );	/* dump stdout address */
  dump_addr( p, "sdtin", stdin );	/* dump stdin address */

  dump_addr( p, "fprintf", fprintf );	/* dump fprintf addr */
  dump_addr( p, "main", main );	/* dump main addr */
  dump_addr( p, "dump", dump );	/* dump dump addr */
  dump_addr( p, "fun1", fun1 );	/* dump fun1 addr */
  dump_addr( p, "fun2", fun2 );	/* dump fun2 addr */

  /* is NVAR1 defined */
  if ( ( cp = getenv( "NVAR1" ) ) != 0 ) {
    dump_addr( p, "&NVAR1", cp );
  }
  /* is NVAR2 defined */
  if ( ( cp = getenv( "NVAR2" ) ) != 0 ) {
    dump_addr( p, "&NVAR2", cp );
  }

  /*
   * by closing this pipe now, we'll start sort on its
   * merry way, sorting our results. the sort output
   * will be sent to standard output.
   */
  pclose( p );
}

/* End $Source$ */

