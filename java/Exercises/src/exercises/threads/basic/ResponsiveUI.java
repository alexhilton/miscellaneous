/**
 * 
 */
package exercises.threads.basic;
import java.io.IOException;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class ResponsiveUI extends Thread {
	private static volatile double d = 1;
	public ResponsiveUI() {
		setDaemon(true);
		start();
	}
	
	public void run() {
		while (true) {
			d = d + (Math.PI + Math.E) / d;
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		 * for the unreponsiveUI you have to kill the process to stop the program.
		 */
//		try {
//			new UnresponsiveUI();
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
		new ResponsiveUI();
		try {
			System.in.read();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println(d);
	}

}

class UnresponsiveUI {
	private volatile double d  = 1;
	public UnresponsiveUI() throws Exception {
		while (d > 0) {
			d = d + (Math.PI + Math.E) / d;
		}
		System.in.read();
	}
}