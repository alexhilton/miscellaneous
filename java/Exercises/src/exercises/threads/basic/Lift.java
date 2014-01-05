/**
 * 
 */
package exercises.threads.basic;

/**
 * @author gongzhihui
 *
 */
public class Lift implements Runnable {
	private int count;
	
	public Lift(int count) {
		this.count = count;
	}
	
	public void run() {
		while (count-- > 0) {
			System.out.print(" " + count + " ");
		}
		System.out.println("Lifting off");
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new Thread(new Lift(10)).start();
		System.out.println("Waiting for lifting off");
	}

}
