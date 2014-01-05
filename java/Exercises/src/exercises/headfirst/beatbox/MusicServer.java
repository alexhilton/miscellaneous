/*
 * #(@) MusicServer
 * Alex Hilton
 * (c) Copyright Alex Hilton, All rights reserved 
 */
package exercises.headfirst.beatbox;
import java.io.*;
import java.net.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
/*
 * MusicServer
 * #(@) Version History:
 * 		#Dec 31 2009
 * 			Build up the program
 */
public class MusicServer {
	/** communication cables between clients */
	private ArrayList<ObjectOutputStream> clientOutputStream;
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new MusicServer().go();
	}
	
	private class ClientHandler implements Runnable {
		private ObjectInputStream ois;
		private Socket clientSocket;
		
		public ClientHandler(Socket socket) {
			try {
				clientSocket = socket;
				ois = new ObjectInputStream(clientSocket.getInputStream());
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		
		public void run() {
			Object obj2 = null;
			Object obj1 = null;
			try {
				while ((obj1 = ois.readObject()) != null) {
					obj2 = ois.readObject();
					
					System.out.println("got two objects");
					tellEveryone(obj1, obj2);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
	
	public void go() {
		clientOutputStream = new ArrayList<ObjectOutputStream>();
		try {
			ServerSocket serverSocket = new ServerSocket(8888);
			
			while (true) {
				Socket clientSocket = serverSocket.accept();
				ObjectOutputStream oos = 
						new ObjectOutputStream(clientSocket.getOutputStream());
				clientOutputStream.add(oos);
				
				Thread handler = new Thread(new ClientHandler(clientSocket));
				handler.start();
				
				System.out.println("got a connection");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * TODO: we should not send message to ourselves, the client should add its
	 * message into its screen, not from server
	 */
	public void tellEveryone(Object one, Object two) {
		try {
			for (ObjectOutputStream oos : clientOutputStream) {
				oos.writeObject(one);
				oos.writeObject(two);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
