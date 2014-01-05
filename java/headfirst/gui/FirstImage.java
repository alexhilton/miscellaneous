package gui;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class FirstImage {
	JFrame frame = new JFrame();
	ImagePanel panel = new ImagePanel();
    public void show() {
	frame.setSize(880, 680);
	frame.setTitle("FirstImage");
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.add(panel);
	frame.setVisible(true);
    }
    public static void main(String[] args) {
	    FirstImage run = new FirstImage();
	    run.show();
    }
}

class ImagePanel extends JPanel {
    public void paintComponent(Graphics g) {
	Image image = new ImageIcon("lixgreen.jpg").getImage();
	g.drawImage(image, 30, 40, this);
    }
}
