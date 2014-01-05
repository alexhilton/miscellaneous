package gui;

import javax.swing.*;
import java.awt.*;

public class SimpleAnimation {
    int x = 70;
    int y = 70;
    public static void main(String[] args) {
	SimpleAnimation gui = new SimpleAnimation();
	gui.go();
    }
    public void go() {
	JFrame frame = new JFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	DrawPanel drawPanel = new DrawPanel();
	frame.getContentPane().add(drawPanel);
	frame.setSize(300, 300);
	frame.setVisible(true);

	for (int i = 0; i < 130; i++) {
	    x++;
	    y++;
	    drawPanel.repaint();
	    try {
		Thread.sleep(50);
	    } catch (Exception ex) {}
	}
    }

    private class DrawPanel extends JPanel {
	public void paintComponent(Graphics g) {
	    g.setColor(Color.white);
	    g.fillRect(0, 0, getWidth(), getHeight());
	    g.setColor(Color.green);
	    g.fillOval(x, y, 40, 40);
	}
    }
}
