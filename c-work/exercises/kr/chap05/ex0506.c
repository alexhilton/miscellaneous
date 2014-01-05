/**
 * ex0506.c
 * implement getline, itoa, atoi and reverse using char pointer
 */
#include <stdio.h>

/**
 * @Function: int getline( char *line, int limit );
 * @Param: char *line -- the buffer you wanna read in
 * @Param: int limit -- the max number of chars the line can hold.
 * @Return: int -- the actual number of chars read, or the length of line after reading.
 * @Description: getline fill character buffer line with characters from standard input up to a newline
 * character or limit or an EOF. It will return the actual number of characters read. If there are more
 * than limit characters on the input line,it will abandon the exceeding chars and return.
 * @Pre-condition:
 * @Post-condition: It cannot return the mark of buffer exceeding and EOF. 
 */
int getline( char *line, int limit );
/**
 * @Function: int atoi( char *str );
 * @Param: char *str -- the string you wanna convert
 * @Return: int -- the converted integer
 * @Description: atoi will convert an string of digits into an integer. It can handle negative and positive
 * integers.
 * @Pre-condition: We assume param str contains digits only and an integer can hold it withouth causing 
 * overflowing. 
 * @Post-condition: it might return wrong answer if your input is invalid, in other words if the string contains non
 * digit or there are too many digits which exceeds an integer, the result is undeterminded. 
 */
int atoi( char *str );
/**
 * @Function: void itoa( char *str, int limit, int n );
 * @Param: char *str -- the string to hold the result
 * @Param: int limit -- max length of result holding string.
 * @Param: int n -- the integer you wanna convert.
 * @Description: itoa will convert integer n into a string into str. If n is invalid integer, it might cause
 * undefined things in str. It can handle negative and positive numbers.
 * @Pre-condition: we assume your input n is a valid integer and str is able to hold it.
 * @Post-condition: If str is too less to hold n, it will truncate up to limit.
 */
void itoa( char *str, int limit, int n );
/**
 * @Function: void reverse( char *str );
 * @Param: char *str --  the string you wanna reverse.
 * @Description: reverse will reverse a string.
 * @Pre-condition: 
 * @Post-condition:
 */
void reverse( char *str );

/* main program */
int main( int argc, char *argv[] ) {
  char str[ 128 ];
  int n;
  printf( "testing getline:\ninput a line:\n" ); 
  n = getline( str, 128 );
  printf( "your input line is: '%s'\n", str );
  reverse( str );
  printf( "testing reverse, the reverse of your last input line is: '%s'\n", str );
  printf( "testing atoi and itoa:\n input a string which you wanna to convert to integer:\n" );
  getline( str, 128 );
  n = atoi( str );
  itoa( str, 128, n );
  printf( "integer is: %d, and its converted string is: '%s'\n", n, str );
  return 0;
}

int getline( char *line, int limit ) {
  char ch;
  int len = 0;
  while ( ++len < limit && (ch = getchar()) != EOF && ch != '\n' ) {
    *line++ = ch;
  }
  if ( ch == '\n' ) {
    *line++ = '\0';
  }
  return len;
}

int atoi( char *str ) {
  int n = 0;
  int sign;
  if ( *str == '-' ) {
    sign = -1;
    str++;
  } else if ( *str == '+' ) {
    sign = 1;
    str++;
  } else {
    sign = 1;
  }
  for ( ; *str != '\0'; str++ ) {
    n = n * 10 + (int) (*str - '0');
  }
  return n * sign;
}

void itoa( char *str, int limit, int n ) {
  char *p = str;
  if ( n < 0 ) {
    *str++ = '-';
    n = -n;
  } 
  while ( n >= 10 ) {
    *str++ = n % 10 + '0';
    n /= 10;
  }
  *str++ = n + '0';
  *str = '\0';
  if ( str - p > limit ) {
    *(p + limit) = '\0';
  }
  if ( *p == '-' ) {
    p++;
  }
  reverse( p );
}

void reverse( char *str ) {
  char *q = str;
  while ( *q++ )
    ;
  q -= 2;
  for ( ; str < q; str++, q-- ) {
    *str -= *q;
    *q += *str;
    *str = *q - *str;
  }
}
