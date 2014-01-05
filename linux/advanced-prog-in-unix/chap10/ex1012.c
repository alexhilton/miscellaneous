/*
 * ex1012.c
 * Use fwrite to write a very large buffer, more than a hundred megebytes.
 * Set a alarm( 1 ) before doing the write.
 * Test result: we found that the fwrite is going all the time until it is done,
 * alarm() does not expire, or the signal SIGALRM didnot be generated. It almost
 * broke down your system by write so many data(512M). You should never try
 * this.
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../com/comhdr.h"

static void sig_alrm( int signo );

int main( int argc, char **argv ) {
  if ( signal( SIGALRM, sig_alrm ) == SIG_ERR ) {
    err_sys( "signal(SIGALRM) error" );
  }
  FILE *fp = fopen( *++argv, "w" );
  assert( fp != NULL );
  size_t size = 512 * 1024 * 1024; /* 512 M */
  char *buf = (char *) malloc( sizeof( char ) * size );
  assert( buf != NULL );
  memset( buf, 0xcc, size );
  /* set off the alarm( 1 ) */
  alarm( 1 );
  /* do the reading */
  fwrite( buf, sizeof( char ), size, fp );

  return 0;
}

static void sig_alrm( int signo ) {
  printf( "SIGALRM caught\n" );
}
