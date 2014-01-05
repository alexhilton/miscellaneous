/**
 * 
 */
package exercises.threads.basic;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class InheritThread extends Thread {
	 private int countDown = 5;
	 private static int threadCount = 0;
	 public InheritThread() {
		 super(Integer.toString(++threadCount));
		 start();
	 }
	 
	 public String toString() {
		 return " # " + getName() + "(" + countDown + "), ";
	 }
	 
	 public void run() {
		 while (true) {
			 System.out.print(this);
			 if (--countDown == 0) {
				 return;
			 }
		 }
	 }
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		for (int i = 0; i < 5; i++) {
			new InheritThread();
			System.out.println();
		}
	}

}
