#include <gl/glut.h>
#include <stdio.h>
#include "test_opengl.h"

void display() {
	printf( "display gets called\n" );
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 0.7f, 0.7f, 0.2f );
	glBegin( GL_POLYGON );
		glVertex3f( 0.25f, 0.25f, 0.0f );
		glVertex3f( 0.25f, 0.75f, 0.0f );
		glVertex3f( 0.75f, 0.75f, 0.0f );
		glVertex3f( 0.75f, 0.25f, 0.0f );
	glEnd();

	glFlush();
}

void init() {
	printf( "init gets called\n" );
	// Clearing color is black
	// red, green, blue and alpha
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f );
}
