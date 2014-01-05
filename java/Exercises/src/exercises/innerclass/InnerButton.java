/**
 * 
 */
package exercises.innerclass;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/**
 * @author gongzhihui
 *
 */
public class InnerButton {
	JFrame frame = new JFrame();
	JPanel panel = new JPanel();
	public void show() {
		frame.setSize(400, 300);
		frame.setTitle("InnerButton");
		JButton color = new JButton("Ok");
		color.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				panel.setBackground(Color.blue);
			}
		});
		JButton exit = new JButton("Exit");
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		panel.add(color);
		panel.add(exit);
		frame.add(panel);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		InnerButton iner = new InnerButton();
		iner.show();
	}	

}