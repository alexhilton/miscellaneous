/**
 * 
 */
package exercises.threads.cooperating;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;
/**
 * @author gongzhihui
 *
 */
public class WaxOMatic2 {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Car car = new Car();
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new WaxOff(car));
		exec.execute(new WaxOn(car));
		try {
			TimeUnit.SECONDS.sleep(5);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		exec.shutdownNow();
	}

}

class Car2 {
	private Lock lock = new ReentrantLock();
	private Condition condition = lock.newCondition();
	private boolean waxOn = false;
	
	public void waxed() {
		lock.lock();
		try {
			waxOn = true;
			condition.signalAll();
		} finally {
			lock.unlock();
		}
	}
	
	public void buffed() {
		lock.lock();
		try {
			waxOn = false;
			condition.signalAll();
		} finally {
			lock.unlock();
		}
	}
	
	public void waitForWaxing() throws InterruptedException {
		lock.lock();
		try {
			while (!waxOn) {
				condition.await();
			}
		} finally {
			lock.unlock();
		}
	}
	
	public void waitForBuffing() throws InterruptedException {
		lock.lock();
		try {
			while (waxOn) {
				condition.await();
			}
		} finally {
			lock.unlock();
		}
	}
}

class WaxOn2 implements Runnable {
	private Car car;
	public WaxOn2(Car c) {
		car  = c;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				System.out.print("Wax on!   \n");
				TimeUnit.MILLISECONDS.sleep(200);
				car.waxed();
				car.waitForBuffing();
			}
		} catch (InterruptedException e) {
			System.out.println("exiting via interruption");
		}
		System.out.println("ending wax on task");
	}
}

class WaxOff2 implements Runnable {
	private Car car;
	public WaxOff2(Car c) {
		this.car = c;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				car.waitForWaxing();
				System.out.print("wax off  \n");
				TimeUnit.MILLISECONDS.sleep(200);
				car.buffed();
			}
		} catch (InterruptedException e) {
			System.out.println("exiting vai interruption");
		}
		System.out.println("ending wax off task");
	}
}