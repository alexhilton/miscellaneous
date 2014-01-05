/*
 * ex0502.c
 * copy from stdin to stdout.
 * We copy stdin into stdout by line-at-a-time. Our line buffer is short, only 4
 * bytes. Apparently, in most cases, the input will exceed our buffer. But why
 * it still work? That owes to buffering of standard I/O library. Your input
 * from keyboard are kept in I/O library's buffers, and fgets gets its buffer
 * from I/O's buffers. So here, I/O's buffering is going on. If you use a short
 * buffer to fgets and fputs, they will be called more.
 */
#include <stdio.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  /* char buf[ MAXLINE ]; */
  char buf[ 4 ];
  while ( fgets( buf, sizeof( buf ), stdin ) != NULL ) {
    /*
     * Reaching EOF when reading is quite normal.
     * If write a EOF, something must be wrong
     */
    if ( fputs( buf, stdout ) == EOF ) {
      err_sys( "fputs error" );
    }
  }
  /*
   * If you implement this program, you will either forget to check errors of
   * stdin and stdout with ferror, or, do it in the while loop. Both of them are
   * bad practices. You can check it after loop. 
   * Remember, if there is any error on stdin, loop will terminate
   */
  if ( ferror( stdin ) ) {
    err_sys( "stdin error" );
  }
  return 0;
}
