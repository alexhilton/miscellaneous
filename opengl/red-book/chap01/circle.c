/*
 * circle.c
 * We draw a colorful circle. We might add some animation to this circle, like
 * making it bounce later.
 */
#include <GL/glut.h>
#include <math.h>

static void display( void );
static void init( void );

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 480, 480 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( "Circle" );

  init();

  glutDisplayFunc( display );
  glutMainLoop();

  return 0;
}

/*
 * Draw a small colorful filled circle.
 */
static void display( void ) {
  glClear( GL_COLOR_BUFFER_BIT );

  int i;
  float radius = 0.25f;
  const float PI = 3.1415926f;
  const float x0 = 0.5f;
  const float y0 = 0.5f;
  /* 
   * draw a colorful filled circle
   * the color will change every one-fourth Pi -- 45 deg.
   */
  glBegin( GL_POLYGON );
    for ( i = 0; i <= 360; i += 2 ) {
      glColor3f( i/360.0f, i/540.0f, i/720.0f );
      glVertex2f( radius * cos( PI*i/180.0f ) + x0, radius * sin( PI*i/180.0f ) + y0 );
    }
  glEnd();
  glFlush();
}

/*
 * Do some essential initialization
 */
static void init( void ) {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f );
}
