/**
 * 
 */
package exercises.threads.termination;
import java.util.*;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class OrnamentalGarden {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < 5; i++) {
			exec.execute(new Entrance(i));
		}
		// run for while then stop and collect the data
		try {
			TimeUnit.SECONDS.sleep(3);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Entrance.cancel();
		exec.shutdown();
		try {
			if (!exec.awaitTermination(250, TimeUnit.MICROSECONDS)) {
				System.out.println("some tasks were not terminated");
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Total: " + Entrance.getTotalCount());
		System.out.println("Sum of Entrances: " + Entrance.sumEntrance());
	}

}

class Count {
	private int count = 0;
	private Random rand = new Random(47);
	// remove the synchronized keyword to see counting fail
	public synchronized int increment() {
		int tmp = count;
		if (rand.nextBoolean()) { // Yield half the time
			Thread.yield();
		}
		return (count = ++tmp);
	}
	public synchronized int value() {
		return count;
	}
	
}

class Entrance implements Runnable {
	private static Count count = new Count();
	private static List<Entrance> entrances = new ArrayList<Entrance>();
	private int number = 0;
	// doesnot need synchronization to read
	private final int id;
	private static volatile boolean cancelled = false;
	// atomic operation on a volatile field
	public static void cancel() {
		cancelled = true;
	}
	
	public Entrance(int id) {
		this.id = id;
		// keep this task in a list. Also prevents garbage collection of dead tasks
		entrances.add(this);
	}
	
	public void run() {
		while (!cancelled) {
			synchronized (this) {
				number++;
			}
			System.out.println(this + " Total: " + count.increment());
			try {
				TimeUnit.MICROSECONDS.sleep(100);
			} catch (InterruptedException e) {
				System.out.println("sleep interrupted");
			}
		}
		System.out.println("stopping " + this);
	}
	
	public synchronized int getValue() {
		return number;
	}
	
	public String toString() {
		return "Entrance " + id + ": " + getValue();
	}
	
	public static int getTotalCount() {
		return count.value();
	}
	
	// sum all the entrances
	public static int sumEntrance() {
		int sum = 0;
		for (Entrance en : entrances) {
			sum += en.getValue();
		}
		return sum;
	}
}