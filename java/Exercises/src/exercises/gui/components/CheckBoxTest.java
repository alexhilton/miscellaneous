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
public class CheckBoxTest {
	JFrame frame;
	JPanel panel;
	JLabel tag;
	JTextArea area;
	JCheckBox basketball;
	JCheckBox football;
	JCheckBox swimming;
	JCheckBox lift;
	JCheckBox soccer;
	JCheckBox shooting;
	
	public void go() {
		frame = new JFrame();
		panel = new JPanel();
		tag = new JLabel("Please select your sport interests: ");
		area = new JTextArea(10, 20);
		BoxLayout manager = new BoxLayout(panel, BoxLayout.Y_AXIS);
		basketball = new JCheckBox("Basketball");
		football = new JCheckBox("Football");
		swimming = new JCheckBox("Swimming");
		lift = new JCheckBox("Lift");
		soccer = new JCheckBox("Soccer");
		shooting = new JCheckBox("Shooting");
		basketball.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				area.append("Basketball\n");
			}
		});
		football.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				area.append("Football\n");
			}
		});
		swimming.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				area.append("Swimming\n");
			}
		});
		lift.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				area.append("Lift\n");
			}
		});
		soccer.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				area.append("Soccer\n");
			}
		});
		shooting.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent event) {
				area.append("Shooting\n");
			}
		});
		frame.getContentPane().add(BorderLayout.NORTH, tag);
		panel.add(basketball, manager);
		panel.add(football, manager);
		panel.add(swimming, manager);
		panel.add(lift, manager);
		panel.add(soccer, manager);
		panel.add(shooting, manager);
		panel.add(area);
		frame.add(panel);
		frame.setSize(480, 320);
		frame.setTitle("Check Box Test");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		CheckBoxTest gui = new CheckBoxTest();
		gui.go();
	}

}
