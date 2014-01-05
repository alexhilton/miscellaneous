import java.util.List;
import java.util.ArrayList;
import javax.swing.*;
import java.awt.*;

public class EnvironmentTest {
    public static void main(String[] args) {
	EnvironmentFrame frame = new EnvironmentFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setVisible(true);
	Environment one = new Environment();
	one.print();
    }
}

class EnvironmentFrame extends JFrame {
    public EnvironmentFrame() {
	setTitle("Enviroment");
	setSize(400, 300);
	JMenuBar menuBar = new JMenuBar();
	setJMenuBar(menuBar);
	JMenu fileMenu = new JMenu("File");
	menuBar.add(fileMenu);
	JMenu editMenu = new JMenu("Edit");
	menuBar.add(editMenu);
	JMenu helpMenu = new JMenu("Help");
	menuBar.add(helpMenu);
	JMenuItem openItem = new JMenuItem("Open");
	JMenuItem newItem = new JMenuItem("New");
	JMenuItem saveItem = new JMenuItem("Save");
	JMenuItem exitItem = new JMenuItem("Exit");
	fileMenu.add(newItem);
	fileMenu.add(openItem);
	fileMenu.add(saveItem);
	fileMenu.add(exitItem);

	JMenuItem copyItem = new JMenuItem("Copy");
	JMenuItem cutItem = new JMenuItem("Cut");
	JMenuItem pasteItem = new JMenuItem("Paste");
	JMenuItem undoItem = new JMenuItem("Undo");
	editMenu.add(undoItem);
	editMenu.add(cutItem);
	editMenu.add(copyItem);
	editMenu.add(pasteItem);
	JMenuItem indexItem = new JMenuItem("Index");
	JMenuItem aboutItem = new JMenuItem("About");
	helpMenu.add(indexItem);
	helpMenu.add(aboutItem);
	EnvironmentPanel panel = new EnvironmentPanel();
	add(panel);
    }
}

class Environment {
    private List<String> environ;
    public Environment() {
	environ = new ArrayList<String>();
	String var;
	while (hasMoreVariable()) {
	    var = getVariable();
	    addVariable(var);
	}
    }
    private void addVariable(String var) {
	environ.add(var);
    }
    public List<String> getEnviron() {
	return environ;
    }
    public void print() {
	for (int i = 0; i < environ.size(); i++) {
	    System.out.println(environ.get(i));
	}
    }
    private native boolean hasMoreVariable();
    private native String getVariable();
    static {
	System.loadLibrary("environ");
    }
}

class EnvironmentPanel extends JPanel {
    public EnvironmentPanel() {
	JTextArea text = new JTextArea(10, 40);
	JLabel label = new JLabel("The Environment Variables:");
	add(label);
	List<String> env = new Environment().getEnviron();
	for (int i = 0; i < env.size(); i++) {
	    text.append(env.get(i) + "\n");
	}
        JScrollPane scroll = new JScrollPane(text);
	//scroll.setAutomaticallyScroll(true);
	scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
	scroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
	add(scroll);
    }
}
