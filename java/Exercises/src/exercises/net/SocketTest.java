/**
 * 
 */
package exercises.net;
import java.io.*;
import java.net.*;
import java.util.*;
/**
 * This program makes a socket connection to the atomic clock in Boulder, Colorado,
 * and prints the time that the server sends.
 * @author gongzhihui
 *
 */
public class SocketTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			Socket sock = new Socket("time-A.timefreq.bldrdoc.gov", 13);
			try {
				InputStream in = sock.getInputStream();
				Scanner scan = new Scanner(in);
				
				while (scan.hasNextLine()) {
					String line = scan.nextLine();
					System.out.println(line);
				}
			} finally {
				sock.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
