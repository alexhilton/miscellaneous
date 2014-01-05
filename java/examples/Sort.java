/*
 * sort.java
 *
 * implementation of sort algorithm
 */
public class Sort {
    public static void main( String[] args ) {
	int[] a = { 20, 10, 30, 20, 19, 4, 2, 68, 13, 78 };
	int i, j, tmp;

	//preview the array
	System.out.println( "before sorting" );
	for ( i = 0; i < a.length; i++ ) {
	    System.out.print( " " + a[ i ] + " " );
	}
	System.out.println( " " );
	// sorting section
	for ( i = 0; i < a.length - 1; i++ ) {
	    for ( j = i + 1; j < a.length; j++ ) {
		if ( a[ i ] > a[ j ] ) {
		    /* exchange the two elements */
		    tmp = a[ i ];
		    a[ i ] = a[ j ];
		    a[ j ] = tmp;
		}
	    }
	}
	System.out.println( "after sorting" );
	for ( i = 0; i < a.length; i++ ) {
	    System.out.print( "  " + a[ i ] + "  " );
	}
	System.out.println( " " );
    }
}
