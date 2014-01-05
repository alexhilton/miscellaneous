import java.awt.*;
import javax.swing.*;

public class HelloWorld {
    public static void main(String[] args) {
	HelloFrame frame = new HelloFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setVisible(true);
    }
}

class HelloFrame extends JFrame {
    public HelloFrame() {
	setTitle("Hello world");
	setSize(300, 400);
	setLocation(300, 125);
	HelloPanel panel = new HelloPanel();
	add(panel);
    }
}

class HelloPanel extends JPanel {
    public void paintComponent(Graphics g) {
	super.paintComponent(g);
	g.drawString("Hello, world", 125, 200);
    }
}
