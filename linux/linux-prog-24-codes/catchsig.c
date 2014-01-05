/*
 * catchsig.c
 *
 * a program demonstrate how to use signal set. catch and handle signal.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static int count = 0;

/*
 * local signal handler function is passed into sigaction structure
 * as signal handler.
 */
static void catch_sig( int signo ) {
  count++;
  /* write is system proveded IO function */
  write( 1, "CAUGHT SIGINT\n", 15 );
}

int main( int argc, char *argv[] ) {
  struct sigaction sa_old;
  struct sigaction sa_new;

  /* .sa_handler is function pointer to void (*f)( int ) */
  sa_new.sa_handler = catch_sig;
  /* clear the signal set */
  sigemptyset( &sa_new.sa_mask );
  sa_new.sa_flags = 0;
  sigaction( SIGINT, &sa_new, &sa_old );

  puts( "Started: " );
  do {
    sleep( 1 );
  } while ( count < 3 );
  puts( "Ended." );
  return 0;
}
