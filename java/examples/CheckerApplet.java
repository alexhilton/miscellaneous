/*
 * File: checkerApplet.java
 *
 * This applet draws an 8x8 checkerboard pattern. The size
 * of the individual squares is chosen so that the checkerboard
 * fills the smaller dimension of the applet window.
 */
import java.applet.Applet;
import java.awt.*;
public class CheckerApplet extends Applet {
    public void paint( Graphics g ) {
	int row, col, squareSize;
	squareSize = ( Math.min( size().width, size().height ) - 1 ) / 8;
	g.drawRect( 0, 0, 8 * squareSize, 8 * squareSize );
	for ( row = 0; row < 8; row++ ) {
	    for ( col = 0; col < 8; col++ ) {
		if ( ( col + row ) % 2 == 0 ) {
		     g.setColor( Color.white );
		} else {
		     g.setColor( Color.black );
		}
		g.fillRect( col * squareSize, row * squareSize,
				squareSize, squareSize );
	    }
	}
    }
}
