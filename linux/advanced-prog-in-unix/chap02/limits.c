/**
 * limits.c
 * test the return value of sysconf.
 * All limits defined in <limits.h> are compile-time limits and can be retrieved
 * immediately through including the header <limits.h>.
 * Other limits can be retrieved by sysconf, pathconf and fpathconf.
 * 	sysconf returns limits about a system
 * 	pathconf and fpathconf return limits about a file(directory) or a kind of
 * 	file(directory).
 * All three of them returning -1 and setting errno as EINVAL on error.
 * Returning -1 but do not set errno if there is no such limit on this system.
 */
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  if ( argc != 2 ) {
    fprintf( stderr, "Usage: limits path\n" );
    return 0;
  }
  printf( "==========through sysconf==========\n" );
  printf( "CHILD_MAX= %ld\n", sysconf( _SC_CHILD_MAX ) );
  printf( "OPEN_MAX= %ld\n", sysconf( _SC_OPEN_MAX ) );
  printf( "CLK_TCK= %ld\n", sysconf( _SC_CLK_TCK ) );
  printf( "HOST_NAME_MAX = %ld\n", sysconf( _SC_HOST_NAME_MAX ) );
  printf( "IOV_MAX= %ld\n", sysconf( _SC_IOV_MAX ) );
  printf( "LINE_MAX= %ld\n", sysconf( _SC_LINE_MAX ) );
  printf( "PAGE_SIZE= %ld\n", sysconf( _SC_PAGE_SIZE ) );
  printf( "========================compile time limits, defined in <limits.h>================\n" );
  printf( "CHAR_BIT= %d\n", CHAR_BIT );
  printf( "CHAR_MAX= %d\n", CHAR_MAX );
  printf( "SHRT_MAX= %d\n", SHRT_MAX );
  printf( "INT_MAX= %d\n", INT_MAX );
  printf( "LONG_MAX= %ld\n", LONG_MAX );
  printf( "CHAR_MIN= %d\n", CHAR_MIN );
  printf( "SHRT_MIN= %d\n", SHRT_MIN );
  printf( "INT_MIN= %d\n", INT_MIN );
  printf( "LONG_MIN= %ld\n", LONG_MIN );
  printf( "##not part of limits, in <stdio.h> BUFSIZ= %d\n", BUFSIZ );
  printf( "==========through sysconf==========\n" );
  printf( "LINK_MAX= %ld\n", pathconf( *++argv, _PC_LINK_MAX ) );
  printf( "MAX_CANON= %ld\n", pathconf( *argv, _PC_MAX_CANON ) );
  printf( "MAX_INPUT= %ld\n", pathconf( *argv, _PC_MAX_INPUT ) );
  printf( "NAME_MAX= %ld\n", pathconf( *argv, _PC_NAME_MAX ) );
  printf( "Path_max= %ld\n", pathconf( *argv, _PC_PATH_MAX ) );
  printf( "PIPE_BUF= %ld\n", pathconf( *argv, _PC_PIPE_BUF ) );
  printf( "SYMLINK_MAX= %ld\n", pathconf( *argv, _PC_SYMLINK_MAX ) );
  return 0;
}
