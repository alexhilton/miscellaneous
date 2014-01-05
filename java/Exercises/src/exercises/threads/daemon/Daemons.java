/**
 * 
 */
package exercises.threads.daemon;
import java.util.concurrent.*;

/**
 * @author gongzhihui
 *
 */
public class Daemons {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Thread d = new Thread(new Daemon());
		d.setDaemon(true);
		d.start();
		System.out.println(" d.isDaemon() = " + d.isDaemon());
		try {
			TimeUnit.SECONDS.sleep(1);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}

class Daemon implements Runnable {
	private Thread[] t = new Thread[10];
	public void run() {
		for (int i = 0; i < t.length; i++) {
			t[ i ] = new Thread(new DaemonSpawn());
			t[ i ].start();
			System.out.println(" DaemonSpawn: " + i + " started. ");
		}
		for (int i = 0; i < t.length; i++) {
			System.out.println(" t[" + i + "].isDaemon() = "+ t[i].isDaemon() + ". ");
		}
		while (true) {
			Thread.yield();
		}
	}
}

class DaemonSpawn implements Runnable {
	public void run() {
		while (true) {
			Thread.yield();
		}
	}
}