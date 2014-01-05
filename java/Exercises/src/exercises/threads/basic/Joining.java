/**
 * 
 */
package exercises.threads.basic;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class Joining {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Sleeper sleepy = new Sleeper("sleepy", 1500);
		Sleeper grumpy = new Sleeper("grumpy", 1500);
		Joiner dopey = new Joiner("Dopey", sleepy);
		Joiner doc = new Joiner("doc", grumpy);
		grumpy.interrupt();
	}

}


// a sleeper class
class Sleeper extends Thread {
	private int duration;
	public Sleeper(String name, int duration) {
		super(name);
		this.duration = duration;
		this.start();
	}
	
	public void run() {
		try {
			sleep(duration);
		} catch (InterruptedException e) {
			System.out.println(this.getName()  + " was interrupted. " + " isInterrupted(): "  + 
					isInterrupted());
			return;
		}
		System.out.println(this.getName() + " has awakened");
	}
}

// joiner class
class Joiner extends Thread {
	private Sleeper sleeper;
	public Joiner(String name, Sleeper sleeper) {
		super(name);
		this.sleeper = sleeper;
		this.start();
	}
	public void run() {
		try {
			/*
			 * sleeper will be suspended.
			 */
			sleeper.join();
		} catch (InterruptedException e) {
			System.out.println("Interrupted");
		}
		System.out.println(this.getName() + " join completed");
	}
}