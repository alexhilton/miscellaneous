/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class SerialNumberChecker {
	private static final int SIZE = 10;
	private static CircularSet serials = new CircularSet(1000);
	private static ExecutorService exec = Executors.newCachedThreadPool();
	static class SerialChecker implements Runnable {
		public void run() {
			while (true) {
				int serial = SerialNumberGenerator.nextSerialNumber();
				if (serials.contains(serial)) {
					System.out.println("Duplicate: " + serial);
					System.exit(0);
				}
				serials.add(serial);
			}
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for (int i = 0; i < SIZE; i++) {
			exec.execute(new SerialChecker());
		}
		if (args.length > 0) {
			try {
				TimeUnit.SECONDS.sleep(new Integer(args[0]));
			} catch (NumberFormatException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("No dupplicates detected");
			System.exit(0);
		}
	}

}

class CircularSet {
	private int[] array;
	private int len;
	private int index = 0;
	public CircularSet(int size) {
		array = new int[size];
		len = size;
		for (int i = 0; i < size; i++) {
			array[i] = -1;
		}
	}
	public synchronized void add(int i) {
		array[index] = i;
		index = ++index % len;
	}
	public synchronized boolean contains(int val) {
		int i;
		for (i = 0; i < len && array[i] != val; i++)
			;
		if (i < len) {
			return true;
		} else {
			return false;
		}
	}
}