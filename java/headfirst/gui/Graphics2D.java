package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Graphics2D {
    public static void main(String[] args) {
	JFrame frame = new JFrame();
	frame.setTitle("Graphics2D");
	frame.setSize(360, 240);
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	GraphicsPanel panel = new GraphicsPanel();
	frame.add(panel);
	frame.setVisible(true);
    }
}

class GraphicsPanel extends JPanel {
    private JButton changeColor;
    private JButton exit;
    public GraphicsPanel() {
	changeColor = new JButton("Change Color");
	changeColor.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    GraphicsPanel.this.repaint();
		}
	    });
	add(changeColor);
	exit = new JButton("Exit");
	exit.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    System.exit(0);
		}
	    });
	add(exit);
    }
    public void paintComponent(Graphics g) {
	Graphics2D g2d = (Graphics2D) g;
	int red = (int) (Math.random() * 255);
	int green = (int) (Math.random() * 255);
	int blue = (int) (Math.random() * 255);
	Color startColor = new Color(red, green, blue);

	red = (int) (Math.random() * 255);
	blue = (int) (Math.random() * 255);
	green = (int) (Math.random() * 255);
	Color endColor = new Color(red, green, blue);
	GradientPaint gradient = new GradientPaint(70, 70, startColor, 150, 150, endColor);
	g2d.setPaint(gradient);
	g2d.fillOval(70, 70, 100, 100);
    }
}
