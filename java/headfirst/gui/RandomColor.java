package gui;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class RandomColor {
    public static void main(String[] args) {
	ColorFrame frame = new ColorFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setVisible(true);
    }
}

class ColorFrame extends JFrame {
    private ColorPanel panel;
    public ColorFrame() {
	panel = new ColorPanel();
	add(panel);
	setSize(320, 240);
	setTitle("RandomColor");
    }
}

class ColorPanel extends JPanel {
    private JButton show;
    private JButton exit;
    public ColorPanel() {
	show = new JButton("Change Color");
	show.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    ColorPanel.this.repaint();
		}
	    });
	exit = new JButton("Exit");
	exit.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    System.exit(0);
		}
	    });
	this.add(show);
	this.add(exit);
    }
    public void paintComponent(Graphics g) {
	g.fillRect(0, 0, this.getWidth(), this.getHeight());
	int red = (int) (Math.random() * 255);
	int green = (int) (Math.random() * 255);
	int blue = (int) (Math.random() * 255);

	Color randomColor = new Color(red, green, blue);
	g.setColor(randomColor);
	g.fillOval(70, 70, 100, 100);
    }
}
