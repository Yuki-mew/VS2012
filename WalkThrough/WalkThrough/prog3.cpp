#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

GLuint objects;
#define RadToDeg 0.01753

int g_w;
int g_h;
double theta = 0.0;
double v = 0.0;
double t = 0.0;

void scene(void)
{
  /* ���̂̐F */
  static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
  static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
  static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
  static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
  static GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  int i, j;

  objects = glGenLists( 1 );
  glNewList( objects, GL_COMPILE );

  /* �Ԃ��� */
  glPushMatrix();
  glTranslated(0.0, 0.0, -3.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(1.0);
  glPopMatrix();

  /* �΂̔� */
  glPushMatrix();
  glTranslated(0.0, 0.0, 3.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
  glutSolidCube(1.0);
  glPopMatrix();

  /* ���� */
  glPushMatrix();
  glTranslated(-3.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
  glutSolidCube(1.0);
  glPopMatrix();

  /* ���F���� */
  glPushMatrix();
  glTranslated(3.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
  glutSolidCube(1.0);
  glPopMatrix();

  /* �n�� */
  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  for (j = -5; j < 5; ++j) {
    for (i = -5; i < 5; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, -0.5, (GLdouble)j);
      glVertex3d((GLdouble)i, -0.5, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)j);
    }
  }
  glEnd();
}

void display(void)
{
  static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* �����̈ʒu */

  static double ex = 0.0, ez = 0.0; /* ���_�̈ʒu */
  static double vx= 0.0, vz = 0.0;
  static double r = 0.0;

  /* ��ʃN���A */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* ���f���r���[�ϊ��s��̏����� */
  glLoadIdentity();

  r += theta * t;

  if( r < 0 )
	  vx = v * sin( fabs( r ) * RadToDeg);
  else
	  vx = -v * sin( fabs( r ) * RadToDeg);
 
  vz = v * cos( fabs( r ) * RadToDeg);

	  ex += vx * t;
	  ez += vz * t;

  /* ���_�̈ړ� */
  glRotated( r, 0.0, 1.0, 0.0 );
  glTranslated( ex, 0.0, ez );

  /* �����̈ʒu��ݒ� */
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glCallList( objects );
  glutSwapBuffers();
  /* �V�[���̕`�� */
  scene();

  glFlush();
}

void resize(int w, int h)
{
  /* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
  glViewport(0, 0, w, h);

  /* �����ϊ��s��̎w�� */
  glMatrixMode(GL_PROJECTION);

  /* �����ϊ��s��̏����� */
  glLoadIdentity();
  gluPerspective(60.0, (double)w / (double)h, 1.0, 1000.0);

  /* ���f���r���[�ϊ��s��̎w�� */
  glMatrixMode(GL_MODELVIEW);

  g_w = w;
  g_h = h;
}

void motion( int x, int y ){
	if( x < g_w / 2 ) theta = -( fabs( 0.5 * g_w - x ) / ( 0.5 * g_w )) * 2.0;
	if( x > g_w / 2 ) theta =  ( fabs( 0.5 * g_w - x ) / ( 0.5 * g_w )) * 2.0;

	if( y < g_h / 2 )  fabs( 0.5 * g_h - y ) / 2000;
	if( y > g_h / 2 ) -fabs( 0.5 * g_h - y ) / 3000;

}

void idle(){
	t += 0.01;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
  /* ESC �� q ���^�C�v������I�� */
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

void init(void)
{
  /* �����ݒ� */
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize( 600, 600 );
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  
  glutIdleFunc(idle);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);

  init();

  glutMainLoop();
  return 0;
}