import genericUtil.*;
public class PintToLiters {
    public static void main( String[] args ) {
	if ( args.length < 1 ) {
	    System.err.println( "No input" );
	} else {
	    for ( int i = 0; i < args.length; i++ ) {
		int value = stringExten.str2int( args[ i ] );
		System.out.println( value * 0.568 );
	    }
	}
    }
}

