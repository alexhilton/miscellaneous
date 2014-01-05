public class myecho {
	public static void main( String[] args ) {
		int i;
		for ( i = 1; i < args.length; i++ ) {
			System.out.print( args[ i ] );
		}
		System.out.println();
	}
}
