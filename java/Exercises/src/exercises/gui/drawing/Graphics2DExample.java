/**
 * 
 */
package exercises.gui.drawing;
import java.awt.Graphics2D;
import javax.swing.JFrame;
import java.awt.Dimension;
import javax.swing.JPanel;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.GradientPaint;
/**
 * @author gongzhihui
 *
 */
public class Graphics2DExample {
	JFrame frame;
	
	public Graphics2DExample() {
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(new Dimension(300, 300));
		Graphics2DPanel panel = new Graphics2DPanel();
		frame.add(panel);
	}
	
	public void go() {
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Graphics2DExample gui = new Graphics2DExample();
		gui.go();
	}

}

class Graphics2DPanel extends JPanel {
	public void paintComponent(Graphics g) {
		Graphics2D g2d = (Graphics2D) g;
		GradientPaint gradient = new GradientPaint(10, 10, Color.blue, 100, 100, Color.orange);
		g2d.setPaint(gradient);
		g2d.fillOval(10, 10, 100, 100);
		
		Color startColor = RandomColor.generateColor();
		Color endColor = RandomColor.generateColor();
		gradient = new GradientPaint(150, 150, startColor, 100, 100, endColor);
		g2d.setPaint(gradient);
		g2d.fillOval(150, 150, 100, 100);
	}
}