/**
 * 
 */
package exercises.threads.threadexception;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class CaptureUncaughtException {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		 * It seems that pass HandlerThreadFactory to Executors.newCachedThreadPool's
		 * constructor is useless.
		 */
//		ExecutorService exec = Executors.newCachedThreadPool(
//				new HandlerThreadFactory());
		ExecutorService exec = Executors.newCachedThreadPool();
		Thread.setDefaultUncaughtExceptionHandler(new MyUncaughtExceptionHandler());
		exec.execute(new ExceptionThread2());
	}

}

class ExceptionThread2 implements Runnable {
	public void run() {
		Thread t = Thread.currentThread();
		System.out.println("run() by " + t);
		System.out.println("eh = " + t.getUncaughtExceptionHandler());
		throw new RuntimeException();
	}
}

class MyUncaughtExceptionHandler implements Thread.UncaughtExceptionHandler {
	public void uncaughtException(Thread t, Throwable e) {
		System.out.println("caught: " + e);
	}
}

class HandlerThreadFactory implements ThreadFactory {
	public Thread newThread(Runnable r) {
		System.out.println(this + " creating new thread");
		Thread t = new Thread();
		System.out.println("created " + t);
		t.setUncaughtExceptionHandler(new MyUncaughtExceptionHandler());
		System.out.println("eh = " + t.getUncaughtExceptionHandler());
		return t;
	}
}