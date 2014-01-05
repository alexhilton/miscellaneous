/*
 * $Header$
 * $Author$
 * $Date$
 * RCS Id: $Id$
 * $Revision$
 * $Log$
 */
/**
 * Simulating the solar system with nine planets orbiting the sun and rotate by
 * themselvs too.
 */
#include <stdlib.h>
#include <GL/glut.h>

/** frequencies of sun ---- year */
static int year = 0;
/** frequencies of earth ---- day */
static int day = 0;
/** frequencies of moon ---- moonRotate */
static int moonRotate = 0;

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
  glColor3f( 1.0f, 1.0f, 1.0f );

  /* Why save the matrix from beginning, not after drawing the sun */
  glPushMatrix();
  /* Draw the sun */
  glColor3f( 1.0f, 0.8f, 0.1f );
  glutSolidSphere( 1.0f, 20, 16 );
  glRotatef( (GLfloat) year, 0.0f, 1.0f, 0.0f );
  glTranslatef( 2.0f, 0.0f, 0.0f );
  glRotatef( (GLfloat) day, 0.0f, 1.0f, 0.4f );
  /* Draw smaller planet */
  glColor3f( 0.1f, 0.3f, 0.2f );
  glutSolidSphere( 0.2f, 10, 8 );

  /* A moon for the planet */
  glColor3f( 1.0f, 0.0f, 0.0f );
  glTranslatef( 2.5f, 0.0f, 0.0f );
  glRotatef( (GLfloat) moonRotate, 0.0f, 1.0f, 0.2f );
  glutSolidSphere( 0.1f, 10, 8 );
  glPopMatrix();
  glPopMatrix();
  glutSwapBuffers();
}

static void reshape( int w, int h ) {
  glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 60.0f, (GLfloat) w/(GLfloat) h, 1.0f, 20.0f );
  glMatrixMode( GL_MODELVIEW );
  gluLookAt( 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
}

static void keyboard( unsigned char key, int x, int y ) {
  switch ( key ) {
  case 'd':
    day = (day + 10) % 360;
    glutPostRedisplay();
    break;
  case 'D':
    day = (day - 10) % 360;
    glutPostRedisplay();
    break;
  case 'y':
    year = (year + 10) % 360;
    glutPostRedisplay();
    break;
  case 'Y':
    year = (year - 10) % 360;
    glutPostRedisplay();
    break;
  case 'm':
    moonRotate = (moonRotate + 10) % 360;
    glutPostRedisplay();
    break;
  case 'M':
    moonRotate = (moonRotate - 10) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit( EXIT_SUCCESS );
  default:
    break;
  }
}
