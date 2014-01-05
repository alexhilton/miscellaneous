/*
 * resturant.c
 * simulate the cook and tablewaitor and customer in a resturant with producer
 * and consumer model and threading tools---lock and condition.
 * thread Cook will cook meals when there is a need 
 * thread Tablewaitor will deliver the meal when meal is ready
 * thread consumer will enjoy the meal when it is delivered.
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t cook_meal_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cook_meal_cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t deliver_meal_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t deliver_meal_cond = PTHREAD_COND_INITIALIZER;

static char *meal = NULL;
static char *table = NULL;

/*
 * When there is no food, the cook must cook it.
 * If the meal is already there, then cook can rest a little while for next
 * order.
 */
static void *cook( void *arg ) {
  pthread_mutex_lock( &cook_meal_lock );
  while ( meal != NULL ) {
    pthread_cond_wait( &cook_meal_cond, &cook_meal_lock );
  }
  pthread_mutex_unlock( &cook_meal_lock );
  meal = "Humberger";
  printf( "Meal is ready to deliver\n" );
  pthread_cond_signal( &cook_meal_cond );

  return (void *) 0;
}

/*
 * If the meal is not ready---the cook hasn't finished, waitor has to wait.
 * If cook finishes, waitor will deliver the meal to consumer --- our guest.
 */
static void *waitor( void *arg ) {
  pthread_mutex_lock( &cook_meal_lock );
  while ( meal == NULL ) {
    pthread_cond_wait( &cook_meal_cond, &cook_meal_lock );
  }
  pthread_mutex_unlock( &cook_meal_lock );
  table = meal;
  printf( "Delivering meal '%s' to customer\n", meal );
  pthread_cond_signal( &deliver_meal_cond );

  return (void *) 0;
}

/*
 * When the meal is delivered, we can enjoy. Otherwise, we have to wait.
 */
static void *consumer( void *arg ) {
  pthread_mutex_lock( &deliver_meal_lock );
  while ( table == NULL ) {
    pthread_cond_wait( &deliver_meal_cond, &deliver_meal_lock );
  }
  pthread_mutex_unlock( &deliver_meal_lock );
  printf( "we can enjoy '%s'\n", table );
  
  return (void *) 0;
}

int main( void ) {
  pthread_t cook_id, waitor_id, consumer_id;
  pthread_create( &consumer_id, NULL, consumer, NULL );
  pthread_create( &waitor_id, NULL, waitor, NULL );
  pthread_create( &cook_id, NULL, cook, NULL );

  return 0;
}
