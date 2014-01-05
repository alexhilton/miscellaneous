package exercises.threads.basic;

/**
 * 
 */

/**
 * @author gongzhihui
 *
 */
public class TakeOff implements Runnable {
	public TakeOff() {
		System.out.println("We are ready to take off!");
	}
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		for (int i = 0; i < 3; i++) {
			System.out.println("Taking off, 3, 2, 1...");
			Thread.yield();
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for (int i = 0; i < 10; i++) {
			new Thread(new TakeOff()).start();
		}
		System.out.println("wating for taking off...");
		try {
			Thread.sleep(100);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
