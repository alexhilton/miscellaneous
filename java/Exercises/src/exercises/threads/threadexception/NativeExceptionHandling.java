/**
 * 
 */
package exercises.threads.threadexception;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class NativeExceptionHandling {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			ExecutorService exec = Executors.newCachedThreadPool();
			exec.execute(new ExceptionThread());
		} catch (RuntimeException e) {
			System.out.println(e.getMessage());
		}
	}

}
