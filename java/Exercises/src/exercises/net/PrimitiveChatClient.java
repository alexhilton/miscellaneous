/**
 * 
 */
package exercises.net;
import java.io.*;
import java.net.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/**
 * @author gongzhihui
 *
 */
public class PrimitiveChatClient {
	private JFrame frame;
	private Socket sock;
	private PrintWriter writer;
	private JTextField edit;
	
	public void setVisible(boolean visible) {
		frame.setVisible(visible);
	}
	
	public void go() {
		frame = new JFrame("Primitive Chat Client");
		frame.setSize(new Dimension(400, 100));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		edit = new JTextField(25);
		setupNetwork();
		JButton send = new JButton("Send");
		send.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				try {
					if (edit == null || edit.getText().equals("")) {
						return;
					}
					writer.println(edit.getText());
					writer.flush();
				} catch (Exception e) {
					e.printStackTrace();
				}
				edit.setText("");
				edit.requestFocus();
			}
		});
		panel.add(edit);
		panel.add(send);
		frame.add(panel);
	}
	
	private void setupNetwork() {
		try {
			sock = new Socket("127.0.0.1", 5000);
			writer = new PrintWriter(sock.getOutputStream());
			System.out.println("Connection established");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PrimitiveChatClient client = new PrimitiveChatClient();
		client.go();
		client.setVisible(true);
	}

}
