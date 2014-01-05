import java.util.*;

/**
 * ExceptionDemo.java
 * A sample demonstration of Exception handling mechanism in java.
 */
public class ExceptionDemo {
    public static void main( String[] args ) {
	int a, b, remainder, quotation;
	Scanner keyboard = new Scanner( System.in );
	try {
	    System.out.println( "input two integers in a line" );
	    a = keyboard.nextInt();
	    b = keyboard.nextInt();
	    if ( b == 0 ) {
		throw new Exception( "Divid by zero" );
	    }
	    System.out.println( a / b );
	} catch ( Exception e ) {
	    System.out.println( e.getMessage() );
	}
    }
}
