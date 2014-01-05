/**
 * eg0108.c
 * Use fork(), exec() and wait() to control processes
 * This program will emulate a simple shell, whose prompt is '%'. In this shell,
 * you can input some commands, and it will execute the command and display the
 * results.
 * Add signal process ability
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "../com/comhdr.h"

/* signal callback function */
static void sig_int( int sig );

#define MAXLINE 4096

int main( int argc, char **argv ) {
  char buf[ MAXLINE ];
  pid_t pid;
  int status;

  if ( signal( SIGINT, sig_int ) == SIG_ERR ) {
    fprintf( stderr, "signal error\n" );
    return 0;
  }

  printf( "%% " ); /* print prompt */

  while ( fgets( buf, MAXLINE, stdin ) != NULL ) {
    buf[ strlen( buf ) - 1 ] = '\0';

    if ( (pid = fork()) < 0 ) {
      fprintf( stderr, "fork_error\n" );
      return 0;
    } else if ( pid == 0 ) {
      /* child process is running */
      execlp( buf, buf, (char *) 0 );
      err_ret( "couldn't execute %s", buf );
      return 127;
    }

    /* parent process is running */
    if ( (pid = waitpid( pid, &status, 0 )) < 0 ) {
      fprintf( stderr, "waitpid error\n" );
      return 0;
    }

    printf( "%% " );
  }

  return 0;
}

static void sig_int( int sig ) {
  printf( "interrupt\n%% " );
}
