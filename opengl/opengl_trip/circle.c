/*#include <gl/glut.h>
#include <math.h>
#include "circle.h"

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
	double radius = 1.0f;
	float theta = 0.0f;
	const float PI = 3.1415926f;
	glBegin( GL_LINE_LOOP );
		for ( theta = 0.0f; theta < 2*PI; theta += PI/12.0f ) {
			float x = radius * cos( theta );
			float y = radius * sin( theta );
			glVertex2f( x, y );
		}
	glEnd();

	glFlush();
}
*/


#include <gl/glut.h>
#include <math.h>
#include "test_opengl.h"

void circle_display() {
	glClear( GL_COLOR_BUFFER_BIT );
	// Draw the X-Y Axis
	glColor3f( 1.0f, 0.0f, 0.0f );
	glBegin( GL_LINES );
		// X axis
		glVertex3f( -1.0f, 0.0f, 0.0f );
		glVertex3f( 1.0f, 0.0f, 0.0f );
		// Y axis
		glVertex3f( 0.0f, -1.0f, 0.0f );
		glVertex3f( 0.0f, 1.0f, 0.0f );
	glEnd();
		
	// Draw the circle
	float radius = 1.0f;
	float theta = 0.0f;
	const float PI = 3.1415926f;
	glBegin( GL_LINE_LOOP );
		for ( theta = 0.0f; theta < 2*PI; theta += PI/12.0f ) {
			float x = radius * cos( theta );
			float y = radius * sin( theta );
			glVertex2f( x, y );
		}
	glEnd();
	
	glFlush();
}

void circle_init() {
	// Clearing color is black
	// red, green, blue and alpha
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f );
}