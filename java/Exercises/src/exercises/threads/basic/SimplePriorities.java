package exercises.threads.basic;


/**
 * 
 */
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

/**
 * @author gongzhihui
 *
 */
public class SimplePriorities implements Runnable {
	private int countDown = 5;
	private volatile double d; // no cpu optimization
	private int priority;
	public SimplePriorities(int priority) {
		this.priority = priority;
	}
	
	public String toString() {
		return Thread.currentThread() + ": " + countDown;
	}
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		Thread.currentThread().setPriority(this.priority);
		while (true) {
			for (int i = 0; i < 10000; i++) {
				d += (Math.PI + Math.E) / (double) i;
				if (i % 1000 == 0) {
					Thread.yield();
				}
			}
			System.out.println(this);
			if (--countDown == 0) {
				return;
			}
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < 5; i++) {
			exec.execute(new SimplePriorities(Thread.MIN_PRIORITY));
		}
		exec.execute(new SimplePriorities(Thread.MAX_PRIORITY));
		exec.shutdown();
	}

}
