/*
 * useradm.c
 *
 * Learn some tricks about user, group and password administration.
 */
#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
  int myid; /* my ID */
  int myeid; /* my effective ID */
  int gid; /* group ID */
  int egid; /* effective group ID */
  struct passwd *pwp;

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
  /*
   * Here, structure pointer is returned value, thus you don't have
   * to worry about it. the function is reponsible for allocating
   * spaces for structure pointer. and freeing it after using is your
   * responsibility.
   */
  pwp = getpwent(); /* get password entry */
  while ( (pwp = getpwent()) != NULL ) {
    /* everything is OK */
    printf( "Here is the inforamtion of the first record in password\n"
	    " database\n" );
    printf( "User name: '%s'\n", pwp->pw_name );
    printf( "User password: '%s'\n", pwp->pw_passwd );
    printf( "User ID: %d\n", pwp->pw_uid );
    printf( "Group ID: %d\n", pwp->pw_gid );
    printf( "Comment field: '%s'\n", pwp->pw_gecos );
    printf( "Home dir: '%s'\n", pwp->pw_dir );
    printf( "Shell: '%s'\n\n", pwp->pw_shell );
  }
  /* error occured or EOF reached */
  if ( errno != 0 ) {
    /* error occured */
    perror( "getpwent() failed" );
    return 1;
  } else {
    printf( "EOF reached\n" );
  }

  /**
   * user function getpwuid() function to get password entry by
   * inputing its ID as arguments.
   */
  /* first we need to rewind file pointer to bof */
  setpwent();
  myid = getuid();
  pwp = getpwuid( myid );
  if ( pwp != NULL ) {
    printf( "User name is '%s'\n", pwp->pw_name );
    printf( "other infor has been omitted\n" );
  } else {
    if ( errno != 0 ) {
      perror( "No password entry found!" );
      return 0;
    }
  }

  /**
   * get password entry through function getpwnam(),
   * inputing argutment is user name.
   * then its password entry will be returned.
   */
  pwp = getpwnam( "root" );
  if ( pwp != NULL ) {
    printf( "User shell is '%s'\n", pwp->pw_shell );
    printf( "other infor omitted \n" );
  }

  endpwent(); /* close the password file */
  return 0;
}
