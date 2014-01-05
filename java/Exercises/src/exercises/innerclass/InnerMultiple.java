/**
 * 
 */
package exercises.innerclass;

/**
 * @author gongzhihui
 *
 */
public class InnerMultiple {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Parcel1 p1 = new Parcel1();
		System.out.println(p1.value());
		System.out.println(p1.readLabel());
		
		System.out.println("Anonymous inner class implements interfaces");
		Parcel2 p2 = new Parcel2();
		p2.print();
	}

}

class Parcel1 implements Destination, Contents {
	private String s = "Detroit Piston";
	private int i = 101;
	public String readLabel() {
		return s;
	}
	public int value() {
		return i;
	}
}

class Parcel2 {
	public Contents contents() {
		return new Contents() {
			int i = 1001;
			public int value() {
				return i;
			}
		};
	}
	
	private void printContents(Contents con) {
		System.out.println(con.value());
	}
	public void print() {
		printContents(new Contents() {
			int i = 1010101;
			public int value() {
				return i;
			}
		});
		printDestination(new Destination() {
			String d = "Boston Celtics";
			public String readLabel() {
				return d;
			}
		});
	}
	private void printDestination(Destination dest) {
		System.out.println(dest.readLabel());
	}
	public Destination destination() {
		return new Destination() {
			String d = "Boston";
			public String readLabel() {
				return d;
			}
		};
	}
	
}