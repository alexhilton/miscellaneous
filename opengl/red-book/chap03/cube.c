/*
 * cube.c
 * a simple cube with some basic transformations.
 */
#include <GL/glut.h>

static void init( void );
static void display( void );
static void reshape( int w, int h );

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 500, 500 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( *argv );
  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
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
  /* Clear the matrix: initialize it with identity matrix */
  glLoadIdentity();
  /* viewing transformation */
  /*
   * the camera(eye) is at (0.0, 0.0, 5.0);
   * it is aimed at (0.0, 0.0, 0.0);
   * And (0.0, 1.0, 0.0) is Up
   */
  gluLookAt( 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f );
  /*
   * The following translate has the same effect as above look at.
   * Because if you put the camera at (0, 0, 5), which is the same as you put
   * the model at (0, 0, -5) and camera at (0, 0, 0).
   */
  //glTranslatef( 0.0f, 0.0f, -5.0f );
  /* modeling transformation */
  /* twice large on y-axis */
  glScalef( 1.0f, 2.0f, 1.0f );
  glutWireCube( 1.0f );
  glFlush();
}

static void reshape( int w, int h ) {
  glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
  glMatrixMode( GL_PROJECTION );
  /* Clear the projection matrix: initialize it with identity matrix */
  glLoadIdentity();
  /* object is much smaller when 120 than 60 */
  //gluPerspective( 120.5f, 1.0f, 1.5f, 20.0f );
  glFrustum( -1.0f, 1.0f, -1.0f, 1.0f, 1.5f, 20.0f );
  glMatrixMode( GL_MODELVIEW );
}
