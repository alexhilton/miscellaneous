/*
 * taskdriver.cc
 *
 * a driver program to task.cc
 */
#include "task.cc"

int main() {
  time_t now = time( 0 );
  Task t1( "Defrost pizzas" ), t2( "Open beer" );
  Task t3( "Eat pizzas and drink beer" );

  t1.setStart( now );
  t1.setFinish( now + 3600 );

  t2.setStart( t1.getFinish() );
  t2.setFinish( t2.getStart() + 2 );

  t3.setStart( t2.getFinish() + 1 );
  t3.setFinish( t3.getStart() + 7200 );

  return 0;
}
