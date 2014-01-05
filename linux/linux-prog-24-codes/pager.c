/*
 * pager.c
 *
 * A program demonstrates how to use IPC message queue.
 * This is a simulation program of client-server of telephone call
 * module.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct msgbuf {
  long mtype;
  char mtext[ 1 ];
} msgbuf;

typedef struct Page Page;

struct Page {
  long mtype;
  char phone[ 20 ];
  char callbk[ 20 ];
};

typedef union Msg Msg;

union Msg {
  struct msgbuf generic;
  Page page;
};

static char *cmdopt_s = 0; /* generic message */
static key_t cmdopt_k = 0; /* IPC key */
static int cmdopt_p = 20; /* Priority level default value */
static int msqid = -1; /* message queue ID */

static void usage( char *cmd ) {
  char *cp = strrchr( cmd, '/' );

  if ( cp != NULL ) {
    cmd = cp + 1;
  }
  fprintf( stderr, "Server Usage: %s -s tty -k key\n\tto start server.\n\n",
	   cmd );
  printf( "Client Usage: %s -k key [-p priority] page#/callbk#...\n"
	  "\tto queue a page request\n\n", cmd );
  printf( "\t-s tty\t\tDefault /dev/tty/n"
	  "\t-k key\t\tIPC key for server\n"
	  "\t-p priority\tDefault priority=20\n"
	  "\t\t\t(range 1 to 100)\n" );
  puts( "\t%s -k 23456 -p5416-555-1212/416-555-5555x4687\n" );
}

/* create or access a message queue */
static int create_msq( key_t key, int perms ) {
  int msqid;
  if ( perms ) {
    perms |= IPC_CREAT | IPC_EXCL;
  }
  if ( (msqid = msgget( key, perms )) == -1 ) {
    perror( "msgget(key, perms)" );
    exit( EXIT_FAILURE );
  }

  return msqid;
}

/* remove a message queue */
static void rmmsg( int *pmsqid ) {
  if ( msgctl( *pmsqid, IPC_RMID, 0 ) == -1 ) {
    perror( "msgctl()" );
    *pmsqid = -1;
  }
}

/* queue a message */
static void send_msg( Msg *msg, int msgsize ) {
  int msize = msgsize - sizeof( long );
  int z;

  do {
    z = msgsnd( msqid, &msg->generic, msize, 0 );
  } while ( z == -1 && errno == EINTR );

  if ( z == -1 ) {
    perror( "msgsnd()" );
    exit( EXIT_FAILURE );
  }
}

/* recieve a message */
static void recv_msg( Msg *msg, long mtype ) {
  int msz = sizeof( *msg ) - sizeof( long );
  int z;

  do {
    z = msgrcv( msqid, &msg->generic, msz, mtype, 0 );
  } while ( z == -1 && errno == EINTR );

  if ( z < 0 ) {
    perror( "msgrcv()" );
    exit( EXIT_FAILURE );
  }
}

/* paging server */
static void server() {
  Msg req;

  while ( 1 ) {
    recv_msg( &req, -100L );
    if ( strcasecmp( req.page.phone, "shutdown" ) == 0 ) {
      break;
    }
    printf( "ATDT%s,,%s\n", req.page.phone, req.page.callbk );
    sleep( 2 );
  }
  rmmsg( &msqid ); 
}

/* client code */
static void client( int argc, char *argv[] ) {
  int i;
  char *cp;
  Msg req;

  req.page.mtype = cmdopt_p; /* priority */
  for ( i = optind; i < argc; i++ ) {
    while ( (cp = strchr( argv[i], 'x' )) != NULL
	    || (cp = strchr( argv[i], 'X' )) != NULL ) {
      *cp = '*'; /* Dial * instead 'x' */
    }
    /* slash sparates call from callback number */
    if ( (cp = strchr( argv[ i ], '/' )) != NULL ) {
      *cp = '\0';
      strncpy( req.page.phone, argv[i], sizeof( req.page.phone ) )
	[ sizeof( req.page.phone ) - 1 ] = '\0';
      strncpy( req.page.callbk, ++cp, sizeof( req.page.callbk ) ) 
	[ sizeof( req.page.callbk ) - 1 ] = '\0';
      send_msg( &req, sizeof( req.page ) );
    } else {
      printf( "No call back number given! (%s)\n", argv[ i ] );
    }
  }
}

/* paging program & main program */
int main( int argc, char *argv[] ) {
  int rc = 0; 
  int optch;
  const char optstring[] = "s:k:p:h";

  /* parse command line arguments */
  while ( (optch = getopt( argc, argv, optstring )) != EOF ) {
    switch ( optch ) {
    case 'h':
      usage( argv[ 0 ] );
      return 0;
    case 's':
      cmdopt_s = optarg;
      break;
    case 'k':
      cmdopt_k = (key_t) atoi( optarg );
      break;
    case 'p':
      cmdopt_p = atoi( optarg );
      if ( cmdopt_p < 1 ) {
	cmdopt_p = 1;
      } else if ( cmdopt_p > 100 ) {
	cmdopt_p = 100;
      }
      break;
    default:
      rc = 1;
    }
  }

  /* test for command line argument errors */
  if ( rc ) {
    exit( 1 ); /* bad options */
  } 
  if ( cmdopt_s && optind < argc ) {
    printf( "Server mode does not accept arguments.\n" );
    usage( argv[ 0 ] );
    exit( 1 );
  }

  if ( !cmdopt_k ) {
    printf( "Must supply IPC key in -k option\n" );
    usage( argv[ 0 ] );
    exit( 1 );
  }

  /* now perform server/client function */
  if ( cmdopt_s ) {
    msqid = create_msq( cmdopt_k, 0666 );
    server();
  } else {
    msqid = create_msq( cmdopt_k, 0 );
    client( argc, argv );
  }

  return 0;
}
