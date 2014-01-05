/**
 * 
 */
package exercises.threads.threadexception;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class ExceptionThread implements Runnable {

	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		throw new RuntimeException();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new ExceptionThread());
	}
}
