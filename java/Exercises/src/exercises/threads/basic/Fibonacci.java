package exercises.threads.basic;


import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.ArrayList;
import java.util.concurrent.Future;
import java.util.concurrent.ExecutionException;
/**
 * 
 */

/**
 * @author gongzhihui
 *
 */
public class Fibonacci implements Callable<Integer> {
	private int n;
	public Fibonacci(int n) {
		this.n = n;
	}
	public Fibonacci() {
		this.n = 30;
	}
	/* (non-Javadoc)
	 * @see java.util.concurrent.Callable#call()
	 */
	public Integer call() throws Exception {
		Integer sum = 0;
		Integer f1 = 1;
		Integer f0 = 1;
		// TODO Auto-generated method stub
		for (int i = 0; i < n; i++) {
			sum = f1 + f0;
			f0 = f1;
			f1 = sum;
		}
		return sum;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		ArrayList<Future<Integer>> results = new ArrayList<Future<Integer>>();
		for (int i = 10; i < 20; i++) {
			results.add(exec.submit(new Fibonacci(i)));
		}
		System.out.println("Printing out resutls...");
		for (Future<Integer> fs : results) {
			try {
				System.out.println(fs.get());
			} catch (InterruptedException e) {
				System.out.println(e);
				return;
			} catch (ExecutionException e) {
				System.out.println(e);
			} finally {
				exec.shutdown();
			}
		}
	}

}
