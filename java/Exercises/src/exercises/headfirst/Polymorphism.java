/**
 * 
 */
package exercises.headfirst;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JPanel;
import javax.swing.JFrame;
/**
 * @author gongzhihui
 *
 */
public class Polymorphism extends JPanel {
	private int x0;
	private int y0;
	private int width;
	private int height;
	public Polymorphism() {
		x0 = 0;
		y0 = 0;
		width = 20;
		height = 20;
	}
	
	public Polymorphism(int x0, int y0, int width, int height) {
		this.x0 = x0;
		this.y0 = y0;
		this.width = width;
		this.height = height;
	}
	
	public void repaintComponent(Graphics g) {
		Shape[] shape = new Shape[4];
		shape[0] = new Circle();
		shape[1] = new Triangle();
		shape[2] = new Rectangle();
		for (Shape s : shape) {
			s.draw(g, x0, y0, width, height);
			x0 += width;
			y0 -= height;
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Polymorphism poly = new Polymorphism(10, 10, 30, 30);
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(poly);
		frame.setSize(new Dimension(400, 400));
		frame.setVisible(true);
	}

}

class Shape {
	public void draw(Graphics g, int x, int y, int width, int height) {
		// draw a picture
		g.setColor(new Color(25, 62, 140));
	}
}

class Circle extends Shape {
	public void draw(Graphics g, int x, int y, int width, int height) {
		super.draw(g, x, y, width, height);
		g.drawArc(10, 10, width, height, 0, 0);
	}
}

class Triangle extends Shape {
	public void draw(Graphics g, int x, int y, int width, int height) {
		super.draw(g, x, y, width, height);
		g.drawArc(x, y, width, height, 0, 0);
	}
}

class Rectangle extends Shape {
	public void draw(Graphics g, int x, int y, int width, int height) {
		super.draw(g, x, y, width, height);
		g.drawRect(x, y, width, height);
	}
}