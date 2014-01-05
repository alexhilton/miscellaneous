/**
 * ex0306.c
 * Verify whether we can lseek an file opened with read write and append flag.
 * The file input for this program is a 4 row * 8 char one each row.
 * First we test whether we can read from any where, we will read 10 chars from
 * 10th char, it will contain a '\n' among the read buffer.
 * Then we will change the third row with its upper case.
 * ####Testing result:
 * Here is the output without flag append:
 *	jklmn
 *	opqr
 *	=======
 *	abcdefg
 *	hijklmn
 *	HIJKLMN # replace the third row successfully
 *	vwxyzAB
 * ----------------------
 * Here is the output with append flag:
 *      jklmn
 *      opqr
 *      =======
 *      abcdefg
 *      hijklmn
 *      opqrstu # nothing changed, but appened
 *      vwxyzAB
 *      HIJKLMN
 * From the output we can conclude that with append flag O_APPEND, we can read
 * from any where we like by lseeking. But we can write only starting from end
 * of file, or we can append texts only, we cannot overwrite it or replace it.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  int fd, n;
  if ( (fd = open( "input.dat", O_RDWR | O_APPEND, 0 )) < 0 ) {
    err_sys( "opening input.dat" );
  }
  /* now lseek up to 10 */
  if ( lseek( fd, 10L, SEEK_CUR ) == -1 ) {
    err_sys( "lseek error" );
  }
  char buf[ 128 ];
  /* read 10 chars */
  if ( (n = read( fd, buf, 10 )) < 0 ) {
    err_sys( "read error" );
  }
  if ( write( STDOUT_FILENO, buf, n ) != n ) {
    err_sys( "write error" );
  }
  printf( "\n=======\n" );

  /* now we replace the third row with its upper case */
  /* lseek to begining of third row */
  if ( lseek( fd, 16L, SEEK_SET ) == -1 ) {
    err_sys( "lseek error when testing relace" );
  }
  strcpy( buf, "HIJKLMN\n" );
  /* replace third row with above text */
  if ( write( fd, buf, 8 ) != 8 ) {
    err_sys( "write error while replacing" );
  }

  /* check the final text contents by reading all of it */
  /* rewind fd */
  if ( lseek( fd, 0L, SEEK_SET ) == -1 ) {
    err_sys( "lseek error while rewinding" );
  }
  if ( (n = read( fd, buf, 64 )) < 0 ) {
    err_sys( "read error while testing final text" );
  }
  if ( write( STDOUT_FILENO, buf, n ) != n ) {
    err_sys( "write error while testing final text" );
  }
  close( fd );
  return 0;
}
