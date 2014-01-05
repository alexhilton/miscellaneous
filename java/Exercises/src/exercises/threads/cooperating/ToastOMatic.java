/**
 * 
 */
package exercises.threads.cooperating;
import java.util.*;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class ToastOMatic {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ToastQueue dryQueue = new ToastQueue();
		ToastQueue butteredQueue = new ToastQueue();
		ToastQueue finishedQueue = new ToastQueue();
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(new Toaster(dryQueue));
		exec.execute(new Butterer(dryQueue, butteredQueue));
		exec.execute(new Jammer(butteredQueue, finishedQueue));
		exec.execute(new Eater(finishedQueue));
		try {
			TimeUnit.SECONDS.sleep(5);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		exec.shutdownNow();
		
	}

}

class Toast {
	public enum Status {
		DRY,
		BUTTERED,
		JAMMED
	};
	private Status status = Status.DRY;
	
	private final int id;
	
	public Toast(int id) {
		this.id = id;
	}
	
	public void butter() {
		status = Status.BUTTERED;
	}
	
	public void jam() {
		status = Status.JAMMED;
	}
	
	public Status getStatus() {
		return status;
	}
	
	public int getId() {
		return id;
	}
	
	public String toString() {
		return "Toast " + id + ": " + status;
	}
}

class ToastQueue extends LinkedBlockingQueue<Toast> {}

class Toaster implements Runnable {
	private ToastQueue toastQueue;
	private int count = 0;
	private Random rand = new Random(47);
	public Toaster(ToastQueue q) {
		toastQueue = q;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				TimeUnit.MILLISECONDS.sleep(100 + rand.nextInt(500));
				Toast t = new Toast(count++);
				System.out.println(t);
				toastQueue.put(t);
			}
		} catch (InterruptedException e) {
			System.out.println("Toaster interrupted");
		}
		System.out.println("Toaster off");
	}
}

class Butterer implements Runnable {
	private ToastQueue dryQueue, butterQueue;
	public Butterer(ToastQueue dry, ToastQueue butter) {
		this.dryQueue = dry;
		this.butterQueue = butter;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				// 
				Toast t = dryQueue.take();
				t.butter();
				System.out.println(t);
				butterQueue.put(t);
			}
		} catch (InterruptedException e) {
			System.out.println("Butterer off");
		}
	}
}

class Jammer implements Runnable {
	private ToastQueue butterQueue, jamQueue;
	public Jammer(ToastQueue butterQueue, ToastQueue jamQueue) {
		this.butterQueue = butterQueue;
		this.jamQueue = jamQueue;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				Toast t = butterQueue.take();
				t.jam();
				System.out.println(t);
				jamQueue.put(t);
			}
		} catch (InterruptedException e) {
			System.out.println("Jammer off");
		}
	}
}

class Eater implements Runnable {
	private ToastQueue finishedQueue;
	private int counter = 0;
	public Eater(ToastQueue finished) {
		this.finishedQueue = finished;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				Toast t = finishedQueue.take();
				if (t.getId() != counter++ || t.getStatus() != Toast.Status.JAMMED) {
					System.out.println(">>>>>Error: " + t);
					System.exit(0);
				} else {
					System.out.println("Chomp! " + t);
				}
			}
		} catch (InterruptedException e) {
			System.out.println("Eater interrupted");
		}
		System.out.println("Eater off");
	}
}