/*
 * alarm.c
 *
 * learn to handler more signal. and how to send an alarm.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void catch_sig( int signo ) {
  if ( signo == SIGINT ) {
    alarm( 0 ); /* cancel timer */
    write( 1, "CAUGTH SIGINT!\n", 15 );
  } else if ( signo  == SIGALRM ) {
    write( 1, "CAUGHT SIGALRM.\n", 16 );
  }
}

int main( int argc, char *argv[] ) {
  sigset_t sigs;
  struct sigaction sa_old;
  struct sigaction sa_new;

  sa_new.sa_handler = catch_sig;
  sigemptyset( &sa_new.sa_mask );
  sigaddset( &sa_new.sa_mask, SIGALRM );
  sigaddset( &sa_new.sa_mask, SIGINT );
  sa_new.sa_flags = 0;

  sigaction( SIGINT, &sa_new, &sa_old );
  sigaction( SIGALRM, &sa_new, 0 );

  sigfillset( &sigs );
  sigdelset( &sigs, SIGINT );
  sigdelset( &sigs, SIGALRM );

  puts( "You have 3 seconds to SIGINT( Cntl+c )" );

  alarm( 3 );
  sigsuspend( &sigs );
  puts( "Done." );
  return 0;
}
