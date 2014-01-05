/*
 * ex0416.c
 * Verify the limitation of Unix/Linux about depths of the directories.
 * We create a directory with long name  and then chdir into that
 * directory and create a long-name directory and enter that again, and so
 * forth.
 * Then we use some tools to retrieve the full path: getcwd, tar and cpio.
 * The result is that, when repeat more than 91 times, path exceeds the path
 * limit. i.e. if repeat 92 or more times, getcwd and pathconf will fail due to
 * long filename.
 * But, contrary to author's experiment, we can use tar to archive it.
 */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

const char *name = "with_great_power_comes_great_responsibility";

int main( int argc, char **argv ) {
  const int depth = atoi( *++argv ); /* repeat times */
  int i;
  for ( i = 0; i < depth; i++ ) {
    mkdir( name, 0777 );
    chdir( name );
  }
  char path[ 5000 ];
  size_t size = 5000;
  if ( getcwd( path, size ) == NULL ) {
    printf( "getcwd error: %s\n", strerror( errno ) );
  } else {
    printf( "current path, length is: %d, content is:\n%s\n", strlen( path ), path );
  }
  long path_max = pathconf( path, _PC_PATH_MAX );
  if ( path_max > 0 ) {
    printf( "path max is: %ld\n", path_max );
  } else {
    printf( "pathconf error: %s\n", strerror( errno ) );
  }

  return 0;
}
