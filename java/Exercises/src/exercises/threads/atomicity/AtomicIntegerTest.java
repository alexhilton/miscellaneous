/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class AtomicIntegerTest implements Runnable {
	private AtomicInteger i = new AtomicInteger(0);
	public int getValue() {
		return i.get();
	}
	private void evenIncrement() {
		i.addAndGet(2);
	}
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		while (true) {
			evenIncrement();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new Timer().schedule(new TimerTask() {
			public void run() {
				System.err.println("Aborting");
				System.exit(0);
			}
		}, 5000); // terminating after 5 seconds
		ExecutorService exec = Executors.newCachedThreadPool();
		AtomicIntegerTest ait = new AtomicIntegerTest();
		exec.execute(ait);
		while (true) {
			int val = ait.getValue();
			if ((val & 0x01) != 0) {
				System.out.println(val);
				System.exit(0);
			}
		}
	}

}
