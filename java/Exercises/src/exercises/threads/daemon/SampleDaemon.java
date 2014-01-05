package exercises.threads.daemon;

/**
 * 
 */
import java.util.concurrent.TimeUnit;
/**
 * @author gongzhihui
 *
 */
public class SampleDaemon implements Runnable {
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		try {
			while (true) {
				TimeUnit.MICROSECONDS.sleep(100);
				System.out.println(Thread.currentThread() + " " + this);
			}
		} catch (InterruptedException e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for (int i = 0; i < 10; i++) {
			Thread daemon = new Thread(new SampleDaemon());
			daemon.setDaemon(true);
			daemon.start();
		}
		System.out.println("All daemons started!!!");
		try {
			TimeUnit.MICROSECONDS.sleep(175);
		} catch (InterruptedException e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
	}

}
