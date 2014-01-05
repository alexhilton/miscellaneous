/*
 * eg1007.c
 * An bit-based, bare bone implementation of sigset* operations
 * This implementation assumes that the number of singals is less than number of
 * bits of an integer -- 32, every bit stands for a signal. sigaddset turns on a
 * bit. sigdelset turns off a bit
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include "../com/comhdr.h"

/* verify whether signo is a valid signal */
/* <signal.h> usually define NSIG to include signal number 0 */
#define SIGBAD( signo ) ( (signo) <= 0 || (signo) >= NSIG )

/* add a signal to set, just turn on the bit: the signo'th bit */
int sigaddset( sigset_t *set, int signo ) {
  /* checking for error: invalid signo, for example */
  if ( SIGBAD( signo ) ) {
    errno = EINVAL;
    return -1;
  }

  /*
   * generally there is no signal 0, so we should substract 1 from signo to get
   * the designated bit
   */
  *set |= (1 << (signo - 1)); /* turn the bit on */
  return 0;
}

/* del a signal from set, just turn off that bit */
int sigdelset( sigset_t *set, int signo ) {
  if ( SIGBAD( signo ) ) {
    errno = EINVAL;
    return -1;
  }

  *set &= ~(1 << (signo - 1));
  return 0;
}

int sigismember( const sigset_t *set, int signo ) {
  if ( SIGBAD( signo ) ) {
    errno = EINVAL;
    return -1;
  }
  /* return *set & (1 << (signo - 1)); */
  return (*set & (1 << (signo - 1))) != 0;
}

int main( int argc, char **argv ) {
  /* test driver goes here */
  return 0;
}
