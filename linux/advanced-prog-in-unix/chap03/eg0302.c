/**
 * eg0302.c
 * Create a file with a hole in it.
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../com/comhdr.h"

char buf1[] = "abcdefghij"; /* ten chars */
char buf2[] = "ABCDEFGHIJ";

int main( int argc, char **argv ) {
  int fd;

  if ( (fd = creat( "file.hole", FILE_MODE )) < 0 ) {
    err_sys( "create error" );
  }

  if ( write( fd, buf1, 10 ) != 10 ) {
    /* there are ten chars */
    err_sys( "buf1 write error" );
  }
  /* offset now = 10 */
  if ( lseek( fd, 40, SEEK_SET ) == -1 ) {
    err_sys( "lseek error" );
  }
  /* offset is 40, now */
  if ( write( fd, buf2, 10 ) != 10 ) {
    err_sys( "buf2 write error" );
  }
  /* offset now = 50 */
  return 0;
}
