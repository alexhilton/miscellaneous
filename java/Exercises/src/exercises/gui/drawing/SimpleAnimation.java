/**
 * 
 */
package exercises.gui.drawing;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/**
 * @author gongzhihui
 *
 */
public class SimpleAnimation {
	private int x = 70;
	private int y = 70;
	private int width = 100;
	private int height = 100;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SimpleAnimation gui = new SimpleAnimation();
		gui.go();
	}
	
	public void go() {
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(new Dimension(400, 300));
		frame.setVisible(true);
		SimplePanel panel = new SimplePanel();
		frame.add(panel);
		
		for (int i = 0; i < 10000; i++ ) {
			if (++x + width > frame.getWidth()) {
				x = 0;
			}
			if (++y + height > frame.getHeight()) {
				y = 0;
			}
			panel.repaint();
			
			// slow down the ball movement, othewise our eyes cannot see it
			try {
				Thread.sleep(20);
			} catch (InterruptedException e) {
				// nothing to do
			}
		}
	}
	
	private class SimplePanel extends JPanel {
		public void paintComponent(Graphics g) {
			// We need to erase our last painting
			g.setColor(Color.white);
			g.fillRect(0, 0, getWidth(), getHeight());
			
			Color color = RandomColor.generateColor();
			g.setColor(color);
			g.fillOval(x, y, width, height);
		}
	}

}
