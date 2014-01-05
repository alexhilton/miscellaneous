/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class AtomicityTest implements Runnable {
	private int i = 0;
	public int getValue() {
		return i;
	}
	private synchronized void evenIncrement() {
		i++;
		i++;
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
		ExecutorService exec = Executors.newCachedThreadPool();
		AtomicityTest at = new AtomicityTest();
		exec.execute(at);
		while (true) {
			int val = at.getValue();
			if ((val & 0x01) != 0) {
				System.out.println(val);
				System.exit(0);
			}
		}
	}

}
