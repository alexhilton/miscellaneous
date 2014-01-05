import java.lang.*;
/*
 * check.java
 *
 * checking the Gadabahe guess
 */
public class Check {
    public static boolean isPrime( int n ) {
	    int i;
	    double j;
	    j = Math.sqrt( n ) + 1;
	    boolean result = true;
	    for ( i = 2; i < j; i++ ) {
		if ( ( n % i ) == 0 ) { 
		    result = false;
		    break;
		}
	    }

	    return ( result );
    }
    public static void main( String[] args ) {
	//a method to tse whether an integer is a prime

	int num;
	int a, b;
	boolean flag = false;
	for ( num = 6; num < 100; num += 2 ) {
	    for ( a = 3; a < num / 2; a += 2 ) {
	        flag = false;
	        b = num - a;
		if ( isPrime( a ) ) {
		    flag = true;
		}
		if ( flag && isPrime( b ) ) {
	 	    System.out.print( num + " = " + a + " + " + b + "; " );
		}
	    }
	    System.out.println();
	}
    }
}
