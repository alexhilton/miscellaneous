/**
 * first_sight.c
 * A simple program demonstrates multi-threading with pthraed(POSIX thread).
 * This program prints a message in a thread created by main thread.
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void *run( void *arg );

int main( int argc, char *argv[] ) {
    pthread_t id;

    printf( "Create a new thread\n" );`
    pthread_create( &id, NULL, run, NULL );
    printf( "new thread %d created\n", id );

    /* 
     * CAUTION: main thread must wait for sub-thread executing, or the process is terminated
     * before sub-thread gets chance to run.
     */
    sleep( 3 );
    return 0;
}

static void *run( void *arg ) {
    printf( "Freedom is nothing but a chance to be better\n" );
    sleep( 1 );
    printf( "Debugging involves backwards reasoning, like solving murder mysteries.\n"
            "Something impossible occurred, and the only solid information is that it "
            "really did occur.\n" );

    pthread_exit( (void *) 2 );
}
