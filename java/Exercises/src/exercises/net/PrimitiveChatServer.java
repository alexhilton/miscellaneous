/*
 * PrimitiveChatServer
 * Alex Hilton
 * Dec 28 2009
 * (c) copyright Alex Hilton, All right reserved.
 */
package exercises.net;
import java.io.*;
import java.util.*;
import java.net.*;
/**
 * <code>PrimitiveChatServer</code>
 * 
 */
public class PrimitiveChatServer {
	private ArrayList clientOutputStreams;
	
	private class ClientHandler implements Runnable {
		private BufferedReader reader;
		private Socket socket;
		
		public ClientHandler(Socket clientSocket) {
			socket = clientSocket;
			try {
				InputStreamReader streamReader = 
					new InputStreamReader(socket.getInputStream());
				reader = new BufferedReader(streamReader);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		public void run() {
			String message;
			try {
				while (reader != null 
						&& (message = reader.readLine()) != null) {
					System.out.println("get message: " + message);
					tellEveryone(message);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	public void go() {
		clientOutputStreams = new ArrayList();
		try {
			ServerSocket serverSocket = new ServerSocket(8080);
			
			while (true) {
				Socket clientSocket = serverSocket.accept();
				PrintWriter writer = 
					new PrintWriter(clientSocket.getOutputStream());
				clientOutputStreams.add(writer);
				
				Thread worker = new Thread(new ClientHandler(clientSocket));
				worker.start();
				System.out.println("Got a connection request");
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void tellEveryone(String message) {
		Iterator it = clientOutputStreams.iterator();
		while (it.hasNext()) {
			try {
				PrintWriter writer = (PrintWriter) it.next();
				writer.println(message);
				writer.flush();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PrimitiveChatServer server = new PrimitiveChatServer();
		server.go();
	}

}
