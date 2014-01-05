#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include "debug.h"

void mylog( const char *fmt, ... ) {
  FILE *fp;
  if ( (fp = fopen( "log.txt", "a+" )) == NULL ) {
    return;
  }
  time_t now = time( NULL );
  fprintf( fp, "%s %s", __FILE__, ctime( &now ) );
  va_list args;
  va_start( args, fmt );
  vfprintf( fp, fmt, args );
  va_end( args );
  fclose( fp );
}
