/**
 * 
 */
package exercises.threads.cooperating;
import java.util.concurrent.*;
import java.io.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class PipedIO {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Sender sender = new Sender();
		Receiver receiver = null;
		try {
			receiver = new Receiver(sender);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		ExecutorService exec = Executors.newCachedThreadPool();
		exec.execute(sender);
		exec.execute(receiver);
		try {
			TimeUnit.SECONDS.sleep(5);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		exec.shutdownNow();
	}

}


class Sender implements Runnable {
	private Random rand = new Random(47);
	private PipedWriter out = new PipedWriter();
	public PipedWriter getPipedWriter() {
		return out;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				for (char ch = 'A'; ch <= 'z'; ch++) {
					out.write(ch);
					TimeUnit.MILLISECONDS.sleep(rand.nextInt(500));
				}
			}
		} catch (IOException e) {
			System.out.println(e + " Sender write exception");
		} catch (InterruptedException e) {
			System.out.println(e + " sender sleep exception");
		}
	}
}

class Receiver implements Runnable {
	private PipedReader in;
	public Receiver(Sender sender) throws IOException {
		in = new PipedReader(sender.getPipedWriter());
	}
	
	public void run() {
		try {
			while (true) {
				System.out.print("Read: " + (char) in.read() + ", ");
			}
		} catch (IOException e) {
			System.out.println(e + " Receiver read exception");
		}
	}
}