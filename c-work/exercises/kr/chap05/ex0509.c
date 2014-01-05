/**
 * ex0509.c
 * implement a tool to convert a day of month into day of year and
 * a day of year into day of month.
 * replace index of array with corresponding pointer.
 */
#include <stdio.h>

static int daytab[ 2 ][ 13 ] = {
  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

/* day-of-year: set day of year from month & day */
static int day_of_year( int year, int month, int day );
/* month_day: set month, day from day_of_year */
static void month_day( int year, int yearday, int *pmonth, int *pday );
/* month_name: return the name of n-th month */
static char *month_name( int month );

/* main program */
int main( int argc, char *argv[] ) {
  int year, day, month, yearday;
  printf( "test day_of_year, input a year, month and day of month:\n" );
  scanf( "%d %d %d", &year, &month, &day );
  printf( "the day of year is: %d\n", day_of_year( year, month, day ) );
  printf( "testing month_day, input a year and day of year:\n" );
  scanf( "%d %d", &year, &yearday );
  month_day( year, yearday, &month, &day );
  printf( "the month is %d, day of month is %d\n", month, day );
  printf( "the name of month is: '%s'\n", month_name( month ) );
  return 0;
}

static char *month_name( int month ) {
  static char *name[] = {
    "Illegal month", "January", "February", "March", "April",
    "May", "June", "July", "August", "September", "October",
    "November", "December"
  };
  return ( month < 1 || month > 12 ) ? *name : *(name + month);
}

static int day_of_year( int year, int month, int day ) {
  int leap, i;
  /* error check */
  if ( year < 0 || month < 1 || month > 12 || day < 1 || day > 31 ) {
    return -1; // error occured
  }

  leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
  for ( i = 1; i < month; i++ ) {
    //day += *(*daytab + leap*13 + i);
    day += *(*(daytab + leap) + i);
  }
  return day;
}

static void month_day( int year, int yearday, int *pmonth, int *pday ) {
  if ( year < 0 || yearday < 0 || yearday > 366 ) {
    return; // error occured.
  }

  int i, leap;
  leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
  for ( i = 1; yearday > *(*(daytab + leap) + i) && i < 13; i++ ) {
    yearday -= *(*(daytab + leap) + i);
  }
  *pmonth = i;
  *pday = yearday;
}
