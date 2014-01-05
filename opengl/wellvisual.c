/*
 * WellVisual.c
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define MAX_SIZE 1000
#define GL_PI 3.1415926f

/* keep track of window size when resizing */
static GLfloat xRot = 0.f;
static GLfloat yRot = 0.f;
static GLfloat x[ MAX_SIZE ];
static GLfloat y[ MAX_SIZE ];
static GLfloat z[ MAX_SIZE ];
static int dataSize = 0;

void loadData() {
  FILE *file = fopen( "input.dat", "w" );
  if ( file == NULL ) {
    perror( "'input.dat'" );
    exit( 0 );
  }
  double a, b, c;
  a = -10.f;
  b = 10.f;
  c = -10.f;
  int i;
  int step = 3;
  double xstep = 1.f;
  for ( i = 0; i < MAX_SIZE; i++ ) {
    fprintf( file, "%.3f %.3f %.3f\n", a, b, c );
    a += ( rand() % step ) / xstep;
    b -= ( rand() % step ) / xstep;
    c += ( rand() % step ) / xstep;
  }
  fclose( file );
  if ( (file = fopen( "input.dat", "r" )) == NULL ) {
    perror( "'input.dat'" );
    exit( 0 );
  }
  int rc;
  GLfloat ratio = 10.f; // zoom ratio
  for ( dataSize = 0; dataSize < MAX_SIZE; dataSize++ ) {
    if ( (rc = fscanf( file, "%f %f %f", &y[ dataSize ], &x[ dataSize ],
		       &z[ dataSize ] )) == EOF ) {
      break;
    }
	y[ dataSize ] /= -ratio;
	x[ dataSize ] /= ratio;
	z[ dataSize ] /= ratio;
    if ( rc != 3 ) {
      perror( "Bad data " );
      exit( 0 );
    }
  }
}
    
/* renderScene, or display in other examples */
void renderScene() {
  int i;
  loadData();
  //printf( "data size is %d\n", dataSize );
  /* clear current screen using current color */
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
  /* save matrix and rotate */
  glPushMatrix();
  glRotatef( xRot, 1.f, 0.f, 0.f );
  glRotatef( yRot, 0.f, 1.f, 0.f );
  /* draw pictures here */

  /* color for axis */
  glColor3f( 1.f, 0.f, 0.f );
  /* draw the axis */
  GLfloat min = -100.f;
  GLfloat max = 100.f;
  /* x axis */
  glBegin( GL_LINES );
    glVertex3f( min, 0.f, 0.f );  
    glVertex3f( max, 0.f, 0.f );
  glEnd();
  /* draw the direction pointer for axis x */
  glPushMatrix();
  glTranslatef( max, 0.f, 0.f );
  glRotatef( 90.f, 0.f, 1.f, 0.f );
  glutSolidCone( 3.f, 6.f, 10, 10 );
  glPopMatrix();
  /* y axis */
  glBegin( GL_LINES );
    glVertex3f( 0.f, min, 0.f );
    glVertex3f( 0.f, max, 0.f );
  glEnd();
  /* draw the direction pointer for axis y */
  glPushMatrix();
  glTranslatef( 0.f, max, 0.f );
  glRotatef( 270.f, 1.f, 0.f, 0.f );
  glutSolidCone( 3.f, 6.f, 10, 10 );
  glPopMatrix();
  /* z axis */
  glBegin( GL_LINES );
    glVertex3f( 0.f, 0.f, min );
    glVertex3f( 0.f, 0.f, max );
  glEnd(); 
  /* draw the direction pointer for axis z */
  glPushMatrix();
  glTranslatef( 0.f, 0.f, max);
  glutSolidCone( 3.f, 6.f, 10, 10 );
  glPopMatrix();
  /* axis done */

  /* mark the axis */
  glPushMatrix();
	//glTranslatef( max, 0.f, 0.f );
	glRasterPos3f( max + 8, 0.f, 0.f );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'X' );
	glRasterPos3f( 0.f, max + 8, 0.f );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'Y' );
	glRasterPos3f( 0.f, 0.f, max + 8 );
	glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'Z' );
  glPopMatrix();

  /* color for well */
  glColor3f( 0.f, 1.f, .5f );
  glTranslatef( 0.f, 100.f, 0.f );
  /* draw the well */
  GLfloat angle = 0.f;
  GLfloat radius = 5.f;
  int step = 500;
  GLfloat num = 18.f; /* divide circle into 36 pieces */
  /* draw vertical lines */
  for ( angle = 0.f; angle < 2*GL_PI; angle += GL_PI/num ) {
    glBegin( GL_LINE_STRIP );
    for ( i = 0; i < dataSize; i += step ) {
      glVertex3f( x[ i ]+radius*cos(angle), y[ i ], z[ i ]+radius*sin(angle) );
    }
    glEnd();
  }
  /* draw horizontal lines */
  for ( i = 0; i < dataSize; i += step ) {
    glBegin( GL_LINE_STRIP );
    for ( angle = 0.f; angle < 2*GL_PI; angle += GL_PI/num ) {
      glVertex3f( x[ i ] + radius*cos(angle), y[ i ], z[ i ]+radius*sin(angle) );
    }
    glEnd();
  }

  /* return rotate */
  glPopMatrix();
 
  dataSize = 0;
  /* refresh */
  glutSwapBuffers();
}

/* set up render condition or init() in other examples */
void setupRC() {
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };
	
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet
	
    // Enable lighting
    glEnable(GL_LIGHTING);
	
    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
	
    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
	
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void keyboard( unsigned char key, int x, int y ) {
  if ( key == 27 || key == 'Q' || key == 'q' ) {
    exit( 0 );
  }
}

void specialKeys( int key, int x, int y ) {
  switch ( key ) {
  case GLUT_KEY_UP:
    xRot -= 5.f;
    break;
  case GLUT_KEY_DOWN:
    xRot += 5.f;
    break;
  case GLUT_KEY_LEFT:
    yRot -= 5.f;
    break;
  case GLUT_KEY_RIGHT:
    yRot += 5.f;
    break;
  default:
    break;
  }
  if ( key > 356.f ) {
    xRot = 0.f;
  }
  if ( key < -1.f ) {
    xRot = 355.f;
  }
  if ( key > 356.f ) {
    yRot = 0.f;
  }
  if ( key < -1.f ) {
    yRot = 355.f;
  }
  glutPostRedisplay();
}

void mouse( int button, int state, int x, int y ) {
  if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) {
    exit( 0 );
  }
}

/* glut call this when window is resizing or reshape in ohers */
void changeSize( GLsizei w, GLsizei h ) {
  GLfloat range = 120.f;

  /* avoid divided by 0 */
  if ( h == 0 ) {
    h = 1;
  }
  if ( w == 0 ) {
    w = 1;
  }

  //GLfloat aspect = (GLfloat) w / (GLfloat) h;
  /* set view port according to window size */
  glViewport( 0, 0, w, h );

  /* reset coordinates */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  /* setup ortho */
 // /*
  if ( w <= h ) {
    glOrtho( -range, range, -range * h/w, range * h/w, -range*2.f, range*2.f );
  } else {
    glOrtho( -range*w/h, range*w/h, -range, range, -range*2.f, range*2.f );
  }
//  */
  //gluPerspective( 60.f, aspect, 0.f, 200.f );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

int main( int argc, char **argv ) {
  glutInit( &argc, argv );

  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 640, 480 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow( argv[ 0 ] );
  glutDisplayFunc( renderScene );
  glutReshapeFunc( changeSize );
  glutSpecialFunc( specialKeys );
  glutKeyboardFunc( keyboard );
  glutMouseFunc( mouse );

  setupRC();

  glutMainLoop();
  return 0;
}
