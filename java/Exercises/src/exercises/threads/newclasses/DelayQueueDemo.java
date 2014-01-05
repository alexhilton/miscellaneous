/**
 * 
 */
package exercises.threads.newclasses;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.TimeUnit.*;
/**
 * @author gongzhihui
 *
 */
public class DelayQueueDemo {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random rand = new Random(47);
		ExecutorService exec = Executors.newCachedThreadPool();
		DelayQueue<DelayedTask> queue = new DelayQueue<DelayedTask>();
		
		for (int i = 0; i < 20; i++) {
			queue.put(new DelayedTask(rand.nextInt(5000)));
		}
		queue.add(new DelayedTask.EndSentinel(5000, exec));
		exec.execute(new DelayedTaskConsumer(queue));
	}

}

class DelayedTask implements Runnable, Delayed {
	private static int counter = 0;
	private final int id = counter++;
	private final int delta;
	private final long trigger;
	protected static List<DelayedTask> sequence = new ArrayList<DelayedTask>();
	
	public DelayedTask(int delayInMilliseconds) {
		delta = delayInMilliseconds;
		trigger = System.nanoTime() + TimeUnit.NANOSECONDS.convert(delta, TimeUnit.MILLISECONDS);
		sequence.add(this);
	}
	
	public long getDelay(TimeUnit unit) {
		return unit.convert(trigger - System.nanoTime(), TimeUnit.NANOSECONDS);
	}
	
	public int compareTo(Delayed arg) {
		DelayedTask that = (DelayedTask)arg;
		if (trigger < that.trigger) {
			return -1;
		}
		if (trigger > that.trigger) {
			return 1;
		}
		return 0;
	}
	public void run() {
		System.out.print(this + " ");
	}
	
	public String toString() {
		return String.format("[%1$-4d]", delta) + " Task " + id;
	}
	
	public String summary() {
		return "(" + id + ":" + delta + ")";
	}
	
	public static class EndSentinel extends DelayedTask {
		private ExecutorService exec;
		public EndSentinel(int delay, ExecutorService exec) {
			super(delay);
			this.exec = exec;
		}
		
		public void run() {
			for (DelayedTask pt : sequence) {
				System.out.println(pt.summary());
			}
			
			System.out.println();
			System.out.print(this + " calling exec.shutdownNow()");
			exec.shutdownNow();
		}
	}
}

class DelayedTaskConsumer implements Runnable {
	private DelayQueue<DelayedTask> q;
	public DelayedTaskConsumer(DelayQueue<DelayedTask> q) {
		this.q = q;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				q.take().run();
			}
		}  catch (InterruptedException e) {
			// let it be
		}
		
		System.out.println("finished Delayed");
	}
}