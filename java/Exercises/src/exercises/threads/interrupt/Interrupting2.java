/**
 * 
 */
package exercises.threads.interrupt;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;
/**
 * @author gongzhihui
 *
 */
public class Interrupting2 {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Thread t = new Thread(new Blocked2());
		t.start();
		try {
			TimeUnit.SECONDS.sleep(1);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		/*
		 * ReentrantLock can be interrupted by Thread.interrupt(). That is the point.
		 */
		System.out.println("issuing t.interrupt()");
		t.interrupt();
	}

}

/*
 * BlockedMutex's contructor gets his own lock and never let it go. So any other
 * thread which tries to call f() will be blocked.
 */
class BlockedMutex {
	private Lock lock = new ReentrantLock();
	public BlockedMutex() {
		lock.lock(); // acquire its own's lock
	}
	
	public void f() {
		try {
			lock.lockInterruptibly();
			System.out.println("Lock acquired in f()");
		} catch (InterruptedException e) {
			System.out.println("Interrrupted from lock acquisition in f()");
		}
	}
}

class Blocked2 implements Runnable {
	BlockedMutex blocked = new BlockedMutex();
	public void run() {
		System.out.println("waiting for f() in blockedMutex()");
		blocked.f();
		System.out.println("broken out of blocked call");
	}
}