/**
 * 
 */
package exercises.threads.newclasses;
import java.util.*;
import java.util.concurrent.*;
/**
 * @author gongzhihui
 *
 */
public class HorseRace {
	static final int FINISH_LINE = 75;
	private List<Horse> horses = new ArrayList<Horse>();
	private ExecutorService exec = Executors.newCachedThreadPool();
	private CyclicBarrier barrier;
	
	public HorseRace(int nhorses, final int pause) {
		barrier = new CyclicBarrier(nhorses, new Runnable() {
			public void run() {
				StringBuilder s = new StringBuilder();
				for (int i = 0; i < FINISH_LINE; i++) {
					s.append("=");
				}
				System.out.println(s);
				for (Horse h : horses) {
					System.out.println(h.tracks());
				}
				
				for (Horse h : horses) {
					if (h.getStrides() >= FINISH_LINE) {
						System.out.println(h + " won!");
						exec.shutdownNow();
						return;
					}
				}
				
				try {
					TimeUnit.MILLISECONDS.sleep(pause);
				} catch (InterruptedException e) {
					System.out.println("barrier-action sleep interrupted");
				}
			}
		});
		
		for (int i = 0; i < nhorses; i++) {
			Horse horse = new Horse(barrier);
			horses.add(horse);
			exec.execute(horse);
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int nhorses = 7;
		int pause = 200;
		if (args.length > 0) {
			int n = new Integer(args[0]);
			nhorses = n > 0 ? n : nhorses;
		}
		if (args.length > 1) {
			int p = new Integer(args[1]);
			pause = p > 0 ? p : pause;
		}
		
		new HorseRace(nhorses, pause);
	}

}

class Horse implements Runnable {
	private static int counter = 0;
	private final int id = counter++;
	private int strides = 0;
	private static Random rand = new Random(47);
	private static CyclicBarrier barrier;
	public Horse(CyclicBarrier b) {
		this.barrier = b;
	}
	
	public synchronized int getStrides() {
		return this.strides;
	}
	
	public void run() {
		try {
			while (!Thread.interrupted()) {
				synchronized (this) {
					strides += rand.nextInt(3);
				}
				barrier.await();
			}
		} catch (InterruptedException e) {
			// let it be
		} catch (BrokenBarrierException e) {
			throw new RuntimeException(e);
		}
	}
	
	public String toString() {
		return "Horse " + id + " ";
	}
	
	public String tracks() {
		StringBuilder s = new StringBuilder();
		for (int i = 0; i < getStrides(); i++) {
			s.append("*");
		}
		s.append(id);
		return s.toString();
	}
}