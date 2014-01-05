/*
 * eg0704.c
 * print all the current resource limits.
 * ?? I wanna know the differences between rlimit and __SC_MAX.
 * 	1. rlimit is for each process, while __SC_CONF is for a system.
 */
#include <stdio.h>
#include <sys/resource.h>
#include "../com/comhdr.h"

#if defined( BSD ) || defined( MACOS )
#  include <sys/time.h>
#  define FMT "%10lld"
#else
#  define FMT "%10ld"
#endif

#define doit( resource ) pr_limits( #resource, resource )

static void pr_limits( char *name, int resource );

int main( int argc, char **argv ) {
#ifdef RLIMIT_AS
  doit( RLIMIT_AS );
#endif

  doit( RLIMIT_CORE );
  doit( RLIMIT_CPU );
  doit( RLIMIT_DATA );
  doit( RLIMIT_FSIZE );
#ifdef RLIMIT_LOCKS
  doit( RLIMIT_LOCKS );
#endif
#ifdef RLIMIT_MEMLOCK
  doit( RLIMIT_MEMLOCK );
#endif
#ifdef RLIMIT_MEMLOCK
  doit( RLIMIT_MEMLOCK );
#endif
  doit( RLIMIT_NOFILE );
#ifdef RLIMIT_NPROC
  doit( RLIMIT_NPROC );
#endif
#ifdef RLIMIT_RSS
  doit( RLIMIT_RSS );
#endif
#ifdef RLIMIT_SBSIZE
  doit( RLIMIT_SBSIZE );
#endif
  doit( RLIMIT_STACK );
#ifdef RLIMIT_VMEM
  doit( RLIMIT_VMEM );
#endif
  return 0;
}

static void pr_limits( char *name, int resource ) {
  struct rlimit limit;
  if ( getrlimit( resource, &limit ) < 0 ) {
    err_sys( "getrlimit error for %s", name );
  }
  printf( "%-14s", name );
  if ( limit.rlim_cur == RLIM_INFINITY ) {
    printf( "(infinite)" );
  } else {
    printf( FMT, limit.rlim_cur );
  }
  if ( limit.rlim_max == RLIM_INFINITY ) {
    printf( "(infinite)" );
  } else {
    printf( FMT, limit.rlim_max );
  }
  putchar( (int) '\n' );
}
