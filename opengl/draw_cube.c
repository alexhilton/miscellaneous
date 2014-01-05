#include <GL/glut.h>
void display( void ) {
	/* clear all pixels */
	/*
	 * It is wierd, but the left bottom corner is (0, 0).
	 */
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1.0, 1.0, 1.0 );
	glBegin( GL_LINE_LOOP );
	glColor3f( 1.f, 0.f, 0.f );
	glVertex3f( 0.25f, 0.25f, 0.0f );
	glVertex3f( 0.25f, 0.5f, 0.0f );
	glVertex3f( 0.5f, 0.5f, 0.0f );
	glVertex3f( 0.5f, 0.25f, 0.0f );
	glEnd(  );
	glBegin( GL_LINE_STRIP );
	glVertex3f( 0.25f, 0.5, 0.0f );
	glVertex3f( 0.375, 0.625, 0.0f );
	glVertex3f( 0.625f, 0.625f, 0.0f );
	glVertex3f( 0.625f, 0.375f, 0.0f );
	glVertex3f( 0.5, 0.25, 0.0f );
	glEnd(  );
	glBegin( GL_LINE_STRIP );
	glVertex3f( 0.5f, 0.5f, 0.0f );
	glVertex3f( 0.625f, 0.625f, 0.0f );
	glEnd(  );
	/* start processing buffered OpenGL routines    */
	glFlush(  );
}

void init( void ) {
	/* select clearing color    */
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity(  );

	/* initialize viewing values    */
	glOrtho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
}

int main( int argc, char **argv ) {

	glutInit( &argc, argv );

	/*Declare initial display mode(single buffer and RGBA). */
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );

	/*Declare initial window size. */
	glutInitWindowSize( 640, 640 );

	/*Declare initial window position. */
	glutInitWindowPosition( 100, 100 );

	/*Open window with "hello"in its title bar. */
	glutCreateWindow( "hello" );

	/*Call initialization routines. */
	init(  );

	/*Register callback function to display graphics. */
	glutDisplayFunc( display );

	/*Enter main loop and process events. */
	glutMainLoop(  );
	return 0;
}
