import javax.swing.*;
  public class SimpleFrameTest
  {
     public static void main(String[] args)
     {
        SimpleFrame frame = new SimpleFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.show();
     }
  }
  class SimpleFrame extends JFrame
  {
     public SimpleFrame()
     {
        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
     }
     public static final int DEFAULT_WIDTH = 300;
     public static final int DEFAULT_HEIGHT = 200;
}

