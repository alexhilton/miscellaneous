/**
 * ex0303.c
 * Three operations:
 *   fd1 = open( pathname, oflags );
 *   fd2 = dup( fd1 );
 *   fd3 = open( pathname, oflags );
 * We are gonna explore the differences between fd1, fd2 and fd3.
 * And we are gonna see who will be affected when modifying fd flags of fd1, and
 * modifying file flags of fd1.
 * From the result we can see that: changing fd flag of fd1 affect fd1 itself
 * only. While changing fl flag of fd1,  fd1 and fd2's fl flag are affected.
 * It is said that each call of open will open a new file table entry. So, 
 * in some sence, fd3 is different from fd1, and they are not related to each other.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  int oflags = O_RDWR; /* read and write */
  char *pathname = "input.dat";
  int fd1, fd2, fd3;
  if ( (fd1 = open( pathname, oflags, 0 )) < 0 ) {
    err_sys( "error opening %s fd1", pathname );
  }
  /* set fd1's fd flag */
  fcntl( fd1, F_SETFD, FD_CLOEXEC );

  /* now dup and  open path name as fd3 */
  if ( (fd2 = dup( fd1 )) < 0 ) {
    err_sys( "error on dup fd1" );
  }
  if ( (fd3 = open( pathname, oflags )) < 0 ) {
    err_sys( "error on opening %s as fd3", pathname );
  }

  int fdflag, flflag;
  printf( "================ initial status of fd and fl ===================\n" );
  if ( (fdflag = fcntl( fd1, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd1" );
  }
  if ( (flflag = fcntl( fd1, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd1" );
  }
  printf( "fd1: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  if ( (fdflag = fcntl( fd2, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd2" );
  }
  if ( (flflag = fcntl( fd2, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd2" );
  }
  printf( "fd2: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  if ( (fdflag = fcntl( fd3, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd3" );
  }
  if ( (flflag = fcntl( fd3, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd3" );
  }
  printf( "fd3: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  /* now change fd flags and then fl flags of fd1 */
  printf( "================ Change fd flag of fd1 ===================\n" );
  if ( fcntl( fd1, F_SETFD, 0 ) < 0 ) {
    err_sys( "error on setting fd flag of fd1" );
  }
  /* now review the properties and see whehter there is some change */
  if ( (fdflag = fcntl( fd1, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd1" );
  }
  if ( (flflag = fcntl( fd1, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd1" );
  }
  printf( "fd1: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  if ( (fdflag = fcntl( fd2, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd2" );
  }
  if ( (flflag = fcntl( fd2, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd2" );
  }
  printf( "fd2: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  if ( (fdflag = fcntl( fd3, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd3" );
  }
  if ( (flflag = fcntl( fd3, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd3" );
  }
  printf( "fd3: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  /* now change fl flag of fd1 */
  printf( "================ Change fl flag of fd1 ===================\n" );
  flflag = (O_NONBLOCK | O_SYNC | O_TRUNC);
  if ( fcntl( fd1, F_SETFL, flflag ) < 0 ) {
    err_sys( "error on setting fl flag of fd1" );
  }
  /* now review the properties and see whether there is some change */
  if ( (fdflag = fcntl( fd1, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd1" );
  }
  if ( (flflag = fcntl( fd1, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd1" );
  }
  printf( "fd1: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  if ( (fdflag = fcntl( fd2, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd2" );
  }
  if ( (flflag = fcntl( fd2, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd2" );
  }
  printf( "fd2: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  if ( (fdflag = fcntl( fd3, F_GETFD, 0 )) < 0 ) {
    err_sys( "error on fcntl while geting fd flags for fd3" );
  }
  if ( (flflag = fcntl( fd3, F_GETFL, 0 )) < 0 ) {
    err_sys( "error on fcntl while getting file flags for fd3" );
  }
  printf( "fd3: fd flag is 0x%x, fl flag is 0x%x\n", fdflag, flflag );

  close( fd1 );
  close( fd2 );
  close( fd3 );
  return 0;
}
