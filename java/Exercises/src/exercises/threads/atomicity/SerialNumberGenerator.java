/**
 * 
 */
package exercises.threads.atomicity;

/**
 * @author gongzhihui
 *
 */
public class SerialNumberGenerator {
	private static volatile int serialNumber = 0;
	public static int nextSerialNumber() {
		return serialNumber++;
	}
}
