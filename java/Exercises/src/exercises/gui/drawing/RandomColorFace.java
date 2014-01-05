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
public class RandomColorFace extends JPanel {
	JButton changeColor;
	JButton exit;
	JOptionPane pane;;
	public void paintComponent(Graphics g) {
		g.setColor(RandomColor.generateColor());
		g.fillOval(120, 140, 400, 280);
		g.setColor(RandomColor.generateColor());
		g.fillOval(220, 210, 40, 70);
		g.setColor(RandomColor.generateColor());
		g.fillOval(380, 210, 40, 70);
		g.setColor(RandomColor.generateColor());
		g.fillOval(270, 320, 100, 70);
	}
	
	public RandomColorFace() {
		changeColor = new JButton("Change Color");
		changeColor.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				RandomColorFace.this.repaint();
			}
		});
		exit = new JButton("Exit");
		pane = new JOptionPane();
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				pane.showMessageDialog(RandomColorFace.this, "Are you sure you want exit?");
				System.exit(0);
			}
		});
		this.add(changeColor);
		this.add(exit);
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(640, 480);
		frame.add(BorderLayout.CENTER, new RandomColorFace());
		frame.setVisible(true);
	}
}
