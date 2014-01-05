/*
 * lines.c
 * exploring details when drawing a line.
 * setting properties like line width, stipple.
 */
#include <GL/glut.h>

#define drawOneLine( x1, y1, x2, y2 ) glBegin( GL_LINES ); \
  glVertex2f( (x1), (y1) ); glVertex2f( (x2), (y2) ); glEnd();

void display( void );
void init( void );
void reshape( int w, int h );

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 450, 256 );
  glutInitWindowPosition( 100, 64 );
  glutCreateWindow( "Line Details" );
  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutMainLoop();
  return 0;
}
void init( void ) {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glShadeModel( GL_FLAT );
}

void display( void ) {
  int i;
  glClear( GL_COLOR_BUFFER_BIT );
  /* select white for all lines */
  glColor3f( 1.0f, 1.0f, 1.0f );
  /* in 1st row, 3 lines, each with a different stipple */
  glEnable( GL_LINE_STIPPLE );
  /* dotted */
  glLineStipple( 1, 0x0101 ); 
  drawOneLine( 50.0f, 125.0f, 150.0f, 125.0f );
  /* dashed */
  glLineStipple( 1, 0x00ff );
  drawOneLine( 150.0f, 125.0f, 250.0f, 125.0f );
  /* dash/dot/dash */
  glLineStipple( 1, 0x1c47 );
  drawOneLine( 250.0f, 125.0f, 350.0f, 125.0f );

  /* in 2nd row, 3 wide lines, each with different stipple */
  glLineWidth( 5.0f );
  /* dotted */
  glLineStipple( 1, 0x0101 );
  drawOneLine( 50.0f, 100.0f, 150.0f, 100.0f );
  /* dashed */
  glLineStipple( 1, 0x00ff );
  drawOneLine( 150.0f, 100.0f, 250.0f, 100.0f );
  /* dash/dot/dash */
  glLineStipple( 1, 0x1c47 );
  drawOneLine( 250.0f, 100.0f, 350.0f, 100.0f );
  glLineWidth( 1.0f );

  /* 
   * in 3rd row, 6 lines, with dash/dot/dash stipple
   * as part of a single connected line strip
   */
  /* dash/dot/dash */
  glLineStipple( 1, 0x1c47 );
  glBegin( GL_LINE_STRIP );
    for ( i = 0; i < 7; i++ ) {
      glVertex2f( 50.0f + ((GLfloat) i * 50.0), 75.0f );
    }
  glEnd();

  /* in 4th row, 6 independent lines with same stipple */
  for ( i = 0; i < 6; i++ ) {
    drawOneLine( 50.0f + ((GLfloat) i * 50.0f), 50.0f,
	50.0 + ((GLfloat) (i+1) * 50.0f), 50.0f );
  }

  /* 
   * in 5th row, 1 line, with dash/dot/dash stipple and a stipple
   * repeat factor of 5
   */
  glLineStipple( 5, 0x1c47 );
  drawOneLine( 50.0f, 25.0f, 350.0f, 25.0f );
  glDisable( GL_LINE_STIPPLE );
  glFlush();
}

void reshape( int w, int h ) {
  glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( 0.0f, (GLdouble) w, 0.0f, (GLdouble) h );
}
