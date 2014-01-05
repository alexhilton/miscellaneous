/*
 * poly_mode.c
 * explore details when drawing polygons.
 * We try different colors and modes for filled polygons
 */
#include <GL/glut.h>
#include <stdlib.h>

void display( void );
void init( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 350, 150 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "Polygon Mode" );
  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMainLoop();
  return 0;
}

void display( void ) {
  glClear( GL_COLOR_BUFFER_BIT );
  glColor3f( 1.0f, 1.0f, 1.0f );

  /*
   * In summary, the mode for polygon is pretty simple: You can specify drawing
   * mode(filled, outlined or pointed) to both front and back faces. You can
   * specify which side is front face, CCW or CW. You can also erase one face or
   * both by culling.
   */
  /* 
   * draw one solid colorful five-sided polygon---Pentegon
   * And another two Yello pentegons with different mode.
   */
  glPolygonMode( GL_BACK, GL_FILL );
  glPolygonMode( GL_FRONT, GL_POINT );
  /* 
   * Make CounterClockWise front face
   * Here, if you set CCW as front face, you will see points since we set front
   * as points. If you set CW as front face, you will see filled polygons,
   * because we set back as filled.
   */
  glFrontFace( GL_CCW );
  glEnable( GL_CULL_FACE );
  /* culling back face----erasing back face */
  /* You will see nothing if you set back face(CW) as front face */
  glCullFace( GL_BACK );
  glBegin( GL_POLYGON );
    glColor3f( 1.0f, 0.0f, 0.0f );
    glVertex2f( 10.0f, 60.0f );
    glColor3f( 0.0f, 1.0f, 0.0f );
    glVertex2f( 35.0f, 10.0f );
    glColor3f( 0.0f, 0.0f, 1.0f );
    glVertex2f( 80.0f, 10.0f );
    glColor3f( 1.0f, 1.0f, 0.0f );
    glVertex2f( 105.0f, 60.0f );
    glColor3f( 0.0f, 1.0f, 1.0f );
    glVertex2f( 80.0f, 110.0f );
    glColor3f( 1.0f, 0.0f, 1.0f );
    glVertex2f( 35.0f, 110.0f );
  glEnd();
  glColor3f( 0.6f, 0.2f, 0.8f );
  glBegin( GL_POLYGON );
    glVertex2f( 115.0f, 60.0f );
    glVertex2f( 140.0f, 10.0f );
    glVertex2f( 185.0f, 10.0f );
    glVertex2f( 210.0f, 60.0f );
    glVertex2f( 185.0f, 110.0f );
    glVertex2f( 140.0f, 110.0f );
  glEnd();
  glColor3f( 0.6f, 0.2f, 0.8f );
  glBegin( GL_POLYGON );
    glVertex2f( 220.0f, 60.0f );
    glVertex2f( 245.0f, 10.0f );
    glVertex2f( 290.0f, 10.0f );
    glVertex2f( 315.0f, 60.0f );
    glVertex2f( 290.0f, 110.0f );
    glVertex2f( 245.0f, 110.0f );
  glEnd();
  glDisable( GL_CULL_FACE );
  glFlush();
}

void init( void ) {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glShadeModel( GL_FLAT );
}

void reshape( int w, int h ) {
  glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( 0.0f, (GLdouble) w, 0.0f, (GLdouble) h );
}

void keyboard( unsigned char key, int x, int y ) {
  if ( key == 27 ) {
    exit( EXIT_SUCCESS );
  }
}
