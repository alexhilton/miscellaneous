/**
 * 
 */
package exercises.threads.synchronization;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;
/**
 * @author gongzhihui
 *
 */
public class MutexEventGenerator extends IntGenerator {
	private int currentEventValue = 0;
	private Lock lock = new ReentrantLock();
	/* (non-Javadoc)
	 * @see exercises.threads.synchronization.IntGenerator#next()
	 */
	@Override
	public int next() {
		// TODO Auto-generated method stub
		lock.lock();
		try {
			this.currentEventValue++;
			Thread.yield();
			this.currentEventValue++;
			return this.currentEventValue;
		} finally {
			lock.unlock();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		EventChecker.test(new MutexEventGenerator());
	}

}
