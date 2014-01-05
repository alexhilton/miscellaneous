/**
 * 
 */
package exercises.threads.cooperating;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class WaxOMatic {
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
		exec.shutdown();
	}

}

class Car {
	private boolean waxOn = false; // whether there is wax on the car
	
	// the wax has been on the car.
	// wax is over
	public synchronized void waxed() {
		waxOn = true; // raedy to buff
		notifyAll();
	}
	
	// buff is over.
	public synchronized void buffed() {
		waxOn = false; // ready for another coat of wax
		notifyAll();
	}
	
	// need wax is on the car to continue
	public synchronized void waitForWaxing() throws InterruptedException {
		while (!waxOn) {
			wait();
		}
	}
	
	// need wax is not on the car to continue
	public synchronized void waitForBuffing() throws InterruptedException {
		while (waxOn) {
			wait();
		}
	}
}

// wax a car
class WaxOn implements Runnable {
	private Car car;
	public WaxOn(Car c) {
		this.car = c;
	}

	public void run() {
		try {
			while (!Thread.interrupted()) {
				System.out.println("Wax on, waxing!");
				TimeUnit.MILLISECONDS.sleep(200);
				car.waxed();
				car.waitForBuffing();
			}
		} catch (InterruptedException e) {
			System.out.println("Exiting via interrrupt");
		}
		System.out.println("Ending wax on task");
	}
}

// buff a car
class WaxOff implements Runnable {
	private Car car;
	public WaxOff(Car c) {
		this.car = c;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				car.waitForWaxing();
				System.out.println("Wax off");
				TimeUnit.MILLISECONDS.sleep(200);
				car.buffed();
			}
		} catch (InterruptedException e) {
			System.out.println("Exiting via interrupt");
		}
		System.out.println("Ending wax off task");
	}
}