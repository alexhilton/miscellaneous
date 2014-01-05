/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;
/**
 * @author gongzhihui
 *
 */
public class ExplicitCriticalSection {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PairManager pman1 = new ExplicitPairManager1();
		PairManager pman2 = new ExplicitPairManager2();
		CriticalSection.testApproaches(pman1, pman2);
	}

}

// synchronize the entrie method
class ExplicitPairManager1 extends PairManager {
	private Lock lock = new ReentrantLock();
	public synchronized void increment() {
		lock.lock();
		try {
			p.incrementX();
			p.incrementY();
			store(getPair());
		} finally {
			lock.unlock();
		}
	}
}

// use a critical section
class ExplicitPairManager2 extends PairManager {
	private Lock lock = new ReentrantLock();
	public void increment() {
		Pair tmp;
		lock.lock();
		try {
			p.incrementX();
			p.incrementY();
			tmp = getPair();
		} finally {
			lock.unlock();
		}
		store(tmp);
	}
}