/**
 * 
 */
package exercises.innerclass;

/**
 * @author gongzhihui
 *
 */
public class CallbackDemo {
	public void action(DoSomething d, String what) {
		d.doSomething(what);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DoSomething d = new DoSomething() {
			public void doSomething(String what) {
				System.out.println(what);
			}
		};
		CallbackDemo callback = new CallbackDemo();
		callback.action(d, "Bake a cake");
	}

}


interface DoSomething {
	public void doSomething(String what);
}