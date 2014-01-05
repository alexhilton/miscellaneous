/**
 * 
 */
package exercises.threads.interrupt;
import java.net.*;
import java.util.concurrent.*;
import java.io.*;
/**
 * @author gongzhihui
 * Since you cannot interrupt the threads which are blocked by IO or locks.
 * But sometimes you do need to interrupt a thread, an alternative is to
 * shutdown all threads if necessary.
 */
public class CloseResource {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		ServerSocket server;
		InputStream socketInput = null;
		try {
			server = new ServerSocket(8080);
			socketInput = new Socket("localhost", 8080).getInputStream();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		exec.execute(new IOBlocked(socketInput));
		exec.execute(new IOBlocked(System.in));
		try {
			TimeUnit.MICROSECONDS.sleep(100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("shutting down all threads");
		exec.shutdownNow();
		try {
			TimeUnit.SECONDS.sleep(1);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("closing " + socketInput.getClass().getName());
		try {
			socketInput.close();
			TimeUnit.SECONDS.sleep(1);
			System.out.println("closing " + System.in.getClass().getName());
			System.in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
