/*
 * trigger.c
 * The main program for OpenGL programs.
 * All other files are included into main program, so we don't have
 * to create many projects.
 */
#include <stdio.h>
#include <gl/glut.h>
#include "circle.h"

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