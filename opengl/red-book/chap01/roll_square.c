/*
 * roll_square.c
 * Draw a rolling cube.
 */
#include <GL/glut.h>

static GLfloat spin = 0.0f;
static void init( void );
static void display( void );
static void reshape( int width, int height );
static void mouse( int button, int state, int x, int y );
static void spinDisplay( void );

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
  glutInitWindowSize( 256, 256 );
  glutInitWindowPosition( 128, 64 );
  glutCreateWindow( "Rolling Cube" );

  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutMouseFunc( mouse );
  glutMainLoop();
  return 0;
}

static void init( void ) {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glShadeModel( GL_FLAT );
}

static void display( void ) {
  glClear( GL_COLOR_BUFFER_BIT );
  glPushMatrix();
  glRotatef( spin, 0.0f, 0.0f, 1.0f );
  glColor3f( 1.0f, 1.0f, 1.0f );
  glRectf( -25.0f, -25.0f, 25.0f, 25.0f );
  glPopMatrix();
  glutSwapBuffers();
}

static void spinDisplay( void ) {
  spin += 2.0f;
  if ( spin > 360.0f ) {
    spin -= 360.0f;
  }
  glutPostRedisplay();
}

static void reshape( int width, int height ) {
  glViewport( 0, 0, (GLsizei) width, (GLsizei) height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glOrtho( -50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

static void mouse( int button, int state, int x, int y ) {
  switch ( button ) {
    case GLUT_LEFT_BUTTON:
      if ( state == GLUT_DOWN ) {
	glutIdleFunc( spinDisplay );
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if ( state == GLUT_DOWN ) {
	glutIdleFunc( NULL );
      }
      break;
    default:
      break;
  }
}
