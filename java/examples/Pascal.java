import genericUtil.*;
/*
 * pascal.java
 *
 * this program generates a Pascal triangle.
 */
public class Pascal {
    public static void pascalArray( int size ) {
	int[][] arr = new int[ size ][ size ];
	int i, j;
	for ( i = 0; i < size; i++ ) {
	    arr[ i ][ 0 ] = 1;
	    arr[ i ][ i ] = 1;
	}
	for ( i = 1; i < size; i++ ) {
	    for ( j = 1; j < i; j++ ) {
		arr[ i ][ j ] = arr[ i - 1 ][ j - 1 ] + arr[ i - 1 ][ j ];
	    }
	}

	 for ( i = 0; i < size; i++ ) {
  	     for ( j = 0; j <= i; j++ ) {
		    System.out.print( " " + arr[ i ][ j ] + " " );
	     }
	     System.out.println();
	 }
    }
    public static void main( String[] args ) {
	int size = 10;
	int len = args.length;
	if ( len < 1 ) {
	    size = 10;
	} else {
            size = stringExten.str2int( args[ 0 ] );
	}
	pascalArray( size );
    }
}

