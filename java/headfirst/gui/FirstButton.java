package gui;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class FirstButton {
    public static void main(String[] args) {
	JFrame frame = new JFrame();
	frame.setSize(400, 300);
	frame.setTitle("FirstJavaButton");
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	final JPanel panel = new JPanel();
	JButton button = new JButton("Hello");
	button.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    panel.setBackground(Color.blue);
		}
	    });
	JButton exitButton = new JButton("Exit");
	exitButton.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
		    System.exit(0);
		}
	    });
	panel.add(button);
	panel.add(exitButton);
	frame.add(panel);
	frame.setVisible(true);
    }
}
