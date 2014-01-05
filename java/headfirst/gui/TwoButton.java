package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TwoButton {
    JFrame frame;
    JLabel label;

    public static void main(String[] args) {
	TwoButton gui = new TwoButton();
	gui.go();
    }
    public void go() {
	frame = new JFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	label = new JLabel("I'm a label");
	DrawPanel panel = new DrawPanel();
	JButton labelButton = new JButton("Change Label");
	labelButton.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
		    label.setText("Ouch");
		}
	    });
	JButton change = new JButton("Change color");
	change.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent event) {
		    frame.repaint();
		}
	    });
	frame.getContentPane().add(BorderLayout.SOUTH, change);
	frame.getContentPane().add(BorderLayout.CENTER, panel);
	frame.getContentPane().add(BorderLayout.EAST, labelButton);
	frame.getContentPane().add(BorderLayout.WEST, label);

	frame.setSize(300, 300);
	frame.setVisible(true);
    }
}

class DrawPanel extends JPanel {
    public void paintComponent(Graphics g) {
	int red = (int) (Math.random() * 255);
	int green = (int) (Math.random() * 255);
	int blue = (int) (Math.random() * 255);
	g.setColor(new Color(red, green, blue));
	g.fillOval(30, 30, 30, 30);
    }
}
