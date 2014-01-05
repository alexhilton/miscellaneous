/*
 * groupadm.c
 *
 * Learn some tricks about group and password administration.
 */
#include <stdio.h>
#include <errno.h>
#include <grp.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
  int myid; /* my ID */
  int myeid; /* my effective ID */
  int gid; /* group ID */
  int egid; /* effective group ID */
  struct group *pwp;
  int i;

  myid = getuid();
  myeid = geteuid();
  gid = getgid();
  egid = getegid();

  printf( "My ID is %d\n", myid );
  printf( "My effective ID is %d\n", myeid );
  printf( "Group ID is %d", gid );
  printf( "Effective Group ID is %d\n", egid );

  /**
   * Get information about user and its password, through
   * function getpsent().
   * It seems that getpwent() function doesn't need to release
   * space.
   */
  errno = 0;
  while ( (pwp = getgrent()) != NULL ) {
    /* everything is OK */
    printf( "Here is the inforamtion of the first record in password\n"
	    " database\n" );
    printf( "User name: '%s'\n", pwp->gr_name );
    printf( "User password: '%s'\n", pwp->gr_passwd );
    printf( "User ID: %d\n", pwp->gr_gid );
    printf( "Members in group %s\n", pwp->gr_name );
    for ( i = 0; pwp->gr_mem[ i ] != NULL; i++ ) {
      printf( "\t'%s'\n", pwp->gr_mem[ i ] );
    }
    putchar( '\n' );
  }
  /* error occured or EOF reached */
  if ( errno != 0 ) {
    /* error occured */
    perror( "getgrent() failed" );
    return 1;
  } else {
    printf( "EOF reached\n" );
  }

  /**
   * user function getgruid() function to get password entry by
   * inputing its ID as arguments.
   */
  /* first we need to rewind file pointer to bof */
  setgrent();
  myid = getgid();
  pwp = getgrgid( myid );
  if ( pwp != NULL ) {
    printf( "User name is '%s'\n", pwp->gr_name );
    printf( "other infor has been omitted\n" );
  } else {
    if ( errno != 0 ) {
      perror( "No password entry found!" );
      return 0;
    }
  }

  /**
   * get password entry through function getgrnam(),
   * inputing argutment is user name.
   * then its password entry will be returned.
   */
  pwp = getgrnam( "root" );
  if ( pwp != NULL ) {
    printf( "group name is '%s'\n", pwp->gr_name );
    printf( "other infor omitted \n" );
  }

  endgrent(); /* close the password file */
  return 0;
}
