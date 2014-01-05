/*
 * SimpleChatClient
 * Alex Hilton
 * Dec 28 2009
 * (c) Copyright Alex Hilton, all rights reserved 
 */
package exercises.net;
import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
/**
 * Client side of a very simple chat application. 
 * @author gongzhihui
 */
public class SimpleChatClient {
	/** Main window */
	private JFrame mainWindow;
	/** Where user input messages */
	private JTextField edit;
	/** show the contents of chatting, sent and received messages */
	private JTextArea textview;
	/** to connect server */
	private Socket sock;
	private PrintWriter writer;
	private BufferedReader reader;
	private String nickName;
	
	public SimpleChatClient() {
		this.nickName = System.getProperty("user.name");
	}
	
	public SimpleChatClient(String nickName) {
		this.nickName = nickName;
	}
	
	public void go() {
		mainWindow = new JFrame("Simple Chat Client");
		mainWindow.setSize(new Dimension(400, 300));
		mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		edit = new JTextField(25);
		textview = new JTextArea(10, 30);
		textview.setEditable(false);
		textview.setLineWrap(true);
		textview.setWrapStyleWord(true);
		Font defaultFont = new Font("sanserif", Font.BOLD, 14);
		textview.setFont(defaultFont);
		JScrollPane textScroll = new JScrollPane(textview);
		textScroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		textScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

		setupConnection();
		JButton send = new JButton("Send");
		send.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				try {
					// We don't allow to send empty message
					if (edit.getText().equals("")) {
						JOptionPane.showMessageDialog(mainWindow, "You cannot send empty message");
						return;
					}
					
					writer.println(edit.getText());
					writer.flush();
					

					textview.append(nickName + ": " + edit.getText() + "\n");
				} catch (Exception e ) {
					e.printStackTrace();
				}
				
				edit.setText("");
				edit.requestFocus();
			}
		});
		
		/*
		 * We need a thread to receiving messages from server 
		 */
		Thread receiver = new Thread(new Runnable() {
			public void run() {
				String message;
				try {
					while (reader != null && (message = reader.readLine()) != null) {
						System.out.println("read " + message);
						textview.append("Receive: " + message + "\n");
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		receiver.start();
		
		panel.add(textScroll);
		panel.add(edit);
		panel.add(send);
		
		mainWindow.add(panel);
	}
	
	public void setNickName(String nickName) {
		this.nickName = nickName;
	}
	
	public void setVisible(boolean visible) {
		mainWindow.setVisible(visible);
	}
	
	private void setupConnection() {
		try {
			sock = new Socket("127.0.0.1", 8080);
			InputStreamReader streamReader = new InputStreamReader(sock.getInputStream());
			reader = new BufferedReader(streamReader);
			writer = new PrintWriter(sock.getOutputStream());
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println("connection established");
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SimpleChatClient client = new SimpleChatClient("alex");
		client.go();
		client.setVisible(true);
	}

}
