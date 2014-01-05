/**
 * 
 */
package exercises.gui.drawing;

import javax.swing.JPanel;
import java.awt.*;
/**
 * @author gongzhihui
 *
 */
public class ChangeColorPanel extends JPanel {
	public void paintComponent(Graphics g) {
		g.setColor(RandomColor.generateColor());
		g.fillOval(40, 40, 100, 100);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	}

}
