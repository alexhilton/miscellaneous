/**
 * 
 */
package exercises.threads.interrupt;
import java.net.*;
import java.nio.*;
import java.nio.channels.*;
import java.io.*;
import java.util.concurrent.*;
import java.util.*;
/**
 * @author gongzhihui
 * It is said that the java.nio.* APIs are able to be interrupted when they are blocked.
 */
public class NIOInterruption {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ExecutorService exec = Executors.newCachedThreadPool();
		try {
			ServerSocket server = new ServerSocket(8080);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		InetSocketAddress isa = new InetSocketAddress("localhost", 8080);
		try {
			SocketChannel sc1 = SocketChannel.open(isa);
			SocketChannel sc2 = SocketChannel.open(isa);
			Future<?> f = exec.submit(new NIOBlocked(sc1));
			exec.execute(new NIOBlocked(sc2));
			exec.shutdown();
			TimeUnit.SECONDS.sleep(1);
			f.cancel(true);
			TimeUnit.SECONDS.sleep(1);
			sc1.close();
			sc2.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace(); 
		}
	}

}

class NIOBlocked implements Runnable {
	private final SocketChannel sc;
	public NIOBlocked(SocketChannel sc) {
		this.sc = sc;
	}
	public void run() {
		try {
			System.out.println("waiting for read() in " + this);
			sc.read(ByteBuffer.allocate(1));
		} catch (ClosedByInterruptException e) {
			System.out.println("closed by interrupted exception e");
		} catch (AsynchronousCloseException e) {
			System.out.println("asynchronous close exception");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		System.out.println("exiting nio blocked run() "  + this);
	}
}