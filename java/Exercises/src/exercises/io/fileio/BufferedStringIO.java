/**
 * 
 */
package exercises.io.fileio;
import java.io.*;
/**
 * @author gongzhihui
 *
 */
public class BufferedStringIO {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			BufferedWriter writer = new BufferedWriter(new FileWriter(new File("tmp.txt")));
			writer.write("With great power comes great responsibility!");
			writer.flush();
			writer.close();
			
			BufferedReader reader = new BufferedReader(new FileReader(new File("tmp.txt")));
			String line = reader.readLine();
			System.out.println(line);
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
