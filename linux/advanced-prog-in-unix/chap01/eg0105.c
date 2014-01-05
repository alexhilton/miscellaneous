/**
 * eg0105.c
 * Use fork(), exec() and wait() to control processes
 * This program will emulate a simple shell, whose prompt is '%'. In this shell,
 * you can input some commands, and it will execute the command and display the
 * results.
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 4096

int main( int argc, char **argv ) {
  char buf[ MAXLINE ];
  pid_t pid;
  int status;

  printf( "%% " ); /* print prompt */

  while ( fgets( buf, MAXLINE, stdin ) != NULL ) {
    buf[ strlen( buf ) - 1 ] = '\0';

    if ( (pid = fork()) < 0 ) {
      fprintf( stderr, "fork_error\n" );
      return 0;
    } else if ( pid == 0 ) {
      /* child process is running */
      execlp( buf, buf, (char *) 0 );
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
