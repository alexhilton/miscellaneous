/**
 * eg0407.c
 * Use six directory utility functions to traverse a file hierarchy. The goal is
 * to print the count for each types of file.
 * Note: 
 * When passing a directory to this program, the count of directory should 
 * always be greater than one, or the min value of ndir is 1. 
 * This is because that myftw will follow a directory, begining from the
 * directory you passed to it, so the ndir is 1 when processing the path you
 * passed to it.
 * When passing a non-directory to this program, ndir should be 0, while others
 * might be 1 or 0 depending the file type you passed to it.
 */
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include "../com/comhdr.h"

/* fucntion type that's called for each filename */
/* Note: the general way is to define a function pointer */
typedef int Myfunc( const char *filepath, const struct stat *statbuf, int type );

/* used to callback */
static Myfunc myfunc;
static int myftw( char *filename, Myfunc *func );
static int dopath( Myfunc *func );
static char *path_alloc( int *size );

/*
 * count for type: regular, directory, block special, character special, fifo,
 * symbolink, socket and total.
 */
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main( int argc, char **argv ) {
  int ret;
  if ( argc != 2 ) {
    err_quit( "usage: ftw [pathname]" );
  }

  nreg = ndir = nblk = nchr = nfifo = nslink = nsock = 0L;
  /* do it all */
  ret = myftw( *++argv, myfunc );

  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if ( ntot == 0 ) {
    ntot = 1; /* avoid divide by 0, print 0 for all counts */
  }
  printf( "regular files       = %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot );
  printf( "directories         = %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot );
  printf( "block special       = %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot );
  printf( "character special   = %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot );
  printf( "fifo                = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot );
  printf( "symbolic link       = %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot );
  printf( "socket              = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot );

  return ret;
}

/*
 * Descend through the hierarchy, starting at "pathname". The caller's func() is
 * called for every file.
 */
#define FTW_F 0x01 /* file other than directory */
#define FTW_D 0x02 /* directory */
#define FTW_DNR 0x03 /* directory that can't be read */
#define FTW_NS 0x04 /* file that we cann't stat */

static char *fullpath; /* contain full pathname for every file */

/* we return whatever func returns */
static int myftw( char *pathname, Myfunc *func ) {
  /* malloc's for PATH_MAX+1 bytes */
  int len;
  fullpath = path_alloc( &len );
  /* initialize full path */
  strncpy( fullpath, pathname, len );
  return dopath( func );
}

/*
 * Descend through the hierarchy, starting at "fullpath".
 * If "fullpath" is anything other than a directory, we lstat() it, call func(),
 * and return. For a directory, we call ourself recursively for each name in the
 * directory.
 */
/* we return whatever func returns */
static int dopath( Myfunc *func ) {
  struct stat statbuf;
  struct dirent *dirp;
  DIR *dp;
  int ret;
  char *ptr;

  if ( lstat( fullpath, &statbuf ) < 0 ) {
    /* stat error */
    return func( fullpath, &statbuf, FTW_NS );
  }

  if ( S_ISDIR( statbuf.st_mode ) == 0 ) {
    /* not a directory */
    return func( fullpath, &statbuf, FTW_F );
  }

  /*
   * It is a directory now, First call func() for the directory, then process
   * each filename in the directory.
   */
  if ( (ret = func( fullpath, &statbuf, FTW_D )) != 0 ) {
    return ret;
  }

  /* make ptr point to end of fullpath */
  ptr = fullpath + strlen( fullpath );
  *ptr++ = '/';
  *ptr = '\0';

  /*
   * First function of directory manipulation: opendir -- to open a directory,
   * returning pointer to DIR
   */
  if ( (dp = opendir( fullpath )) == NULL ) {
    /* cannot open directory, not even to read */
    return func( fullpath, &statbuf, FTW_DNR );
  }

  /* 
   * Read each entry in directory, until NULL returned
   * Second function: readdir -- read each directory entry, until NULL returned 
   */
  while ( (dirp = readdir( dp )) != NULL ) {
    /* skip self '.' and parent '..', otherwise infinite loop occur */
    if ( strcmp( dirp->d_name, "." ) == 0
	|| strcmp( dirp->d_name, ".." ) == 0 ) {
      continue;
    }
    /* 
     * d_name is a relative path, it is only the filename in the directory.
     * To apply func on to filename, we need to construct its full path name.
     */
    strcpy( ptr, dirp->d_name );
    if ( (ret = dopath( func )) != 0 ) { /* recursive */
      break; /* time to leave */
    }
  }

  /* erase everything from slash onwards */
  /* this is peculiar enough, Doesn't this cause Segmentation fault? */
  ptr[ -1 ] = '\0';
  /* third one, close diectory, taking a pointer to DIR, 0 on success, -1 on
   * error */
  if ( closedir( dp ) < 0 ) {
    err_ret( "cannot close directory %s", fullpath );
  }

  return ret;
}

static int myfunc( const char *pathname, const struct stat *statptr, int type ) {
  switch ( type ) {
  case FTW_F:
    if ( S_ISREG( statptr->st_mode ) ) {
      nreg++;
    } else if ( S_ISBLK( statptr->st_mode ) ) {
      nblk++;
    } else if ( S_ISCHR( statptr->st_mode ) ) {
      nchr++;
    } else if ( S_ISFIFO( statptr->st_mode ) ) {
      nfifo++;
    } else if ( S_ISLNK( statptr->st_mode ) ) {
      nslink++;
    } else if ( S_ISSOCK( statptr->st_mode ) ) {
      nsock++;
    } else if ( S_ISDIR( statptr->st_mode ) ) {
      /* directories should have type = FTW_D */
      err_dump( "for S_ISDIR for %s", pathname );
    }
    break;
  case FTW_D:
    ndir++;
    break;
  case FTW_DNR:
    err_ret( "can't read directory %s", pathname );
    break;
  case FTW_NS:
    err_ret( "stat error for %s", pathname );
    break;
  default:
    err_dump( "unknown type %d for pathname %s", type, pathname );
  }
  return 0;
}

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

/*
 * if PATH_MAX is indeterminate, we have to guess one. We're not guaranteed this
 * is adequate.
 */
#define PATH_MAX_GUESS 1024
#define SUSV3 200112L

static long posix_version   = 0;
static char *path_alloc( int *size );

static char *path_alloc( int *size ) {
  char *ptr;
  int s;

  if ( posix_version == 0 ) {
    posix_version = sysconf( _SC_VERSION );
  }
  printf( "posix_version = %ld\n", posix_version );

  if ( pathmax == 0 ) {
    errno = 0;
    if ( (pathmax = pathconf( "/", _PC_PATH_MAX )) < 0 ) {
      if ( errno == 0 ) {
	/* it is indeterminate we have to guess one */
	pathmax = PATH_MAX_GUESS;
      } else {
	err_sys( "pathconf error for _PC_PATH_MAX" );
      }
    } else {
      /* add one, since it is relative to root */
      pathmax++;
    }
  }

  /*
   * Standards prior to SUSv3 is unclear as to whether or not path included a
   * null byte at the end of path. We have to test it and add one more in case.
   */
  if ( posix_version < SUSV3 ) {
    s = pathmax + 1;
  } else {
    s = pathmax;
  }

  if ( (ptr = malloc( s )) == NULL ) {
    err_sys( "out of memory" );
  }
  if ( ptr != NULL ) {
    *size = s;
  }

  return ptr;
}
