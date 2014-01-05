/**
 * 
 */
package exercises.io.fileio;
import java.io.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/**
 * @author gongzhihui
 *
 */
public class FileExample {
	JFrame frame;
	JPanel panel;
	JButton browse;
	JTextArea area;
	JButton delete;
	JButton clear;
	JButton exit;
	
	public void go() {
		frame = new JFrame("File Example");
		frame.setSize(new Dimension(480, 300));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		panel = new JPanel();
		Font font = new Font("sanserif", Font.BOLD, 18);
	
		area = new JTextArea(6, 24);
		area.setEditable(true);
		area.setLineWrap(true);
		area.setFont(font);
		JScrollPane scroll = new JScrollPane(area);
		scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		
		panel.add(scroll);
		
		browse = new JButton("Browse");
		browse.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JFileChooser chooser = new JFileChooser(System.getProperty("user.home"));
				/*
				 * Here you must set the properties before showing the dialog, otherwise the dialog
				 * will be shown without properties
				 */
				chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				if (chooser.showOpenDialog(frame) == JFileChooser.APPROVE_OPTION) {
					listFolder(chooser.getSelectedFile());
				}
			}
		});
		delete = new JButton("Delete");
		delete.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JFileChooser chooser = new JFileChooser(System.getProperty("user.home"));
				/*
				 * Here you have to set the properties before showing the dialog, otherwise the 
				 * dialog will be shown without properties
				 */		
				chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
				if (chooser.showDialog(frame, "Delete") == JFileChooser.APPROVE_OPTION) {
					deleteFile(chooser.getSelectedFile());
				}
			}
		});
		clear = new JButton("Clear");
		clear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				area.setText("");
			}
		});
		exit = new JButton("Exit");
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		
		panel.add(browse);
		panel.add(delete);
		panel.add(clear);
		panel.add(exit);
		frame.add(panel);
	}
	
	private void deleteFile(File home) {
		assert(home != null);
		
		if (home.isDirectory()) {
			String[] fileList = home.list();
			for (String file : fileList) {
				new File(file).delete();
			}
		}
		home.delete();
	}
	
	private void listFolder(File home) {
		assert(home != null);
		
		if (home.isDirectory()) {
			String[] fileList = home.list();
			for (int i = 0; i < fileList.length; i++) {
				area.insert(fileList[i] + "\n", i);
			}
		} else {
			area.setText(home.getName());
		}
	}
	
	public void setVisible(boolean b) {
		frame.setVisible(b);
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FileExample gui = new FileExample();
		gui.go();
		gui.setVisible(true);
	}

}
