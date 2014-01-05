/*
 * eg0804.c
 * trick to avoid zombie, by calling fork twice.
 * I didn't really get the points, honestly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../com/comhdr.h"

int main( int argc, char **argv ) {
  pid_t pid;

  if ( (pid = fork()) < 0 ) {
    err_sys( "error on fork" );
  } else if ( pid == 0 ) {
    if ( (pid = fork()) < 0 ) {
      err_sys( "error on fork" );
    } else if ( pid > 0 ) {
      exit( 0 ); /* the Son is dead */
    }

    /* Actually, this is not second child, but grandchild of original process */
    /* we are in second; our parent becomes init as soon as our real parent
     * calls exit() in the statement above. Here's where we'd continue
     * executing, knowing that when we're done, init will reap our status.
     */
    sleep( 2 );
    printf( "second child, parent pid = %d\n", getppid() );
    exit( 0 );
  }

  if ( waitpid( pid, NULL, 0 ) != pid ) {
    err_sys( "waitpid error" );
  }
  
  /*
   * we're the parent (the original process); we continue executing, knowing
   * that we're not the parent of the second child.
   */
  return 0;
}
