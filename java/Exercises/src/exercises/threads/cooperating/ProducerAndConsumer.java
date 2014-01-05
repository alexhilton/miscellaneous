/**
 * 
 */
package exercises.threads.cooperating;
import java.util.*;
import java.util.concurrent.*;
/**
 * @author Alex Hilton
 *
 */
public class ProducerAndConsumer {
	private String meal;
	private class Cook implements Runnable {
		public void run() {
			synchronized (this) {
				while (meal != null) {
					try {
						wait();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
			meal = new String("Turkey");
			System.out.println("Meal is ready");
			synchronized(this) {
				notify();
			}
		}
	}
	
	private class Guest implements Runnable {
		public void run() {
			synchronized (this) {
				while (meal == null) {
					try {
						wait();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
			System.out.println("I got meal");
		}
	}
	
	public void test() {
		new Thread(new Cook()).start();
		new Thread(new Guest()).start();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new ProducerAndConsumer().test();
	}

}
