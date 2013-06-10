#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXPOINTS 100
GLint point[ MAXPOINTS ][2];
int pointnum = 0;
int rubberband = 0;

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 1.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { 0.0, 1.0, 1.0 }
};

int face[][4] = {
  { 0, 1, 2, 3 },
  { 1, 5, 6, 2 },
  { 5, 4, 7, 6 },
  { 4, 0, 3, 7 },
  { 4, 5, 1, 0 },
  { 3, 2, 6, 7 }
};

GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };

GLdouble color[][3] = {
  { 1.0, 0.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 1.0, 0.0 },
  { 1.0, 0.0, 1.0 },
  { 0.0, 1.0, 1.0 }
};

int edge[][2] = {
  { 0, 1 },
  { 1, 2 },
  { 2, 3 },
  { 3, 0 },
  { 4, 5 },
  { 5, 6 },
  { 6, 7 },
  { 7, 4 },
  { 0, 4 },
  { 1, 5 },
  { 2, 6 },
  { 3, 7 }
};


void display(void)
{
	int i;
	int j;
	static int r = 0;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

  /* ���_�ʒu�Ǝ������� */
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    /* �����̈ʒu�ݒ� */
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

  /* �}�`�̉�] */
  glRotated((double)r, 0.0, 1.0, 0.0);

    /* �}�`�̐F (��)  */
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

  /* �}�`�̕`�� */
//  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  for (j = 0; j < 6; ++j) {
	  glNormal3dv( normal[j] );
    for (i = 0; i < 4; ++i) {
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();

  glutSwapBuffers();

	  /* �����������]�p�� 0 �ɖ߂� */
  if (++r >= 360) r = 0;

}


void idle(void)
{
  glutPostRedisplay();
}

void resize(int w, int h)
{
  glViewport(0, 0, w, h);

  /* �����ϊ��s��̐ݒ� */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  /* ���f���r���[�ϊ��s��̐ݒ� */
  glMatrixMode(GL_MODELVIEW);
}
void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      /* �A�j���[�V�����J�n */
      glutIdleFunc(idle);
    }
    else {
      /* �A�j���[�V������~ */
      glutIdleFunc(0);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) {
      /* �R�}���� (1�X�e�b�v�����i�߂�) */
        glutPostRedisplay();
    }
    break;
  default:
    break;
  }
}
  
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
    exit(0);
  default:
    break;
  }
}


void motion(int x, int y)
{
  static GLint savepoint[2]; /* �ȑO�̃��o�[�o���h�̒[�_ */

  /* �_�����Z�@�\ ON */
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_INVERT);

  glBegin(GL_LINES);
  if (rubberband) {
    /* �ȑO�̃��o�[�o���h������ */
    glVertex2iv(point[pointnum - 1]);
    glVertex2iv(savepoint);
  }
  /* �V�������o�[�o���h��`�� */
  glVertex2iv(point[pointnum - 1]);
  glVertex2i(x, y);
  glEnd();

  glFlush();

  /* �_�����Z�@�\ OFF */
  glLogicOp(GL_COPY);
  glDisable(GL_COLOR_LOGIC_OP);

  /* ���`�������o�[�o���h�̒[�_��ۑ� */
  savepoint[0] = x;
  savepoint[1] = y;
 
  /* ���`�������o�[�o���h�͎��̃^�C�~���O�ŏ��� */
  rubberband = 1;
}

void init(){
	glClearColor( 1.0, 1.0, 0.0, 1.0 );

	glEnable( GL_DEPTH_TEST );
	glCullFace( GL_FRONT );

  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
  glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}