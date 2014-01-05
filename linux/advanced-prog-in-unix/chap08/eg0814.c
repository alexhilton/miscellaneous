/*
 * eg0814.c
 * time and execute all command-line arguments
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../com/comhdr.h"

static void pr_times( clock_t, struct tms *, struct tms * );
static void do_cmd( const char * );
static void pr_exit( int status );

int main( int argc, char **argv ) {
  setbuf( stdout, NULL );
  while ( --argc > 0 ) {
    do_cmd( *++argv );
  }

  return 0;
}

static void do_cmd( const char *cmd ) {
  int status;
  struct tms tstart, tend;
  clock_t start, end;

  printf( "\ncommand: '%s'\n", cmd );
  if ( (start = times( &tstart )) < 0 ) { 
    /* starting values */
    err_sys( "tms error" );
  }
  if ( (status = system( cmd )) < 0 ) {
    err_sys( "error on system(%s)", cmd );
  }
  if ( (end = times( &tend )) < 0 ) {
    /* ending values */
    err_sys( "tms error" );
  }
  pr_times( end-start, &tstart, &tend );
  pr_exit( status );
}

static void pr_times( clock_t elapsed, struct tms *start, struct tms *end ) {
  static long clktck = 0;
  if ( (clktck = sysconf( _SC_CLK_TCK )) < 0 ) { /* fetching clock ticks per second first time */
    err_sys( "error on sysconf _SC_CLK_TCK" );
  }
  printf( "real: %7.2f\n", elapsed / (double) clktck );
  printf( "user: %7.2f\n", (end->tms_utime - start->tms_utime) / (double) clktck );
  printf( "system: %7.2f\n", (end->tms_stime - start->tms_stime) / (double) clktck );
  printf( "child user: %7.2f\n", (end->tms_cutime - start->tms_cutime) / (double) clktck );
  printf( "child system: %7.2f\n", (end->tms_cstime - start->tms_cstime) / (double) clktck );
}

static void pr_exit( int status ) {
  if ( WIFEXITED( status ) ) {
    printf( "Normal exited with exit code %d\n", WEXITSTATUS( status ) );
  } else if ( WIFSIGNALED( status ) ) {
    printf( "Abnormal terminated by signal number %d%s\n",
	WTERMSIG( status ),
#ifdef WCOREDUMP
	WCOREDUMP( status ) ? "(core dumped)" : "" );
#else
	"" );
#endif
  } else if ( WIFSTOPPED( status ) ) {
    printf( "Abnormal stopped by signal number %d\n",
	WSTOPSIG( status ) );
  }
}
