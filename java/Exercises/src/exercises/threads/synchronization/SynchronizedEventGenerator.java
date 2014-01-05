/**
 * 
 */
package exercises.threads.synchronization;

/**
 * @author gongzhihui
 *
 */
public class SynchronizedEventGenerator extends IntGenerator {
	private int currentEventValue = 0;
	/* (non-Javadoc)
	 * @see exercises.threads.synchronization.IntGenerator#next()
	 */
	@Override
	public synchronized int next() {
		// TODO Auto-generated method stub
		this.currentEventValue++;
		Thread.yield();
		this.currentEventValue++;
		return this.currentEventValue;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		EventChecker.test(new SynchronizedEventGenerator());
	}

}
