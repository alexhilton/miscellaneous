/**
 * 
 */
package exercises.net;
import java.io.*;
import java.net.*;
/**
 * @author gongzhihui
 *
 */
public class DailyAdviceClient {
	public void go() {
		try {
			Socket sock = new Socket("127.0.0.1", 4242);
			try {
				InputStreamReader inputReader = new InputStreamReader(sock.getInputStream());
				BufferedReader reader = new BufferedReader(inputReader);

				String advice = reader.readLine();
				System.out.println(advice);
				reader.close();
			} finally {
				sock.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DailyAdviceClient gui = new DailyAdviceClient();
		gui.go();
	}

}
