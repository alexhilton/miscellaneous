import genericUtil.*;
import java.lang.*;

public class IsPrime {
    public static boolean isPrime( int n ) {
	int i;
	double j;
	boolean result = true;
	j = Math.sqrt( n ) + 1;
	for ( i = 2; i < j; i++ ) {
	    if ( n % i == 0 ) {
		result = false;
		break;
	    }
	}
	return ( result );
    }
    public static void main( String[] args ) {
	int len = args.length;
	int num;
	if ( len < 1 ) {
	    System.err.println( "no input" );
	    System.exit( 1 );
	} else {
	    for ( int i = 0; i < len; i++ ) {
                num = stringExten.str2int( args[ i ] );
                if ( isPrime( num ) ) {
	            System.out.println( "true" );
                } else {
                    System.out.println( "false" );
	        }
	    }
	}
    }
}
