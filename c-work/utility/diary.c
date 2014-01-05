/*
 * diary.c
 * this program creates a new diary with dd-mm-yyyy.txt as filename
 * and insert date and time in the first line of file.
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const char months[][20] = { 
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
  "Aug", "Sep", "Oct", "Nov", "Dec"
};

int diary();
int help();

int main( int argc, char **argv ) {
  if ( argc == 2 ) {
    if ( strcasecmp( argv[ 1 ], "--help" ) == 0 ) {
      help();
    }
  }
  diary();
  return 0;
}

/*
 * function: diary
 * param:
 * return:
 * description:
 */
int diary() {
  time_t now = time( 0 );
  struct tm *today;
  today = gmtime( &now );
  char fname[ 256 ];
  FILE *file;
  sprintf( fname, "%s-%2d-%4d.txt", months[ today->tm_mon ], today->tm_mday, today->tm_year+1900 );
  if( (file = fopen( fname, "w" )) == NULL ) {
    perror( fname );
    return -1;
  }
  fprintf( file, "%s", ctime( &now ) );
  char buf[ 1024 ];
  printf( "entering your diary...\n" );
  while ( 1 ) {
    printf( ">" );
    if ( fgets( buf, sizeof( buf ), stdin ) == NULL ) {
      break;
    }
    fputs( buf, file );
  }
  fclose( file );
  printf( "\n" );
  return 0;
}


int help() {
  fprintf( stdout, "Entering what you want to write after prompt '>'\n" );
  fprintf( stdout, "Press Ctrl-D after prompt '>', if you finish your writing\n" );
  return 0;
}
