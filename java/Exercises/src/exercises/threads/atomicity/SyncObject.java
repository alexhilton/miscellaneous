/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class SyncObject {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		final DualSync ds = new DualSync();
		new Thread() {
			public void run() {
				ds.f();
			}
		}.start();
		ds.g();
	}

}

class DualSync {
	private Object syncObject = new Object();
	public synchronized void f() {
		for (int i = 0; i < 5; i++) {
			System.out.println("f()");
			Thread.yield();
		}
	}
	public void g() {
		synchronized (syncObject) {
			for (int i = 0; i < 5; i++) {
				System.out.println("g()");
				Thread.yield();
			}
		}
	}
}