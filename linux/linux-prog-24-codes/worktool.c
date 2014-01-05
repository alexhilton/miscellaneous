/*
 * worktool.c
 *
 * A program which simulates workers and tools demonstrates how to
 * create, use, maintain and remove semaphore.
 * It will create four sub-processes: Paul, Alfred, Robert and Adam to
 * use  tools: three hammers, two screwdrivers and one chisel.
 * they (four sub-processes) will use tools and return them.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define N_SEC 3 /* run simulation for n seconds */

static int semid = 1; /* semaphore IPC ID */

/* worker list */
typedef struct Worker Worker;

struct Worker {
  char *name;
  pid_t PID;
};

Worker worker[] = {
  { "Paul", 0 },
  { "Alfred", 0 },
  { "Robert", 0 },
  { "Adam", 0 }
};

/* definition for semun semaphore union */
typedef union semun semun;
union semun {
  int val; /* used for SETALL only */
  struct semid_ds *buf; /* for IPC_STAT and IPC_SET */
  ushort *array; /* used for GETALL and SETALL */
};

/* tool list */
static char *tool[] = {
  "Hammer",
  "Screwdriver",
  "Chisel"
};

/*
 * In this case we just want to notify the control semaphore (#3).
 * The control semaphore prevents other processes from reporting
 * something to stdout until the present process is finished its 
 * reporting to stdout. this keeps the report serialized.
 */
static void notify_ctrl() {
  int z;
  static struct sembuf sops = { 3, 1, 0 };
  /* semop() wait for semaphore */
  z = semop( semid, &sops, 1 );
  if ( z == -1 ) { /* error occured */
    perror( "semop(notify ctrl)" );
    exit( EXIT_FAILURE );
  }
}

/*
 * this function randomly selects 1 to 3 tools that will be required.
 * When hammers or chisels are selected, only require one tool. For
 * Screwdrivers allow one or two screwdrivers to be required.
 */
static struct sembuf *identify_tool( int *n ) {
  int x, y, sem;
  /* if you don't use static, error occurs, array cannot be returned */
  static struct sembuf sops[ 3 ];

  /* determine the number of tools required */
  *n = rand() % 3 + 1; /* 1 ~ 3 */

  /* now uniquely define the tools needed */
  for ( x = 0; x < *n; x++ ) {
    do {
      sem = rand() % 3;
      for ( y = 0; y < x; y++ ) {
	if ( sops[y].sem_num == sem ) {
	  /* already used */
	  sem = -1;
	  break;
	}
      }
    } while ( sem == -1 );
    sops[ x ].sem_num = sem; /* tool required */
    if ( sem == 1 ) { /* allow up to 2 screwdrivers */
      sops[ x ].sem_op = rand() % 2 + 1;
    } else { /* all other tools, only one each */
      sops[ x ].sem_op = -1;
    }
    sops[ x ].sem_flg = 0;
  }

  /* the control semaphore */
  sops[ *n ].sem_num = 3; /* Sem #3 controls stdout */
  sops[ *n ].sem_op = -1; /* wait operattion */
  sops[ *n ].sem_flg = 0; /* no flag */

  return sops;
}

/* this function is used to report our tools & state */
void report_tool( int n, struct sembuf *sops, char *name, char flag ) {
  int x;
  int nt; /* number of tools */
  char *oper; /* operation */
  char buf[ 1024 ]; /* formatting buffer */

  if ( flag == 'W' ) {
    oper = "waiting for tools";
  } else if ( flag == 'X' ) {
    oper = "using tools";
  } else {
    oper = "returning tools";
  }

  sprintf( buf, "worker %s is %s\n", name, oper );

  /* only report the tools for the 'using' status report */
  if ( flag == 'X' ) {
    for ( x = 0; x < n; x++ ) {
      nt = abs( sops[ x ].sem_op );
      sprintf( buf+strlen(buf), " %d %s%s\n", nt, tool[ sops[x].sem_num ],
	       (nt == 1 ? "" : "s") );
    }
  }

  /* write all of our text lines atomically to standard output. */
  write( 1, buf, strlen( buf ) );
}

/*
 * this function is run by the child process to simulate one worker
 * needing and returning tools.
 */
static void tool_time( int workerx, time_t t0 ) {
  char *name = worker[ workerx ].name;
  pid_t pid = getpid();
  int x;
  time_t tn; /* current time */
  int ntools; /* number of tools required */
  struct sembuf *sops = NULL; /* tool list */

  /* start random number generator */
  srand( (unsigned) pid );

  /* loop for N_SEC seconds */
  while ( 1 ) {
    /* check for quitting time */
    time( &tn );
    if ( tn - t0 >= N_SEC ) {
      return; /* quitting */
    }

    /* identify the tools that we need */
    sops = identify_tool( &ntools );
    report_tool( ntools, sops, name, 'W' );

    /* 
     * wait fro tools to become available:
     * Note: ntools+1 including ctrl semaphore.
     */
    semop( semid, sops, ntools+1 );
    report_tool( ntools, sops, name, 'X' );
    notify_ctrl(); /* done with stdout */

    /* pretend to work */
    sleep( 1 );

    /*
     * turn wait sem_ops into notifies for the tools only (we don't use
     * the control semaphore here 
     */
    for ( x = 0; x < ntools; x++ ) {
      sops[ x ].sem_op = -sops[ x ].sem_op;
    }

    /* 
     * return the tools to the toolbox:
     * Notify operation.
     */
    report_tool( ntools, sops, name, 'R' );
    semop( semid, sops, ntools );
  }
}

/* main program */
int main( int argc, char *argv[] ) {
  int z; 
  int x;
  time_t t0; /* starting time */
  union semun arg; /* semctl() arg */

  /* initial counts of tools in toolbox */
  static ushort init_count[] = {
    3, /* Hammers */
    2, /* Screwdrivers */
    1, /* chisel */
    1 /* control semaphore */
  };
  ushort final_count[ 4 ]; /* final tool counts */
  int status; /* termination status of sub-process */
  pid_t sub_pid; /* child process  ID */

  /* get a private set of semaphore */
  semid = semget( IPC_PRIVATE, 4, 0600 );
  if ( semid == -1 ) { /* error occured */
    perror( "semget()" );
    return 1;
  }

  /* initialize the semaphore counts */
  arg.array = init_count;
  z = semctl( semid, 0, SETALL, arg );
  if ( z == -1 ) {
    perror( "semctl(SETALL)" );
    return 1;
  }

  /* record our starting time */
  time( &t0 );

  /* now create four worker processes */
  for ( x = 0; x < 4; x++ ) {
    fflush( stdout );
    fflush( stderr );

    if ( (sub_pid = fork()) == 0 ) {
      /* child process */
      tool_time(x, t0 );
      return 0;
    } else if ( sub_pid == (pid_t)(-1) ) {
      fprintf( stderr, "%s: fork(x=%d)\n", strerror( errno ), x );
      return 1;
    }
    worker[ x ].PID = sub_pid;
  }

  /* now wait for all processes to end */
  do {
    sub_pid = wait( &status );
    for ( x = 0; x < 4; x++ ) {
      if ( worker[ x ].PID == sub_pid ) {
	worker[ x ].PID = 0;
	break;
      }
    }

    /* see if they have terminated */
    for ( x = 0; x < 4; x++ ) {
      if ( worker[ x ].PID != 0 ) {
	break;
      }
    }
  } while ( x < 4 );

  printf( "all workers have quit.\n" );

  /* obtain all semaphore counts */
  arg.array = final_count;
  z = semctl( semid, 0, GETALL, arg );
  if ( z == -1 ) {
    perror( "semctl(GETALL)" );
    return 1;
  }

  /* check our tool counts */
  for ( x = 0; x < 3; x++ ) {
    if ( final_count[ x ] != init_count[ x ] ) {
      printf( "Now have %d %ss. Had initially %d.\n", final_count[ x ],
	      tool[ x ], init_count[ x ] );
    } else {
      printf( "all %d %ss are accounted for.\n", final_count[ x ],
	      tool[ x ] );
    }
  }

  printf( "simulation complete.\n" );

  /* remove the semaphore set */
  z = semctl( semid, 0, IPC_RMID, arg );
  if ( z == -1 ) {
    perror( "semctl(IPC_RMID)" );
    return 1;
  }

  return 0;
}
