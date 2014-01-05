package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Face  {
    JFrame frame;
    public static void main(String[] args) {
	Face face = new Face();
	face.go();
    }
    public void go() {
	frame = new JFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	JButton button = new JButton("Change  colors");
	button.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    frame.repaint();
		}
	    });
	MyDrawPanel drawPanel = new MyDrawPanel();
	frame.getContentPane().add(BorderLayout.SOUTH, button);
	frame.add(BorderLayout.CENTER, drawPanel);
	frame.setSize(480, 360);
	frame.setVisible(true);
    }
}

class MyDrawPanel extends JPanel {
    public void paintComponent(Graphics g) {
	int red = (int) (Math.random() * 255);
	int green = (int) (Math.random() * 255);
	int blue = (int) (Math.random() * 255);
	g.setColor(new Color(red, green, blue));
	g.fillOval(40, 20, 400, 280);
	red = (int) (Math.random() * 255);
	green = (int) (Math.random() * 255);
	blue = (int) (Math.random() * 255);
	g.setColor(new Color(red, green, blue));
	g.fillOval(140, 90, 40, 70);
	red = (int) (Math.random() * 255);
	green = (int) (Math.random() * 255);
	blue = (int) (Math.random() * 255);
	g.setColor(new Color(red, green, blue));
	g.fillOval(300, 90, 40, 70);
	red = (int) (Math.random() * 255);
	green = (int) (Math.random() * 255);
	blue = (int) (Math.random() * 255);
	g.setColor(new Color(red, green, blue));
	g.fillRect(190, 200, 100, 70);
    }
}
