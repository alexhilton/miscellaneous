/*
 * ex0802.c
 * Let see what will happen if a sub-function call vfork.
 * From our verification, nothing strange happened!
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

static void call_fork();
static void after_fork();

int main( int argc, char **argv ) {
  call_fork();
  after_fork();
  return 0;
}

static void call_fork() {
  pid_t pid;
  if ( (pid = vfork()) < 0 ) {
    err_sys( "error on vfork()" );
  }
}

static void after_fork() {
  int i;
  char buf[ 16 ];
  for ( i = 0; i < 16; i++ ) {
    buf[ i ] = i;
  }
  buf[ 16 ] = '\0';
}
