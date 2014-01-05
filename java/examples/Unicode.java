public class Unicode {
	public static void main( String[] args ) {
		int i;
		for ( i = 0; i < 201; i++ ) {
			System.out.print( " " + ( char ) i + " " );
			if ( i % 10 == 0 ) {
				System.out.println();
			}
		}
	}
}
