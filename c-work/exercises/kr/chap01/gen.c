#include <stdio.h>
#include <limits.h>

int main() {
  FILE *out = fopen( "input.dat", "a" );
  fprintf( out, "%d\n", INT_MIN );
  fprintf( out, "%d\n", INT_MAX );
  return 0;
}
