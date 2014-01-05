/*
 * File: HelloApplet.java
 *
 * This applet displays the message Hello world in the browser,
 * window.
 */
import java.applet.Applet;
import java.awt.*;
public class HelloApplet extends Applet {
    public void paint( Graphics g ) {
	g.drawString( " Hello, world", 30, 30 );
    }
}
