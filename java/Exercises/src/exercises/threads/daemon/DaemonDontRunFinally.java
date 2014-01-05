/**
 * 
 */
package exercises.threads.daemon;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class DaemonDontRunFinally {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Thread t = new Thread(new ADaemon());
		t.setDaemon(true);
		t.start();
	}
}

class ADaemon implements Runnable {
	public void  run() {
		try {
			System.out.println(" staring ADaemon");
			TimeUnit.SECONDS.sleep(1);
		} catch (InterruptedException e) {
			System.out.println("Exiting via InterruptedException");
		} finally {
			System.out.println("This should alwasy run?");
		}
	}
}
