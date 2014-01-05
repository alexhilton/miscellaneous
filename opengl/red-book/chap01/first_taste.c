/*
 * first_taste.c
 * The very first try of OpenGL.
 * First example --- example 1.1 in the red book--OpenGL programming guide.
 */
#include <GL/glut.h>

static void display();
static void init();

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 256, 256 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "First Taste" );
  init();
  glutDisplayFunc( display );
  glutMainLoop();

  return 0;
}

/*
 * The drawing part of an opengl program.
 * We do all drawing in this function.
 */
static void display( void ) {
  /* clear all pixels */
  glClear( GL_COLOR_BUFFER_BIT );
  /*
   * Draw a polygon (rectangle) with each color for each vertex.
   * One of most surprising discovery, glColor3i cannot work
   */
  //glColor3i( 255, 255, 255 );
  glColor3f( 1.0f, 1.0f, 1.0f );
  glBegin( GL_POLYGON );
    glColor3f( 1.0f, 1.0f, 0.0f );
    glVertex3f( 0.25f, 0.25f, 0.0f );
    glColor3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 0.75f, 0.25f, 0.0f );
    glColor3f( 0.0f, 0.0f, 1.0f );
    glVertex3f( 0.75f, 0.75f, 0.0f );
    glColor3f( 0.0f, 1.0f, 0.0f );
    glVertex3f( 0.25f, 0.75f, 0.0f );
  glEnd();

  /* Don't wait for completion of drawing */
  glFlush();
}

void init( void ) {
  /* black */
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f );
}
