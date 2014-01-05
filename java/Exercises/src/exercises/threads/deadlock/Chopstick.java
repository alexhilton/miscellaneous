/**
 * 
 */
package exercises.threads.deadlock;

/**
 * @author gongzhihui
 *
 */
public class Chopstick {
	private boolean taken = false;
	public synchronized void take() throws InterruptedException {
		while (taken) {
			wait();
		}
		taken = true;
	}
	
	public synchronized void drop() {
		taken = false;
		notifyAll();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
