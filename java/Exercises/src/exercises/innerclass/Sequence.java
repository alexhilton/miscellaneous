/**
 * 
 */
package exercises.innerclass;

/**
 * @author gongzhihui
 *
 */
public class Sequence {
	private Object[] items;
	private int next = 0;
	public Sequence(int size) {
		items = new Object[size];
	}
	
	public void add(Object x) {
		if (next < items.length) {
			items[next++] = x;
		}
	}
	
	/**
	 * Bullet point: inner class is able to access the outer class's instance variables.
	 * @author gongzhihui
	 *
	 */
	private class SequenceSelector implements Selector {
		private int i  = 0;
		public boolean end() {
			return i == items.length;
		}
		public Object current() {
			return items[i];
		}
		public void next() {
			if ( i < items.length) {
				i++;
			}
		}
		
	}
	public Selector selector() {
		return new SequenceSelector();
	}
		
		
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Sequence sequence = new Sequence(10);
		for (int i = 0; i < 10; i++) {
			sequence.add(Integer.toString(i));
		}
		Selector selector = sequence.selector();
		while (!selector.end()) {
			System.out.print(selector.current() + "  ");
			selector.next();
		}
	}

}


interface Selector {
	public boolean end();
	public Object current();
	public void next();
}