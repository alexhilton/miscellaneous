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
public class TextFieldTest {
	JTextField text;
	JFrame frame;
	JPanel panel;
	JLabel tag;
	JScrollPane scroll;
	JTextArea area;
	public void go() {
		frame = new JFrame();
		panel = new JPanel();
		area = new JTextArea(5, 20);
		tag = new JLabel("Please input your name: ");
		text = new JTextField(20);
		panel.add(tag);
		/**
		 * we have add area on scroll, so panel add scroll is sufficient.
		 * we don't neet add area on panel any more.
		 */
		scroll = new JScrollPane(area);
		scroll.setAutoscrolls(true);
		scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		text.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				area.append(text.getText() + "\n");
				text.setText("");
			}
		});
		panel.setBackground(new Color(155, 155, 30));
		panel.add(text);
		panel.add(scroll);
		frame.add(panel);
		frame.setSize(480, 320);
		frame.setTitle("TextFieldTest");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TextFieldTest gui = new TextFieldTest();
		gui.go();
	}

}
