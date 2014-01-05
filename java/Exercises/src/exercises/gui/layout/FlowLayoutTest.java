/**
 * 
 */
package exercises.gui.layout;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/**
 * @author gongzhihui
 *
 */
public class FlowLayoutTest {
	JFrame frame;
	JPanel panel;
	JButton one;
	JButton exit;
	JButton three;
	JButton four;
	public void go() {
		frame = new JFrame();
		panel = new JPanel();
		frame.setSize(480, 320);
		frame.setTitle("FlowLayoutTest");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		one = new JButton("shock me");
		exit = new JButton("exit");
		three = new JButton("Three");
		four = new JButton("Four");
		frame.setBackground(Color.blue);
		panel.setBackground(Color.darkGray);
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		panel.add(one);
		panel.add(exit);
		panel.add(three);
		panel.add(four);
		frame.getContentPane().add(BorderLayout.EAST, panel);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FlowLayoutTest gui = new FlowLayoutTest();
		gui.go();
	}

}
