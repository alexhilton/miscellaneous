/**
 * implement an simple calculator
 */
package exercises.gui.components;

import javax.swing.JPanel;
import javax.swing.JFrame;
import java.awt.Dimension;

import javax.swing.ButtonGroup;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
/**
 * @author gongzhihui
 *
 */
public class Calculator {
	private final JFrame frame;
	private final JPanel northPanel;
	private JPanel centralPanel;
	private JTextField entry;
	private JButton[] buttons;
	private BorderLayout layout;
	private GridLayout grid;
	private ButtonGroup group;
	private String[] names = {
			"1", "2", "3", "4",
			"5", "6", "7", "8",
			"9", "0", ".", "=", 
			"+", "-", "*", "/"
	};
	private int index;
	
	public Calculator() {
		frame = new JFrame();
		northPanel = new JPanel();
		centralPanel = new JPanel();

		entry = new JTextField(20);
		buttons = new JButton[16];
		group = new ButtonGroup(); 
		layout = new BorderLayout();
		grid = new GridLayout(4, 4, 20, 20);
		frame.setSize(new Dimension(400, 300));
		frame.add(northPanel, layout.NORTH);
		frame.add(centralPanel, layout.CENTER);
		northPanel.add(entry, layout.CENTER);
		centralPanel.setLayout(grid);
		for (int i = 0; i < buttons.length; i++) {
			buttons[i] = new JButton(names[i]);
			group.add(buttons[i]);
			centralPanel.add(buttons[i]);
		}
		for (int i = 0; i < buttons.length; i++) {
			index = i;
			buttons[i].addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					entry.setText("");
					entry.setText(names[index]);
				}
			});
		}
	}
	
	public void go() {
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Calculator cal = new Calculator();
		cal.go();
	}

}
