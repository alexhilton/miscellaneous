// package headfirst.thread;

/**
 * run multi tasks through a single thread.
 */
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

public class SingleThreadMultiTask implements Runnable {
    private int count;
    public SingleThreadMultiTask(int count) {
	this.count = count;
    }
    public SingleThreadMultiTask() {}
    public void startRun() {
	ExecutorService exec = Executors.newSingleThreadExecutor();
	exec.submit(this);
	exec.shutdown();
    }
    public void run() {
	while (count-- > 0) {
	    System.out.println("counting down..." + count);
	}
	System.out.println("#########Fire###########");
    }
    public void setCount(int count) {
	this.count = count;
    }
    public static void main(String[] args) {
	SingleThreadMultiTask rocket = new SingleThreadMultiTask();
	for (int i = 0; i < 5; i++) {
	    rocket.setCount(5);
	    rocket.startRun();
	    try {	    
		Thread.sleep(100);
	    } catch (InterruptedException e) {
		e.printStackTrace();
	    }
	}
	System.out.println("All rockets have been fired...");
    }
}
