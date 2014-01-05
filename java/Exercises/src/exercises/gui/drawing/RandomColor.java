/**
 * 
 */
package exercises.gui.drawing;
import javax.swing.*;
import java.awt.*;
/**
 * @author gongzhihui
 *
 */
public class RandomColor {
	public static Color generateColor() {
		int red = (int) (Math.random() * 255);
		int green = (int) (Math.random() * 255);
		int blue = (int) (Math.random() * 255);
		return new Color(red, green, blue);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
