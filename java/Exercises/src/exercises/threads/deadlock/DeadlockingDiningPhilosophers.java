/**
 * 
 */
package exercises.threads.deadlock;
import java.io.IOException;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class DeadlockingDiningPhilosophers {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int ponder = 5;
		if (args.length > 0) {
			ponder = Integer.parseInt(args[0]);
		}
		int size = 5;
		if (args.length > 1) {
			size = Integer.parseInt(args[1]);
		}
		ExecutorService exec = Executors.newCachedThreadPool();
		Chopstick[] sticks = new Chopstick[size];
		for (int i = 0; i < size; i++) {
			sticks[i] = new Chopstick();
		}
		
		for (int i = 0; i < size; i++) {
			exec.execute(new Philosopher(sticks[i], sticks[(i+1) % size], i, ponder));
		}
		
		try {
			if (args.length == 3 && args[2].equals("timeout")) {
				TimeUnit.SECONDS.sleep(5);
			} else {
				System.out.println("Press 'Enter' to quit");
				System.in.read();
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		exec.shutdownNow();
	}

}
