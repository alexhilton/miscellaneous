/**
 * 
 */
package exercises.interfaces;

/**
 * @author gongzhihui
 *
 */
public class TestParcel {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Parcel p = new Parcel();
		Contents c = p.contents();
		Destination d = p.destination("Alaska");
		System.out.println(c.value());
		System.out.println(d.readLabel());
	}

}

interface Destination {
	public String readLabel();
}

interface Contents {
	public int value();
}

class Parcel {
	private class PContents implements Contents {
		private int i = 11;
		public int value() {
			return i;
		}
	}
	protected class PDestination implements Destination {
		private String label;
		private PDestination(String w) {
			label = w;
		}
		public String readLabel() {
			return label;
		}
	}
	public Destination destination(String s) {
		return new PDestination(s);
	}
	
	public Contents contents() {
		return new PContents();
	}
}