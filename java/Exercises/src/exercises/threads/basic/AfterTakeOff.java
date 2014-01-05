package exercises.threads.basic;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.ExecutionException;
import java.util.ArrayList;

public class AfterTakeOff implements Callable<String> {
	private int id;
	public AfterTakeOff(int id) {
		this.id = id;
	}
	public String call() throws Exception {
		// TODO Auto-generated method stub
		return "result of AfterTakeOff: " + id;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		ArrayList<Future<String>> results = new ArrayList<Future<String>>();
		for (int i = 0; i < 10; i++) {
			results.add(exec.submit(new AfterTakeOff(i)));
		}
		for (Future<String> fs : results) {
			try {
				System.out.println(fs.get());
			} catch (InterruptedException e) {
				System.out.println(e);
				return;
			} catch (ExecutionException e) {
				System.out.println(e);
				return;
			} finally {
				exec.shutdown();
			}
		}
	}

}
