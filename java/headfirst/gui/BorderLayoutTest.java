/**
 * This class is deisignated to demonstrate how to use the BoderLayout.
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class BorderLayoutTest {
    JFrame frame;
    JButton north;
    JButton east;
    JButton south;
    JButton west;
    JButton center;
    JOptionPane pane;
    public void go() {
	frame = new JFrame();
	pane = new JOptionPane();
	frame.setBackground(new Color(125, 125, 125));
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	north = new JButton("North");
	north.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
			pane.showMessageDialog(frame, "You clicked North just now");
		}
	});
	east = new JButton("East");
	east.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
			pane.showMessageDialog(frame, "You clicked East just now");
		}
	});
	south = new JButton("South");
	east.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
			pane.showMessageDialog(frame, "You clicked South just now");
		}
	});
	west = new JButton("West");
	east.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
			pane.showMessageDialog(frame, "You clicked West just now");
		}
	});
	center = new JButton("Center");
	east.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
			pane.showMessageDialog(frame, "You clicked Center just now");
		}
	});
	frame.getContentPane().add(BorderLayout.NORTH, north);
	frame.getContentPane().add(BorderLayout.EAST, east);
	frame.getContentPane().add(BorderLayout.SOUTH, south);
	frame.getContentPane().add(BorderLayout.WEST, west);
	frame.getContentPane().add(BorderLayout.CENTER, center);
	frame.setSize(480, 320);
	frame.setVisible(true);
    }
    public static void main(String[] args) {
	    BorderLayoutTest gui = new BorderLayoutTest();
	    gui.go();
    }
}
