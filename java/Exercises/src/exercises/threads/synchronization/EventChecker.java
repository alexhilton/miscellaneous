/**
 * 
 */
package exercises.threads.synchronization;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class EventChecker implements Runnable {
	private IntGenerator generator;
	private final int id;
	public EventChecker(IntGenerator g, int id) {
		this.generator = g;
		this.id = id;
	}
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		while (!generator.isCanceled()) {
			int val = generator.next();
			if ((val & 0x01) != 0) {
				System.out.println(val + " not even");
				generator.cancel();
			}
		}
	}

	public static void test(IntGenerator go, int count) {
		System.out.println("Press Control-C to exit");
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < count; i++) {
			exec.execute(new EventChecker(go, i));
		}
		exec.shutdown();
	}
	
	public static void test(IntGenerator go) {
		test(go, 10);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
