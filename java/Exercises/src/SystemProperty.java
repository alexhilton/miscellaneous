/**
 * 
 */
import java.io.*;
/**
 *
 */
public class SystemProperty {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println(System.getProperty("user.name"));
		System.out.println(System.getProperty("user.home"));
		String userHome = "/usr/include/sys/types";
		String[] tmp = userHome.split("/");
		for (String t : tmp) {
			System.out.println(t);
		}
		System.out.println(System.getProperty("user.dir"));
		System.out.println(System.getProperty("os.name"));
		System.out.println(System.getProperty("os.version"));
		String str = "Alex Hilton\n";
		System.out.println("where is '\\n': " + str.indexOf("\n"));
//		System.out.println(false || true && true || false);
		createArray();
		long start = System.currentTimeMillis();
		File log = new File( "C:\\obex-cli.log");
		if (log.exists() && log.length() > 512 * 1024) {
			log.delete();
		}
		long end = System.currentTimeMillis();
		System.out.println("deleting obex-cli.log takes: " + (double) (end - start) / 1000.0F + " seconds");
	}
	
	static void createArray() {
		int[] a = new int[ 10 ];
		for (int i = 0; i < a.length; i++) {
			a[i] += 4;
		}
		useArray(a);
	}
	
	static void useArray(int[] a) {
		for (int i : a) {
			System.out.print(i + " ");
		}
		System.out.println();
	}
}
