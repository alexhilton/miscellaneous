#include <sys/wait.h>
#include <stdio.h>

int main( int argc, char **argv ) {
  int status;
  wait( &status );
  perror( "error on wait" );
  return 0;
}
