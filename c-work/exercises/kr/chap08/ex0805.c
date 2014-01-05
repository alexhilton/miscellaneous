/**
 * ex0805.c
 * print file size with traverse directory.
 * learn how to write system-dependent program in a system-independent way.
 * To do that, you have to define your own structures, you own functions and
 * make different implementations depending on which platform you are in.
 * Then when you port your program to other OS, the modifications are minimized.
 * Only thing you have to change is the implementation.
 * print more info about a file
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define __USE_BSD "use bsd"
#include <sys/dir.h>
#include <sys/stat.h>
#define DIRSIZE 14

#define MAX_PATH 1024 /* max length of a path */
#define MAX_NAME 255 /* longest filename */
typedef struct { /* portable directory entry */
  int ino; /* inode number */
  char name[ MAX_NAME + 1 ]; /* name + '\0' */
} Dirent;

typedef struct { /* portable directory */
  int fd; /* file descriptor */
  Dirent d;
} Dir;

/*
 * open a directory named by filename, return a pointer to portable structure
 * describing the directory
 */
Dir *opendirect( char *filename );
/*
 * read each directoy entry from the directroy pointed by dir
 */
Dirent *readdirect( Dir *dir );
/* close the dir opened by opendirect */
void closedirect( Dir *dir );
/* check each directory entry, apply fsize to each entry */
void dirwalk( char *filename, void (*fcn)(char *filename) );
/* print file size */
void fsize( char *filename );

/* print file size */
int main( int argc, char **argv ) {
  if ( argc == 1 ) { /* default: current directory */
    fsize( "." );
  } else {
    while ( --argc > 0 ) {
      fsize( *++argv );
    }
  }
  return 0;
}

/* fsize: print size of file */
void fsize( char *filename ) {
  struct stat stbuf; 

  if ( stat( filename, &stbuf ) == -1 ) {
    fprintf( stderr, "fsize: cannot access %s\n", filename );
    return;
  }
  /* this takes time to understand */
  if ( (stbuf.st_mode & S_IFMT) == S_IFDIR ) {
    /* apply dirwalk to a directory */
    dirwalk( filename, fsize );
  }
  /* if it is a regular file, we print its size and name then leave */
  printf( "%8ld %s last changed on %s", stbuf.st_size, filename, ctime( &stbuf.st_ctime ) );
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk( char *dir, void (*fcn)(char *filename) ) {
  char name[ MAX_PATH ];
  Dirent *dp;
  Dir *dfd;
  if ( (dfd = opendirect( dir )) == NULL ) {
    fprintf( stderr, "dirwalk: can't open %s\n", dir );
    return;
  }
  while ( (dp = readdirect( dfd )) != NULL ) {
    if ( strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0 ) {
      continue; /* skip self and parent directory */
    }
    /* +2, one for '/' the other for '\0' */
    if ( strlen(dir)+strlen(dp->name)+2 > sizeof( name ) ) {
      fprintf( stderr, "dirwalk: name %s/%s too long\n", dir, dp->name );
    } else {
      sprintf( name, "%s/%s", dir, dp->name );
      /* 
       * for each directory entry, we apply fsize to it. If it is a directory
       * again, fsize can detect that and apply dirwalk recursively to it.
       */
      (*fcn)( name );
    }
  } 
  closedirect( dfd );
}

/* opendirect: open a directory for readdirect calls */
Dir *opendirect( char *dirname ) {
  int fd;
  struct stat stbuf;
  Dir *dp;

  /* through this if block, much work are done */
  if ( (fd = open(dirname, O_RDONLY, 0)) == -1 || 
       fstat(fd, &stbuf) == -1 ||
       (stbuf.st_mode & S_IFMT) != S_IFDIR ||
       (dp = (Dir *) malloc( sizeof( *dp ) )) == NULL ) {
    return NULL;
  }
  dp->fd = fd;
  return dp;
}

/* closedirect: close directory opened by opendirect */
void closedirect( Dir *dp ) {
  if ( dp != NULL ) {
    close( dp->fd );
    free( dp );
  }
}

/* readdirect: read directory entries in sequence */
Dirent *readdirect( Dir *dp ) {
  struct direct dirbuf; /* local directory structure */
  static Dirent d; /* portable structure */

  /* read each directory entry and return it to caller */

  /* 
   * d is declared as static, this can save some space and spare you from
   * freeing memory if you use a pointer.
   * An alternative is Dirent *d, but you have to allocate memory to use it and
   * free memory after using it.
   */
  while ( read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf) ) {
    /* if a file's inode is zero, indicate that it is free, not in use */
    if ( dirbuf.d_ino == 0 ) { /* slot not in use */
      continue;
    }
    d.ino = dirbuf.d_ino;
    strncpy( d.name, dirbuf.d_name, DIRSIZE );
    d.name[ DIRSIZE ] = '\0'; /* ensure termination */
    return &d;
  }

  return NULL;
}
