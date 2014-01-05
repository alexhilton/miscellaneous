/**
 * join_thread.c
 * Create three sub-threads, one joins into main thread, another joins into first sub-thread.
 */
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static pthread_t t1, t2, t3;

static void *run1( void *arg ) {
    printf( "this is thread  1\n" );

    pthread_join( t2, NULL );

    printf( "thread 1 exits\n" );

    pthread_exit( NULL );
}

static void *run2( void *arg ) {
    printf( "this is thread 2\n" );

    printf( "Freedom is nothing but a chance to be better\n" );

    printf( "thread 2 exits\n" );

    pthread_exit( NULL );
}

static void *run3( void *arg ) {
    printf( "this is thread 3\n" );

    printf( "Debugging involves backwards reasoning, like solving murder mysteries.\n" );

    printf( "thread 3 exits\n" );

    pthread_exit( NULL );
}

int main( int argc, char *argv[] ) {
    printf( "create threads\n" );
    pthread_create( &t1, NULL, run1, NULL );
    pthread_create( &t2, NULL, run2, NULL );
    pthread_create( &t3, NULL, run3, NULL );

    pthread_join( t3, NULL );

    sleep( 2 );
    printf( "main thread exit\n" );
    return 0;
}
