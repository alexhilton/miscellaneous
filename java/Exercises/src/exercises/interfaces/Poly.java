/**
 * 
 */
package exercises.interfaces;

/**
 * @author gongzhihui
 *
 */
public class Poly {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Shape[] shape = new Shape[3];
		shape[0] = new Circle();
		shape[1] = new Triangular();
		shape[2] = new Square();
		for (Shape sh : shape) {
			sh.draw();
		}
	}

}

abstract class Shape {
	public abstract void draw();
}

class Circle extends Shape {
	@Override
	public void draw() {
		System.out.println("Circle");
	}
}

class Triangular extends Shape {
	@Override
	public void draw() {
		System.out.println("Triangular");
	}
}

class Square extends Shape {
	@Override
	public void draw() {
		System.out.println("Square");
	}
}