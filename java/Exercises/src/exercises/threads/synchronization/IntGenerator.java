/**
 * 
 */
package exercises.threads.synchronization;

/**
 * @author gongzhihui
 *
 */
public abstract class IntGenerator {
	private volatile boolean cancelled = false;
	public abstract int next();
	public void cancel() {
		cancelled = true;
	}
	public boolean isCanceled() {
		return cancelled;
	}
}
