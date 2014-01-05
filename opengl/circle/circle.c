#include <gl/glut.h>
#include <math.h>

void circle_display() {
	glClear( GL_COLOR_BUFFER_BIT );
	
	// Draw the X-Y Axis
	glColor3f( 1.0f, 0.0f, 0.0f );
	glBegin( GL_LINES );
		// X axis
		glVertex2f( -1.0f, 0.0f );
		glVertex2f( 1.0f, 0.0f );
		// Y axis
		glVertex2f( 0.0f, -1.0f );
		glVertex2f( 0.0f, 1.0f );
	glEnd();
	
	// Draw the circle
	const GLfloat radius = 1.0f;
	GLfloat theta = 0.0f;
	const GLfloat PI = 3.1415926f;
	glBegin( GL_LINE_LOOP );
		for ( theta = 0.0f; theta < 2*PI; theta += PI/12.0f ) {
			GLfloat x = radius * cos( theta );
			GLfloat y = radius * sin( theta );
			glVertex2f( x, y );
		}	
	glEnd();
	
	glFlush();
}

void circle_init() {
	// Set background as black
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f );
}

/*
* trigger.c
* The main program for OpenGL programs.
* All other files are included into main program, so we don't have
* to create many projects.
*/
int main( int argc, char **argv ) {
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( 250, 250);
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( "OpenGL Trip" );
	
	circle_init();
	
	glutDisplayFunc( circle_display );
	glutMainLoop();
	
	return 0;
}
