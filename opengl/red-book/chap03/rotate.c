/*
 * rotate.c
 * exploring how the roatation works
 */
#include <stdlib.h>
#include <GL/glut.h>

static int xrot = 0;
static int yrot = 0;
static int zrot = 0;
static int rotate = 2;
static int xRot = 0;
static int yRot = 0;

/** private function prototypes */
static void init( void );
static void display( void );
static void reshape( int w, int h );
static void keyboard( unsigned char key, int x, int y );
static void specialKeys( int key, int x, int y );
static void mouse( int button, int state, int x, int y );

/* Main function */
int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 640, 480 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "Rotation Exploration" );
  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutSpecialFunc( specialKeys );
  glutMouseFunc( mouse );
  glutKeyboardFunc( keyboard );
  glutMainLoop();

  return 0;
}

static void display_bak( void ) {
  double len = 50.0f;
  double base = 2.0f;
  double height = 4.0f;
  glClear( GL_COLOR_BUFFER_BIT );
  glColor3f( 1.0f, 1.0f, 1.0f );

  glPushMatrix();
  glRotatef( (GLfloat) xrot, 1.0f, 0.0f, 0.0f );
  glRotatef( (GLfloat) yrot, 0.0f, 1.0f, 0.0f );
  glRotatef( (GLfloat) zrot, 0.0f, 0.0f, 1.0f );

  glColor3f( 1.0f, 0.0f, 0.0f );
  glLineWidth( 3.0f );
  /* Draw a 3-D axes x, y and z of coordinate system */
  /* X-axis */
  glBegin( GL_LINES );
    glVertex3f( len/-2.0f, 0.0f, 0.0f );
    glVertex3f( len/2.0f, 0.0f, 0.0f );
  glEnd();
  /* Y-axis */
  glBegin( GL_LINES );
    glVertex3f( 0.0f, len/-2.0f, 0.0f );
    glVertex3f( 0.0f, len/2.0f, 0.0f );
  glEnd();
  /* Z-axis */
  glBegin( GL_LINES );
    glVertex3f( 0.0f, 0.0f, len/-2.0f );
    glVertex3f( 0.0f, 0.0f, len/2.0f );
  glEnd();
  glPushMatrix();
  /* Draw the directions */
  /* X-axis' direction */
  glTranslatef( 0.0f, 0.0f, len/2.0f );
  glutSolidCone( base, height, 10, 20 );
  /* X-axis' direction */
  glTranslatef( len/2.0f, 0.0f, 0.0f );
  glRotatef( 90.0f, 0.0f, 1.0f, 0.0f );
  glutSolidCone( base, height, 10, 20 );
  /* X-axis' direction */
  glTranslatef( 0.0f, len/2.0f, 0.0f );
  glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
  glutSolidCone( base, height, 10, 20 );
  glPopMatrix();
  glPopMatrix();


  glutSwapBuffers();
}

static void keyboard_bak( unsigned char key, int x, int y ) {
  switch ( key ) {
  case 'x':
    xrot = (xrot + rotate) % 360;
    glutPostRedisplay();
    break;
  case 'X':
    xrot = (xrot - rotate) % 360;
    glutPostRedisplay();
    break;
  case 'y':
    yrot = (yrot + rotate) % 360;
    glutPostRedisplay();
    break;
  case 'Y':
    yrot = (yrot - rotate) % 360;
    glutPostRedisplay();
    break;
  case 'z':
    zrot = (zrot + rotate) % 360;
    glutPostRedisplay();
    break;
  case 'Z':
    zrot = (zrot - rotate) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit( EXIT_SUCCESS );
  default:
    break;
  }
}

void reshape_bak( GLsizei w, GLsizei h ) {
  glViewport( 0, 0, w, h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  if ( w <= h ) {
    glOrtho( -50.0f, 50.0f, -50.0f*(GLfloat) h/(GLfloat) w,
	50.0f*(GLfloat) h/(GLfloat) w, -1.0, 1.0 );
  } else {
    glOrtho( -50.0f*(GLfloat) w / (GLfloat) h,
	50.0*(GLfloat) w / (GLfloat) h, -50.0f, 50.0f, -1.0, 1.0f );
  }
  glMatrixMode( GL_MODELVIEW );
}

/* renderScene, or display in other examples */
static void display() {
  int i;
  /* clear current screen using current color */
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  gluLookAt( 50.0f, 30.0f, 50.f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
  /* save matrix and rotate */
  glPushMatrix();
  glRotatef( xRot, 1.f, 0.f, 0.f );
  glRotatef( yRot, 0.f, 1.f, 0.f );
  /* draw pictures here */

  /* color for axis */
  glColor3f( 1.f, 0.f, 0.f );
  /* draw the axis */
  GLfloat min = -100.f;
  GLfloat max = 100.f;
  /* x axis */
  glBegin( GL_LINES );
    glVertex3f( min, 0.f, 0.f );  
    glVertex3f( max, 0.f, 0.f );
  glEnd();
  /* draw the direction pointer for axis x */
  glPushMatrix();
  glTranslatef( max, 0.f, 0.f );
  glRotatef( 90.f, 0.f, 1.f, 0.f );
  glutSolidCone( 3.f, 6.f, 10, 10 );
  glPopMatrix();
  /* y axis */
  glBegin( GL_LINES );
    glVertex3f( 0.f, min, 0.f );
    glVertex3f( 0.f, max, 0.f );
  glEnd();
  /* draw the direction pointer for axis y */
  glPushMatrix();
  glTranslatef( 0.f, max, 0.f );
  glRotatef( 270.f, 1.f, 0.f, 0.f );
  glutSolidCone( 3.f, 6.f, 10, 10 );
  glPopMatrix();
  /* z axis */
  glBegin( GL_LINES );
    glVertex3f( 0.f, 0.f, min );
    glVertex3f( 0.f, 0.f, max );
  glEnd(); 
  /* draw the direction pointer for axis z */
  glPushMatrix();
  glTranslatef( 0.f, 0.f, max);
  glutSolidCone( 3.f, 6.f, 10, 10 );
  glPopMatrix();
  /* axis done */

  /* mark the axis */
  glPushMatrix();
	glRasterPos3f( max + 8, 0.f, 0.f );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'X' );
	glRasterPos3f( 0.f, max + 8, 0.f );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'Y' );
	glRasterPos3f( 0.f, 0.f, max + 8 );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'Z' );
  glPopMatrix();

  glColor3f( 1.0f, 1.0f, 0.0f );
  glutWireSphere( 30.0f, 20, 20 );
  /* return rotate */
  glPopMatrix();
 
  /* refresh */
  glutSwapBuffers();
}

/* set up render condition or init() in other examples */
void init() {
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };
	
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	
    // Enable lighting
    glEnable(GL_LIGHTING);
	
    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
	
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
	
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void keyboard( unsigned char key, int x, int y ) {
  if ( key == 27 || key == 'Q' || key == 'q' ) {
    exit( 0 );
  }
}

static void specialKeys( int key, int x, int y ) {
  switch ( key ) {
  case GLUT_KEY_UP:
    xRot -= 5.f;
    break;
  case GLUT_KEY_DOWN:
    xRot += 5.f;
    break;
  case GLUT_KEY_LEFT:
    yRot -= 5.f;
    break;
  case GLUT_KEY_RIGHT:
    yRot += 5.f;
    break;
  default:
    break;
  }
  if ( key > 356.f ) {
    xRot = 0.f;
  }
  if ( key < -1.f ) {
    xRot = 355.f;
  }
  if ( key > 356.f ) {
    yRot = 0.f;
  }
  if ( key < -1.f ) {
    yRot = 355.f;
  }
  glutPostRedisplay();
}

void mouse( int button, int state, int x, int y ) {
  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) {
    exit( 0 );
  }
}

/* glut call this when window is resizing or reshape in ohers */
static void reshape( GLsizei w, GLsizei h ) {
  GLfloat range = 120.f;

  /* avoid divided by 0 */
  if ( h == 0 ) {
    h = 1;
  }
  if ( w == 0 ) {
    w = 1;
  }

  GLfloat aspect = (GLfloat) w / (GLfloat) h;
  /* set view port according to window size */
  glViewport( 0, 0, w, h );

  /* reset coordinates */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  /* setup ortho */
  if ( w <= h ) {
    glOrtho( -range, range, -range * h/w, range * h/w, -range*2.f, range*2.f );
  } else {
    glOrtho( -range*w/h, range*w/h, -range, range, -range*2.f, range*2.f );
  }
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}
