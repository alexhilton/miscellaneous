/*
 * testsigsus.c
 *
 * a simple program to test the return value of sigsuspend() function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static void catch_sig( int signo ) {
  write( 1, "CAUGHT SIGNAL!\n", 15 );
}

int main( int argc, char *argv[] ) {
  int z; /* return code of sigsuspend() */
  sigset_t sigs;
  struct sigaction sa_new;
  sa_new.sa_handler = catch_sig;

  sigemptyset( &sa_new.sa_mask );
  sa_new.sa_flags = 0;
  sigaction( SIGALRM, &sa_new, 0 );

  sigfillset( &sigs );
  sigdelset( &sigs, SIGINT );
  sigdelset( &sigs, SIGALRM );

  alarm( 3 );

  errno = 0; 
  z = sigsuspend( &sigs );

  printf( "z = %d, errno = %d (%s)\n", z, errno, strerror( errno ) );

  return 0;
}
