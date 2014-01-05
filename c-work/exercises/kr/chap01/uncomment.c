/**
 * uncomment.c
 * this program is to remove all the comments of a leagal C program, which has
 * no compilation errors.
 */
#include <stdio.h>

/* for testing */
char b[] = "''', /// \\, abfdl /*, */, //* '*/, you'd better keep this line as it was ";
char a = '"';
#define debug "/*for debug */, ha ha */, /*, /* you cannot remove this line */"

static int in_comment = 0; /* boolean variable indicating whether in comments or not */
static int in_quote = 0; /* whether in double quotes, string constants */
static int in_char = 0; /* whether in character constant, this is obscure */

static int remove_comment( FILE *in, FILE *out );

int main( int argc, char **argv ) {
  if ( remove_comment( stdin, stdout ) != 0 ) {
    printf( "error: error when removing comments\n" );
    return 0;
  }
  return 0;
}

static int remove_comment( FILE *in, FILE *out ) {
  char ch, prev, next;
  while ( (ch = fgetc( in )) != EOF ) {
    /* 
     * we will ignore character constant: i.e. char has been backslashed '\\' or
     * others
     */
    if ( ch == '\\' ) {
      /* ignore it */
      fputc( ch, out );
      ch = fgetc( in );
      if ( ch == EOF ) {
	break;
      }
    }
    if ( ch == '/' ) {
      if ( (ch = fgetc( in )) == '*' && !in_quote ) {
	in_comment = 1;
	while ( in_comment ) {
	  /* we read until end of comments */
	  while ( (ch = fgetc( in )) != EOF && ch != '*' )
	    ;
	  if ( ch == EOF ) {
	    break;
	  }
	  /* now ch is '*', we need to check next one */
	  next = fgetc( in );
	  if ( next == EOF ) {
	    break;
	  }
	  if ( next == '/' ) {
	    /* end of comments */
	    /*
	     * Note: 
	     * Here we have to read one more char from input stream, otherwise you
	     * will print one '/' all the time. Here is out of comments, but the 
	     * ch = '/', so in the following output segments, it will print ch,
	     * since it is out of comment, but the ch is '/'. As a result, we need
	     * to read one more. Be cautious about EOF, it can happen everywhere.
	     * You'd better check it every time read a new char.
	     */
	    ch = fgetc( in );
	    if ( ch == EOF ) {
	      break;
	    }
	    in_comment = 0;
	  } else {
	    /* move forward */
	    ch = next;
	  }
	}
      } else {
	if ( ch == EOF ) {
	  break;
	}
	/* we don't have to push it back, we can output two chars, '/' and ch */
	fputc( '/', out );
      }
    }

    /*
     * Now, it is normal output, no matter what this char is, we have to output
     * it. But it might other special chars, like quotes or char constants.
     * So we had better check it before we put it onto some output stream.
     */
    if ( ch == '\'' && !in_quote ) {
      prev = fgetc( in );
      next = fgetc( in );
      if ( next == '\'' ) {
	in_char = 1;
      } else {
	in_char = 0;
      }
      ungetc( next, in );
      ungetc( prev, in );
    }
    if ( ch == '"' && !in_char ) {
      if ( in_quote ) {
	in_quote = 0;
      } else {
	in_quote = 1;
      }
    } 

    fputc( ch, out );
  }
  return 0;
}
/* end of source */
