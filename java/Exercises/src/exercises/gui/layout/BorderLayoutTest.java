/**
 * 
 */
package exercises.gui.layout;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * @author gongzhihui
 *
 */
public class BorderLayoutTest {
	JOptionPane pane = new JOptionPane();
	JFrame frame;
	public void go() {
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JButton north = new JButton("North");
		north.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				pane.showMessageDialog(frame, "You clicked Button North just now");
			}
		});
		JButton east = new JButton("East");
		east.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				pane.showMessageDialog(frame, "You clicked button East just now");
			}
		});
		JButton south = new JButton("South");
		south.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				pane.showMessageDialog(frame, "You clicked button South just now");
			}
		});
		JButton west = new JButton("West");
		west.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				pane.showMessageDialog(frame, "You clicked button West just now");
			}
		});
		JButton center = new JButton("Center");
		center.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				pane.showMessageDialog(frame, "You clicked button center just now");
			}
		});
		frame.setSize(400, 300);
		frame.getContentPane().add(BorderLayout.NORTH, north);
		frame.getContentPane().add(BorderLayout.EAST, east);
		frame.getContentPane().add(BorderLayout.SOUTH, south);
		frame.getContentPane().add(BorderLayout.WEST, west);
		frame.getContentPane().add(BorderLayout.CENTER, center);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BorderLayoutTest gui = new BorderLayoutTest();
		gui.go();
	}

}
