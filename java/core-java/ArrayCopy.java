public class ArrayCopy {
    public static void main( String[] args ) {
	int[] from = { 2, 3, 5, 7, 9 };
	int[] to = { 1001,1002, 1003, 1004, 1005, 1006, 1007 };
	int i;
	System.out.println( "preview array a and b " );
	for ( i : from ) {
	    System.out.print( i + " " );
	}
	System.out.println();
	for ( i : to ) {
	    System.out.print( i + " " );
	}
	System.out.println();
	System.ArrayCopy( from, 2, to, 3, 3 );
	for ( i : to ) {
	    System.out.print( i + " " );
	}
	System.out.println();
    }
}