/*
 * poly_edge.c
 * explore details when drawing polygons.
 * we hide edges inside polygon.
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
   * We draw both back and front face using lines
   */
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  glColor3f( 0.6f, 0.2f, 0.8f );
  glBegin( GL_POLYGON );
    glEdgeFlag( GL_FALSE );
    glVertex2f( 115.0f, 60.0f );
    glVertex2f( 140.0f, 10.0f );
    glEdgeFlag( GL_TRUE );
    glVertex2f( 205.0f, 10.0f );
    glVertex2f( 230.0f, 60.0f );
    glEdgeFlag( GL_FALSE );
    glVertex2f( 205.0f, 110.0f );
    glVertex2f( 140.0f, 110.0f );
  glEnd();
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
