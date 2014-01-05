package exercises.threads.basic;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 
 */

/**
 * @author gongzhihui
 *
 */
public class LiftOff implements Runnable {
	private int countDown = 10; 
	private static int taskCount = 0;
	private final int id = taskCount++;
	public LiftOff() {}
	public LiftOff(int countDown) {
		this.countDown = countDown;
	}
	
	public String status() {
		return "#" + id + "(" + (countDown > 0 ? countDown : "LiftOff!") + "). ";
	}
	
	
	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		while (countDown-- > 0) {
			System.out.print(status());
			Thread.yield();
		}
//		System.out.println();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		LiftOff launch = new LiftOff();
//		Thread t = new Thread(launch);
//		t.start();
//		try {
//			Thread.sleep(10);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//		for (int i = 0; i < 6; i++) {
//			new Thread(new LiftOff()).start();
//			try {
//				Thread.sleep(100);
//			} catch (InterruptedException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
//			System.out.println();
//		}
//		System.out.println("Waiting for LiftOff");
		ExecutorService exec = Executors.newCachedThreadPool();
		for (int i = 0; i < 5; i++) {
			exec.execute(new LiftOff());
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				// nothing
			}
			System.out.print('\n');
		}
		exec.shutdown();
		System.out.println("Waiting for lifting off....");
		
		exec = Executors.newFixedThreadPool(5);
		for (int i = 0; i < 5; i++) {
			exec.execute(new LiftOff());
//			try {
//				Thread.sleep(10);
//			} catch (InterruptedException e) {
//				// nothing
//			}
			System.out.print('\n');
		}
		exec.shutdown();
		System.out.println("Waiting for lifting off....");
		
		exec = Executors.newSingleThreadExecutor();
		for (int i = 0; i < 5; i++) {
			exec.execute(new LiftOff());
//			try {
//				Thread.sleep(10);
//			} catch (InterruptedException e) {
//				// nothing
//			}
			System.out.print('\n');
		}
		exec.shutdown();
		System.out.println("Waiting for lifting off....");
	}

}
