/*
 * atm_async.c
 * Simulate an ATM terminal, transfering random amount of money from each
 * account to a random account.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define ACCOUNT_SIZE 10
#define INIT_AMOUNT 1000

static int accounts[ ACCOUNT_SIZE ];

static int sum( void ) {
  int s = 0;
  int i;
  for ( i = 0; i < ACCOUNT_SIZE; i++ ) {
    s += accounts[ i ];
  }
  return s;
}

static void *transfer( void *acc_from ) {
  int from = *(int *) acc_from;
  while ( 1 ) {
    int to = random() % ACCOUNT_SIZE;
    int amount = random() % INIT_AMOUNT;
    if ( accounts[ from ] < amount ) {
      return (void *) 0;
    }
    accounts[ from ] -= amount;
    printf( "terminal '%d': %5d from [%02d] to [%02d]\t", pthread_self(),
	amount, from, to );
    accounts[ to ] += amount;
    printf( "sum is %5d\n", sum() );
    usleep( random() % 200 );
  }

  return (void *) 0;
}

int main( void ) {
  pthread_t id[ ACCOUNT_SIZE ];
  int i;
  for ( i = 0; i < ACCOUNT_SIZE; i++ ) {
    accounts[ i ] = INIT_AMOUNT;
  }
  /* exit one seconds later */
  alarm( 1 );
  for ( i = 0; i < ACCOUNT_SIZE; i++ ) {
    pthread_create( id+i, NULL, transfer, (void *) &i );
  }

  return 0;
}
