/**
 * 
 */
package exercises.gui.components;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * @author gongzhihui
 *
 */
public class TextAreaTest {
	JFrame frame;
	JPanel panel;
	JButton click;
	JLabel tag;
	JTextArea area;
	JScrollPane scroll;
	
	public void go() {
		frame = new JFrame();
		panel = new JPanel();
		click = new JButton("Click on me!");
		tag = new JLabel("the result will be displayed here!");
		area = new JTextArea(10, 40);
		scroll = new JScrollPane(area);
		scroll.setAutoscrolls(true);
		scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		click.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				area.append("You've just clicked on me!\n");
			}
		});
		panel.add(tag);
		panel.add(scroll);
		panel.add(click);
		frame.add(panel);
		frame.setSize(480, 320);
		frame.setTitle("TextAreaTest");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TextAreaTest gui = new TextAreaTest();
		gui.go();
	}

}
