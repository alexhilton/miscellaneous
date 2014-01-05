/**
 * 
 */
package exercises.io.fileio;
import java.io.*;
/**
 * @author gongzhihui
 *
 */
public class WriteFile {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			FileWriter out = null;
			FileReader in = null;
			try {
				String filename = "tmp.txt";
				out = new FileWriter("tmp.txt");
				out.write("With great power comes great responsibility");
				out.close();

				in = new FileReader(filename);
				in.read();
			} finally {
				if (out != null) {
					out.close();
				}
				if (in != null) {
					in.close();
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
