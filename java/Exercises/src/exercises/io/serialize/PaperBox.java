/**
 * 
 */
package exercises.io.serialize;

import java.io.Serializable;

/**
 * @author gongzhihui
 *
 */
public class PaperBox extends Box implements Serializable {
	
	public String toString() {
		return "I'm a paper box: " + super.toString();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
