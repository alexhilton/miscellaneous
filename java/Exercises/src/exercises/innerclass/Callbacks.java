/**
 * 
 */
package exercises.innerclass;

/**
 * @author gongzhihui
 *
 */
public class Callbacks {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Callee1 c1 = new Callee1();
		Callee2 c2 = new Callee2();
		MyIncrement.foo(c2);
		Caller caller1 = new Caller(c1);
		Caller caller2 = new Caller(c2.getCallbackReference());
		caller1.go();
		caller1.go();
		caller2.go();
		caller2.go();
	}

}

interface Incrementable {
	public void increment();
}

class Callee1 implements Incrementable {
	private int i = 0;
	public void increment() {
		i++;
		System.out.println("i = " + i);
	}
}

class MyIncrement {
	public void increment() {
		System.out.println("Other operations");
	}
	public static void foo(MyIncrement mi) {
		mi.increment();
	}
}

class Callee2 extends MyIncrement {
	private int i = 0;
	// override super class
	public void increment() {
		super.increment();
		i++;
		System.out.println("i = " + i);
	}
	/**
	 * inner class Closure implements interface
	 * it is a closure
	 * @author gongzhihui
	 *
	 */
	private class Closure implements Incrementable {
		public void increment() {
			Callee2.this.increment();
		}
	}
	Incrementable getCallbackReference() {
		return new Closure();
	}
}

class Caller {
	private Incrementable callbackReference;
	public Caller(Incrementable cbh) {
		callbackReference = cbh;
	}
	public void go() {
		callbackReference.increment();
	}
}