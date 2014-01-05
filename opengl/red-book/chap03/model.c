/*
 * model.c
 * This program demonstrates modeling transformations.
 */
#include <GL/glut.h>
#include <stdlib.h>

void init( void );
void display( void );
void draw_triangle( void );
void reshape( GLsizei w, GLsizei h );
void keyboard( unsigned char key, int x, int y );

int main( int argc, char **argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 500, 500 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( *argv );
  init();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutMainLoop();
  return 0;
}

void init( void ) {
  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
  glShadeModel( GL_FLAT );
}

void draw_triangle( void ) {
  glBegin( GL_LINE_LOOP );
    glVertex2f( 0.0f, 25.0f );
    glVertex2f( 25.0f, -25.0f );
    glVertex2f( -25.0f, -25.0f );
  glEnd();
}

void display( void ) {
  glClear( GL_COLOR_BUFFER_BIT );

  /* Normal one */
  glLoadIdentity();
  glColor3f( 1.0f, 0.0f, 0.0f );
  draw_triangle();

  /* move 20 units down to -x-axis */
  glColor3f( 1.0f, 1.0f, 0.0f );
  glEnable( GL_LINE_STIPPLE );
  glLineStipple( 1, 0xf0f0 );
  glLoadIdentity();
  glTranslatef( -20.0f, 0.0f, 0.0f );
  draw_triangle();

  /* stretch twice and a half in x-axis, shrink half in y-axis, z-axis unchanged */
  glColor3f( 0.0f, 1.0f, 1.0f );
  glLineStipple( 1, 0xf00f );
  glLoadIdentity();
  glScalef( 1.5f, 0.5f, 1.0f );
  draw_triangle();

  /* rotate 90 degress around z-axis */
  glColor3f( 0.0f, 0.0f, 1.0f );
  glLineStipple( 1, 0x8888 );
  glLoadIdentity();
  glRotatef( 90.0f, 0.0f, 0.0f, 1.0f );
  draw_triangle();
  glDisable( GL_LINE_STIPPLE );

  glFlush();
}

void reshape( GLsizei w, GLsizei h ) {
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

void keyboard( unsigned char key, int x, int y ) {
  if ( key == 27 ) {
    exit( EXIT_SUCCESS );
  }
}
