/**
 * 
 */
package exercises.io.serialize;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.io.IOException;

/**
 * @author gongzhihui
 *
 */
public class RestoreBox {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PaperBox cup = new PaperBox();
		String filename = "box.txt";
		try {
			FileInputStream file = new FileInputStream(filename);
			ObjectInputStream oo = new ObjectInputStream(file);
			cup = (PaperBox) oo.readObject();
		} catch (IOException e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		} catch (Exception e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
		cup.print();
		System.out.println("I'm restored from file " + filename + " just now");
	}

}
