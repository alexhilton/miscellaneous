/**
 * eg0503.c
 * Print the buffering information for stdin, stdout and stderr.
 */
#include <stdio.h>
#include "../com/comhdr.h"

static void pr_stdio( const char *name, FILE *fp );

int main( int argc, char **argv ) {
  FILE *fp;
  fputs( "enter any character\n", stdout );
  if ( getchar() == EOF ) {
    err_sys( "getchar error" );
  }
  fputs( "one line to standard error\n", stderr );

  pr_stdio( "stdin", stdin );
  pr_stdio( "stdout", stdout );
  pr_stdio( "stderr", stderr );

  if ( (fp = fopen( "/etc/motd", "r" )) == NULL ) {
    err_sys( "fopen error on /etc/motd" );
  }
  if ( getc( fp ) == EOF ) {
    err_sys( "getc error" );
  }
  pr_stdio( "/etc/motd", fp );
  return 0;
}

static void pr_stdio( const char *name, FILE *fp ) {
  printf( "stream = %s, ", name );

  /**
   * NOTE: the following codes are not portable
   */
  if ( (fp->_IO_file_flags & _IONBF) == _IONBF ) {
    printf( "unbuffered" );
  } else if ( (fp->_IO_file_flags & _IOLBF) == _IOLBF ) {
    printf( "line buffered" );
  } else if ( (fp->_IO_file_flags & _IOFBF) == _IOFBF ) {
    printf( "fully buffered" );
  }
  printf( ", buffer size = %d\n", fp->_IO_buf_end - fp->_IO_buf_base );
}
