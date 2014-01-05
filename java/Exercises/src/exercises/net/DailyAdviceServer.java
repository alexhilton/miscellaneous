/**
 * 
 */
package exercises.net;
import java.net.*;
import java.io.*;
/**
 * @author gongzhihui
 *
 */
public class DailyAdviceServer {
	private String[] adviceList = {
			"Take smaller bites", // 0
			"Go for the tight jeans. No they do not make you look fat", // 1
			"One word: inappropriate", // 2 
			"Just for today, be honest. Tell your boss what you really think", // 3
			"You might want to rethink that haircut" // 4
	};
	
	public void go() {
		try {
			ServerSocket serverSock = new ServerSocket(4242);
			while (true) {
				Socket sock = serverSock.accept();
				
				PrintWriter writer  = new PrintWriter(sock.getOutputStream());
				String advice = getAdvice();
				writer.println(advice);
				writer.close();
				System.out.println(advice);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private String getAdvice() {
		int random = (int) (Math.random() * adviceList.length);
		return adviceList[random];
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DailyAdviceServer server = new DailyAdviceServer();
		server.go();
	}

}
