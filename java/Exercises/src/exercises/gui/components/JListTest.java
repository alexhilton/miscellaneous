/**
 * 
 */
package exercises.gui.components;
import javax.swing.*;
import javax.swing.event.*;

/**
 * @author gongzhihui
 *
 */
public class JListTest {
	JFrame frame;
	JList list;
	JPanel panel;
	JScrollPane scroll;
	
	public void go() {
		frame = new JFrame();
		panel = new JPanel();
		String[] entries = { "alpha", "beta", "gama", "delta", "episilon", 
				"zeta", "theta", "eta" };
		frame.setSize(320, 240);
		frame.setTitle("JList Test Program");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		list = new JList(entries);
		list.setVisibleRowCount(5);
		scroll = new JScrollPane(list);
		scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		list.addListSelectionListener(new ListSelectionListener() {
				public void valueChanged(ListSelectionEvent arg0) {
				// TODO Auto-generated method stub
				String tmp = (String) list.getSelectedValue();
				System.out.println(tmp);
			}
		});
		panel.add(scroll);
		frame.add(panel);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		JListTest gui = new JListTest();
		gui.go();
	}

}
