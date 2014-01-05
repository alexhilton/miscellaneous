/**
 * 
 */
package exercises.threads.daemon;

import java.util.concurrent.ThreadFactory;

/**
 * @author gongzhihui
 *
 */
public class DaemonThreadFactory implements ThreadFactory {

	/* (non-Javadoc)
	 * @see java.util.concurrent.ThreadFactory#newThread(java.lang.Runnable)
	 */
	public Thread newThread(Runnable arg0) {
		// TODO Auto-generated method stub
		Thread t = new Thread(arg0);
		t.setDaemon(true);
		return t;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
