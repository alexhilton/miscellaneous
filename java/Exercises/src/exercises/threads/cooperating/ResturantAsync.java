/**
 * 
 */
package exercises.threads.cooperating;

/**
 * @author gongzhihui
 *
 */
public class ResturantAsync {
	private String meal;
	private String table;
	private class Cook implements Runnable {
		public void run() {
			meal = new String("Humberger");
			System.out.println("Meal is ready");
		}
	}
	private class Waitor implements Runnable {
		public void run() {
			while (meal == null) {
				try {
					Thread.sleep(500);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			table = meal;
			System.out.println("Table is ready");
		}
	}
	
	private class Consumer implements Runnable {
		public void run() {
			while (table == null) {
				try {
					Thread.sleep(500);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			System.out.println("I can enjoy '" + table + "'");
		}
	}
	
	public void test() {
		new Thread(new Cook()).start();
		new Thread(new Waitor()).start();
		new Thread(new Consumer()).start();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new ResturantAsync().test();
	}

}
