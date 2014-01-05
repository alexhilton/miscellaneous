/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class ThreadLocalVariableHolder {
	private static ThreadLocal<Integer> value = new ThreadLocal<Integer>() {
		private Random rand = new Random(47);
		protected synchronized Integer initialValue() {
			return rand.nextInt(10000);
		}
	};
	public static void increment() {
		value.set(value.get() + 1);
	}
	public static int get() {
		return value.get();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < 5; i++) {
			exec.execute(new Accessor(i));
		}
		TimeUnit.SECONDS.sleep(3); // run for a while
		exec.shutdown();
	}

}

class Accessor implements Runnable {
	private final int id;
	public Accessor(int idn) {
		this.id = idn;
	}
	public void run() {
		while (!Thread.currentThread().isInterrupted()) {
			ThreadLocalVariableHolder.increment();
			System.out.println(this);
			Thread.yield();
		}
	}
	public String toString() {
		return "#" + id + ": " + ThreadLocalVariableHolder.get();
	}
}