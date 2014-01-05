/**
 * 
 */
package exercises.threads.interrupt;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class InterruptingIdiom {
	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		if (args.length != 1) {
			System.out.println("usage: java InterruptingIdiom delay-in-ms");
			System.exit(0);
		}
		Thread t = new Thread(new Blocked3());
		t.start();
		TimeUnit.MILLISECONDS.sleep(new Integer(args[0]));
		t.interrupt();
	}
}

class NeedsCleanup {
	private final int id;
	public NeedsCleanup(int ident) {
		id = ident;
		System.out.println("NeedsCleanup " + id);
	}
	
	public void cleanup() {
		System.out.println("Cleaning up " + id);
	}
}

class Blocked3 implements Runnable {
	private volatile double d = 0.0;
	public void run() {
		try {
			while (!Thread.interrupted()) {
				// point 1
				NeedsCleanup n1 = new NeedsCleanup(1);
				/*
				 * start try-finally immediately after definition of n1, to guarantee
				 *  proper cleanup of n1.
				 */
				try {
					System.out.println("Sleeping");
					TimeUnit.SECONDS.sleep(1);
					// point2
					NeedsCleanup n2 = new NeedsCleanup(2);
					// Guarantee proper clenaup of n2
					try {
						System.out.println("Calculating");
						// a time-consuming, non-blocking operation
						for (int i = 1; i < 2500000; i++) {
							d = d + (Math.PI + Math.E) / d;
						}
						System.out.println("Finished time-consuming operation");
					} finally {
						n2.cleanup();
					}
				} finally {
					n1.cleanup();
				}
			}
			System.out.println("exiting via while() test");
		} catch (InterruptedException e) {
			System.out.println("exiting via interruptedException");
		}
	}
}