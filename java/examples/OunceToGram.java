import genericUtil.*;
/*
 * exercise one of chap six.
 * implement converting ounce to gram.
 */
public class OunceToGram {
    public static void main( String[] args ) {
	if ( args.length < 1 ) {
	    System.out.println( "No input" );
	} else {
	    for ( int i = 0; i < args.length; i++ ) {
		int value = stringExten.str2int( args[ i ] );
		System.out.println( value * 28 );
	    }
	}
    }
}
