/**
 * 
 */
package exercises.threads.cooperating;
import java.util.*;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class NotifyVsNotifyAll {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < 5; i++) {
			exec.execute(new Task());
		}
		exec.execute(new Task2());
		Timer timer = new Timer();
		timer.scheduleAtFixedRate(new TimerTask() {
			boolean prod = true;
			public void run() {
				if (prod) {
					System.out.println("\nnoitfy()");
					Task.blocker.prod();
					prod = false;
				} else {
					System.out.println("\nnotifyAll()");
					Task.blocker.prodAll();
					prod = true;
				}
			}
		}, 400, 400);
		
		try {
			TimeUnit.SECONDS.sleep(5);
			timer.cancel();
			System.out.println("\nTimer cancelled");
			TimeUnit.MILLISECONDS.sleep(500);
			System.out.println("Task2.blocker.prodAll()");
			Task2.blocker.prodAll();
			TimeUnit.MILLISECONDS.sleep(500);
			System.out.println("\nShutting down");
			exec.shutdown();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}

class Blocker {
	synchronized void waitingCall() {
		try {
			while (!Thread.interrupted()) {
				wait();
				System.out.println(Thread.currentThread() + " ");
			}
		} catch (InterruptedException e) {
			// do nothing
		}
	}
	
	synchronized void prod() {
		notify();
	}
	
	synchronized void prodAll() {
		notifyAll();
	}
}

class Task implements Runnable {
	static Blocker blocker = new Blocker();
	public void run() {
		blocker.waitingCall();
	}
}

class Task2 implements Runnable {
	static Blocker blocker = new Blocker();
	public void run() {
		blocker.waitingCall();
	}
}