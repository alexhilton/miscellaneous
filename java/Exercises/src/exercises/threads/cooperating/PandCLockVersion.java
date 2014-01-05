package exercises.threads.cooperating;
import java.util.concurrent.locks.*;
public class PandCLockVersion {
	private String meal;
	private Lock mealLock = new ReentrantLock();
	// Condition must be protected by a lock
	private Condition mealCondition = mealLock.newCondition();
	
	private class Cook implements Runnable {
		public void run() {
			mealLock.lock();
			try {
				while (meal != null) {
					mealCondition.await();
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				mealLock.unlock();
			}
			meal = new String("Turkey");
			System.out.println("Meal is ready");
			mealLock.lock();
			mealCondition.signal();
			mealLock.unlock();
		}
	}
	
	private class Guest implements Runnable {
		public void run() {
			mealLock.lock();
			try {
				while (meal == null) {
					mealCondition.await();
				}
				System.out.println("I got meal:\n" + meal);
			} catch (InterruptedException e) {
				e.printStackTrace();
			} finally {
				mealLock.unlock();
			}
		}
	}
	
	public void test() {
		new Thread(new Cook()).start();
		new Thread(new Guest()).start();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new PandCLockVersion().test();
	}
}
