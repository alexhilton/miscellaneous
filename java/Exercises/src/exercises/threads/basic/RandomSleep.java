package exercises.threads.basic;

/**
 * 
 */
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;
/**
 * @author gongzhihui
 *
 */
public class RandomSleep implements Runnable {
	private int second;
	public RandomSleep() {
		second = (int) (Math.random() * 1000) % 1000;
	}
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("I am gonna sleep about " + second + " milleseconds!");
		try {
			TimeUnit.MICROSECONDS.sleep(second);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < 10; i++) {
			exec.execute(new RandomSleep());
		}
		exec.shutdown();
		System.out.println("randome sleeping...");
	}

}
