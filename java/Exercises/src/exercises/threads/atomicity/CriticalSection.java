/**
 * 
 */
package exercises.threads.atomicity;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class CriticalSection {
	static void testApproaches(PairManager pman1, PairManager pman2) {
		ExecutorService exec = Executors.newCachedThreadPool();
		PairManipulator pm1 = new PairManipulator(pman1);
		PairManipulator pm2 = new PairManipulator(pman2);
		PairChecker pchck1 = new PairChecker(pman1);
		PairChecker pchck2 = new PairChecker(pman2);
		exec.execute(pm1);
		exec.execute(pm2);
		exec.execute(pchck1);
		exec.execute(pchck2);
		try {
			TimeUnit.MICROSECONDS.sleep(500);
		} catch (InterruptedException e) {
			System.out.println("sleep interrupted");
		}
		System.out.println("pm1: " + pm1 + "\npm2: " + pm2);
		System.exit(0);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PairManager pm1 = new PairManager1();
		PairManager pm2 = new PairManager2();
		testApproaches(pm1, pm2);
	}

}

class Pair { // not thread-safe
	private int x, y;
	public Pair(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public Pair() {
		this(0, 0);
	}
	public int getX() {
		return x;
	}
	public int getY() {
		return y;
	}
	public void incrementX() {
		x++;
	}
	public void incrementY() {
		y++;
	}
	public String toString() {
		return "x: " + x + ", y: " + y;
	}
	public class PairValueNotEqualException extends RuntimeException {
		public PairValueNotEqualException() {
			super("Pair values not equal: " + Pair.this);
		}
	}
	
	// Arbitrary invariant -- both variables must be equal
	public void checkState() {
		if (x != y) {
			throw new PairValueNotEqualException();
		}
	}
}

// protect a Pair inside a thread-safe class
abstract class PairManager {
	AtomicInteger checkCounter = new AtomicInteger(0);
	private List<Pair> storage = Collections.synchronizedList(new ArrayList<Pair>());
	protected Pair p = new Pair();
	public synchronized Pair getPair() {
		// make a copy to keep the original safe
		return new Pair(p.getX(), p.getY());
	}
	
	// assume this is a time consuming operation
	protected void store(Pair p) {
		storage.add(p);
		try {
			TimeUnit.MICROSECONDS.sleep(50);
		} catch (InterruptedException e) {
			//e.printStackTrace();
			// ignores it
		}
	}
	
	public abstract void increment();
}

// synchronize the entire method
class PairManager1 extends PairManager {
	public synchronized void increment() {
		p.incrementX();
		p.incrementY();
		store(getPair());
	}
}

// use a critical section
class PairManager2 extends PairManager {
	public void increment() {
		Pair tmp;
		synchronized(this) {
			p.incrementX();
			p.incrementY();
			tmp = getPair();
		}
		store(tmp);
	}
}

class PairManipulator implements Runnable {
	private PairManager pm;
	public PairManipulator(PairManager pm) {
		this.pm = pm;
	}
	
	public void run() {
		while (true) {
			pm.increment();
		}
	}
	
	public String toString() {
		return "Pair: " + pm.getPair() + " checkCounter = " + pm.checkCounter.get();
	}
}

class PairChecker implements Runnable {
	private PairManager pm;
	public PairChecker(PairManager pm) {
		this.pm = pm;
	}
	
	public void run() {
		while (true) {
			pm.checkCounter.incrementAndGet();
			pm.getPair().checkState();
		}
	}
}