/**
 * 
 */
package exercises.io.serialize;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;

/**
 * @author gongzhihui
 *
 */
public class SaveBox {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PaperBox cup = new PaperBox();
		cup.setName("Cup's box");
		cup.setHeight(340);
		cup.setWeight(30);
		cup.setCapacity(402);
		cup.print();
		System.out.println("I'm going to serialize now...");
		String filename = "box.txt";
		try {
			FileOutputStream file = new FileOutputStream(filename);
			ObjectOutputStream oo = new ObjectOutputStream(file);
			oo.writeObject(cup);
			file.close();
			oo.close();
		} catch (IOException e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
	}
}
