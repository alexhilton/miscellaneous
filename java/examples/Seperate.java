import genericUtil.*;
/*
 * exercise two of chap six
 */
public class Seperate {
    public static void main( String[] args ) {
	int i = 0, j = 0;
	int length = 0;
	length = args.length;
	if ( length < 1 ) {
	    System.err.println( "No input" );
	} else {
	    for ( i = 0; i < length; i++ ) {
		String lowercase = args[ i ].toLowerCase();
		for ( j = 0; j < args[ i ].length(); j++ ) {
		    char c = lowercase.charAt( j );
		    if ( stringExten.isVowel( c ) ) {
			c = Character.toUpperCase( c );
		    }
		    System.out.println( c );
		}
	    }
	}
    }
}
