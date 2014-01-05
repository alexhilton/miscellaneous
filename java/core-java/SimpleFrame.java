import javax.swing.*;

public class SimpleFrame {
    public static void main( String[] args ) {
	NullFrame frame = new NullFrame();
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setVisible(true);
    }
}

class NullFrame extends JFrame {
    NullFrame() {
	setSize(300, 200);
    }
}