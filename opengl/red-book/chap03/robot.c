/*
 * $Header$
 * $Author$
 * $Date$
 * RCS Id: $Id$
 * $Revision$
 * $Log$
 */
/**
 * Simulating the arm of a robot
 */
#include <stdlib.h>
#include <GL/glut.h>

static int shoulder = 0;
static int elbow = 0;

/** private function prototypes */
static void init( void );
static void display( void );
static void reshape( int w, int h );
static void keyboard( unsigned char key, int x, int y );

/* Main function */
int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize( 500, 500 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "Solar System" );
  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMainLoop();

  return 0;
}

static void init( void ) {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glShadeModel( GL_FLAT );
}

static void display( void ) {
  glClear( GL_COLOR_BUFFER_BIT );

  /* Why save the matrix from beginning, not after drawing the sun */
  glPushMatrix();
  /* Draw the sun */
  glColor3f( 1.0f, 0.8f, 0.1f );
  glTranslatef( -1.0f, 0.0f, 0.0f );
  glRotatef( (GLfloat) shoulder, 0.0f, 0.0f, 1.0f );
  glTranslatef( 1.0f, 0.0f, 0.0f );
  glPushMatrix();
  glScalef( 2.0f, 0.4f, 1.0f );
  glutWireCube( 1.0f );
  glPopMatrix();

  glTranslatef( 1.0f, 0.0f, 0.0f );
  glRotatef( (GLfloat) elbow, 0.0f, 0.0f, 1.0f );
  glTranslatef( 1.0f, 0.0f, 0.0f );
  glPushMatrix();
  glScalef( 2.0f, 0.4f, 1.0f );
  glutWireCube( 1.0f );
  glPopMatrix();

  glPopMatrix();
  glutSwapBuffers();
}

static void reshape( int w, int h ) {
  glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 65.0f, (GLfloat) w/(GLfloat) h, 1.0f, 20.0f );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0.0f, 0.0f, -5.0f );
}

static void keyboard( unsigned char key, int x, int y ) {
  switch ( key ) {
  case 's':
    shoulder = (shoulder + 10) % 360;
    glutPostRedisplay();
    break;
  case 'S':
    shoulder = (shoulder - 10) % 360;
    glutPostRedisplay();
    break;
  case 'e':
    elbow = (elbow + 10) % 360;
    glutPostRedisplay();
    break;
  case 'E':
    elbow = (elbow - 10) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit( EXIT_SUCCESS );
  default:
    break;
  }
}
