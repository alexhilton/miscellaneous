/**
 * 
 */
package exercises.threads.interrupt;
import java.io.*;
import java.util.concurrent.*;

/**
 * @author gongzhihui
 *
 */
public class Interrupting {
	private static ExecutorService exec = Executors.newCachedThreadPool();
	static void test(Runnable r) throws InterruptedException {
		Future<?> f = exec.submit(r);
		TimeUnit.MICROSECONDS.sleep(100);
		System.out.println("interrupting " + r.getClass().getName());
		f.cancel(true);
		System.out.println("Interrupt sent to " + r.getClass().getName());
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			test(new SleepBlocked());
			test(new IOBlocked(System.in));
			test(new SynchronizedBlocked());
			TimeUnit.SECONDS.sleep(3);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("aborting with system.exit(0)");
		System.exit(0);
	}

}

// make a thread blocked by sleeping
class SleepBlocked implements Runnable {
	public void run() {
		try {
			/*
			 * we sleep long enough to make it easy to interrupt this thread.
			 */
			TimeUnit.SECONDS.sleep(100);
		} catch (InterruptedException e) {
			System.out.println("InterruptedException");
		}
		System.out.println("exiting sleep blocked. run()");
	}
}

// make a thread blocked by IO
class IOBlocked implements Runnable {
	private InputStream in;
	public IOBlocked(InputStream is) {
		this.in = is;
	}
	
	public void run() {
		try {
			System.out.println("waiting for read():");
			in.read();
		} catch (IOException e) {
			if (Thread.currentThread().isInterrupted()) {
				System.out.println("interrupted from blocked io");
			} else {
				throw new RuntimeException(e);
			}
		}
		System.out.println("exiting io blocked run()");
	}
}

// make a thread blocked by syncrhonization
class SynchronizedBlocked implements Runnable {
	public synchronized void f() {
		while (true) {
			Thread.yield();
		}
	}
	
	public SynchronizedBlocked() {
		new Thread() {
			public void run() {
				f(); // Lock acquired
			}
		}.start();
	}
	
	public void run() {
		System.out.println("Trying to call f()");
		f();
		System.out.println("exiting synchronizedblocked run()");
	}
}