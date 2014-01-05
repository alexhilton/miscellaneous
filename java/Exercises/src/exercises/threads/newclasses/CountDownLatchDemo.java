/**
 * 
 */
package exercises.threads.newclasses;
import java.util.concurrent.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class CountDownLatchDemo {
	static final int SIZE = 100;
	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		// all must share a single CountDownLatch object
		// initialize the latch's counter with SIZE=100
		CountDownLatch latch = new CountDownLatch(SIZE);
		for (int i = 0; i < 10; i++) {
			exec.execute(new WaitingTask(latch));
		}
		
		for (int i = 0; i < SIZE; i++) {
			exec.execute(new TaskPortion(latch));
		}
		
		System.out.println("Launched all tasks");
		exec.shutdown();
	}

}

// perform some portion of a task
class TaskPortion implements Runnable {
	private static int counter = 0;
	private final int id = counter++;
	private static Random rand = new Random(47);
	private final CountDownLatch latch;
	TaskPortion(CountDownLatch latch) {
		this.latch = latch;
	}
	
	public void run() {
		try {
			doWork();
			latch.countDown();
		} catch (InterruptedException e) {
			// let it be
		}
	}
	
	public void doWork() throws InterruptedException {
		TimeUnit.MILLISECONDS.sleep(rand.nextInt(2000));
		System.out.println(this + " completed");
	}
	
	public String toString() {
		return String.format("%s1$-3d ", id);
	}
}

// waits on the CountDownLatch {
class WaitingTask implements Runnable {
	private static int counter = 0;
	private final int id = counter++;
	private final CountDownLatch latch;
	WaitingTask(CountDownLatch latch) {
		this.latch = latch;
	}
	
	public void run() {
		try {
			latch.await();
			System.out.println("Latch barrier passed for " + this);
		} catch (InterruptedException e) {
			System.out.println(this + " interrupted");
		}
	}
	
	public String toString() {
		return String.format("waiting task %1$-3d", id);
	}
}