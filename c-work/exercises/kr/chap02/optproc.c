#include <stdio.h>
#include <unistd.h>

int main( int argc, char *argv[ ] ) {
  char optstring[] = "abcd";
  char ch;
  while ( (ch = getopt( argc, argv, optstring )) != EOF ) {
    switch ( ch ) {
    case 'a':
      printf( "option a caught\n" );
      break;
    case 'b':
      printf( "option b caugth\n" );
      break;
    case 'c':
      printf( "option c caught\n" );
      break;
    case 'd':
      printf( "option d caught\n" );
      break;
    default:
      printf( "Unkown options\n" );
      break;
    }
  }
  return 0;
}
