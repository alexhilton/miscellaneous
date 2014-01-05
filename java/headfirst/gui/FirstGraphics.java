package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class FirstGraphics {
    public static void main(String[] args) {
	JFrame frame = new JFrame();
	frame.setSize(400, 300);
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	MyPanel panel = new MyPanel();
	frame.add(panel);
	frame.setVisible(true);
    }
}

class MyPanel extends JPanel {
    public void paintComponent(Graphics g) {
	Graphics2D g2 = (Graphics2D) g;
	g2.setColor(Color.red);
	g2.fillOval(20, 30, 120, 130);
	g2.setColor(Color.blue);
	g2.fillRect(140, 50, 240, 150);
    }
}
