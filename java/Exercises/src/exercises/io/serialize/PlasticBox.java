/**
 * 
 */
package exercises.io.serialize;

import java.io.Serializable;

/**
 * @author gongzhihui
 *
 */
public class PlasticBox extends Box implements Serializable {

	public String toString() {
		return "I'm plastic box: " + super.toString();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
