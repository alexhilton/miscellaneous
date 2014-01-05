import java.io.*;

/*
 * MyCopy.java
 * an utility for dos that copies a file from another.
 */
public class MyCopy {
	public static void main( String[] args ) throws IOException {
		File inputFile = new File( "src.txt" );
		File outputFile = new File( "dst.txt" );

		FileReader in = new FileReader( inputFile );
		FileWriter out = new FileWriter( outputFile );

		int c;

		while ( ( c = in.read() ) != -1 ) {
			out.write( c );
		}
		in.close();
		out.close();
	}
}

