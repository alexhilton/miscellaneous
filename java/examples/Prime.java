import java.lang.*;
/*
 * prime.java
 *
 * program to test Gadabahe guess, that is, divide all even integers
 * into sum of two primes.
 */
public class Prime {
    public static void main( String[] args ) {
	int i = 0;
	int prime = 0;
	boolean isPrime = true;
	double j = 0;
	for ( prime = 3; prime < 200; prime += 1 ) {
	    isPrime = true;
	    j = Math.sqrt( prime ) + 1;
	    for ( i = 2; i < j; i++ ) {
		if ( ( prime % i ) == 0 ) {
	            isPrime = false;
		    break;
		} 
	    }
	    if ( isPrime ) {
		System.out.println( "the prime is " + prime );
	    }
	}
    }
}
