#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>


// Define a constant for the value of PI
#define PI 3.1415f

// Rotation amounts
static GLfloat xrot = 0.0f;
static GLfloat yrot = 0.0f;

void DrawTorus()
{
	GLfloat x, y, z, angle;
	angle = 0.f;
	z = 0.f;
	glColor3f( 1.f, .2f, .4f );
	glPointSize(3.f);
	// to-do: add drawing codes here
	glBegin(GL_LINE_STRIP);
	for ( angle = 0.f; angle < 8*PI; angle += .5f ) {
		x = 50.f * cos( angle );
		y = 50.f * sin( angle );
		glVertex3f( x, y, z );
	}
	// end drawing
	glEnd();
}

// Reset flags as appropriate in response to menu selections
void processMenu(int value)	{
	switch(value) {
	case 1:
		exit( 0 );
	default:
		break;
	}
}

// add keyboard process function
void keyboard( unsigned char key, int x, int y ) {
	if ( key == 'q' || key == 'Q' || key == 27 ) {
		exit( 0 );
	}
}

// Called to draw scene
void renderScene(void) {

	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);


	DrawTorus();
	// Restore transformations
	glPopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context. 
void setupRC() {
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);
}

void specialKeys(int key, int x, int y)	{
	if(key == GLUT_KEY_UP) {
		xrot-= 5.0f;
	}

	if(key == GLUT_KEY_DOWN) {
		xrot += 5.0f;
	}

	if(key == GLUT_KEY_LEFT) {
		yrot -= 5.0f;
	}

	if(key == GLUT_KEY_RIGHT) {
		yrot += 5.0f;
	}

	if(key > 356.0f) {
		xrot = 0.0f;
	}

	if(key < -1.0f) {
		xrot = 355.0f;
	}

	if(key > 356.0f) {
		yrot = 0.0f;
	}

	if(key < -1.0f) {
		yrot = 355.0f;
	}

	// Refresh the Window
	glutPostRedisplay();
}


void changeSize(int w, int h) {
	GLfloat range = 100.0f;

	// Prevent a divide by zero
	if(h == 0) {
		h = 1;
	}

	// Set View port to window dimensions
    glViewport(0, 0, w, h);

	// Reset projection matrix stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) {
		glOrtho (-range, range, -range*h/w, range*h/w, -range, range);
    } else { 
		glOrtho (-range*w/h, range*w/h, -range, range, -range, range);
	}

	// Reset Model view matrix stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[]) {
	int modeMenu;

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( 640, 480 );
	glutInitWindowPosition( 100, 100 );
	glutCreateWindow( argv[ 0 ] );
	
	// Create the Menu
	modeMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry( "Exit", 1 );
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutReshapeFunc(changeSize);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyboard);

	setupRC();

	glutMainLoop();

	return 0;
}
