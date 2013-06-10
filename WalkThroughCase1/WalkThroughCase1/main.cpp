#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

//=========================================================
// �O���[�o���ϐ�
//=========================================================
extern float data_pos0[][3];
extern float data_normal0[][3];
extern int   data_index_buf0[];
extern int   data_index_num0;

//---------------------------------------------------------
// ���s�����̃x�N�g��
//--------------------------------------------------------- 
float light0_pos[]       = { 1.0, 0.3, 1.0, 0.0 };
float light0_ambient[]   = { 0.2, 0.2, 0.2, 1.0 };
float light0_specular[]  = { 1.0, 1.0, 1.0, 1.0 };
float light0_diffuse[]   = { 0.2, 0.2, 0.2, 1.0 };

float light1_pos[]       = { -1.0, 0.3, -1.0, 0.0 };
float light1_ambient[]   = { 0.0, 0.0, 0.0, 1.0 };
float light1_specular[]  = { 1.0, 1.0, 1.0, 1.0 };
float light1_diffuse[]   = { 0.5, 0.5, 0.5, 1.0 };

//---------------------------------------------------------
// �ގ�
//--------------------------------------------------------- 
float surface_ambient[]  = { 1.0, 1.0, 1.0, 1.0 };
float surface_specular[] = { 0.0, 0.0, 0.0, 1.0 };
float surface_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

//---------------------------------------------------------
// ���̑�
//---------------------------------------------------------
float g_eye[3] = { 40.0, 1.5, 40.0 };
float g_theta = -2.4;

int g_KeyUp    = 0;		// ���󂪉�����Ă�����"1"
int g_KeyDown  = 0;		// ����󂪉�����Ă�����"1"
int g_KeyRight = 0;		// �E��󂪉�����Ă�����"1"
int g_KeyLeft  = 0;		// ����󂪉�����Ă�����"1"

int g_KeyPageUp   = 0;		// ����󂪉�����Ă�����"1"
int g_KeyPageDown = 0;		// ����󂪉�����Ă�����"1"
int g_KeyHome     = 0;		// ����󂪉�����Ă�����"1"
int g_KeyEnd      = 0;		// ����󂪉�����Ă�����"1"


#define PI 3.14159265
//---------------------------------------------------------
// �f�B�X�v���C�֐��i�\���Ɋւ��鏈�����s���j
//---------------------------------------------------------
void display(void)
{
	int i;

	// ��ʃN���A
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

	// �r���[�s��ݒ胂�[�h
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	gluLookAt( g_eye[0], g_eye[1], g_eye[2], g_eye[0]+cos(g_theta), g_eye[1], g_eye[2]+sin(g_theta), 0.0, 1.0, 0.0);
	
	// ���C�e�B���O�ݒ�
	glEnable(GL_LIGHTING);
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos );

	light1_pos[0] = -1.0*cos(g_theta);
	light1_pos[1] = 0.0;
	light1_pos[2] = -1.0*sin(g_theta);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos );

	// �����ݒ�
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  surface_diffuse );
	//glMaterialfv(GL_FRONT, GL_AMBIENT,  surface_ambient );
	//glMaterialfv(GL_FRONT, GL_SPECULAR, surface_specular);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE,  surface_diffuse );
	//glMaterialf(GL_FRONT, GL_SHININESS,  10.0f);

	// ���݂̃��f���r���[�s���ۑ�
	glPushMatrix();
	
	// ���C���[�t���[���ŕ\������p
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// �����̂�`��
	glBegin( GL_TRIANGLES );
	//glBegin( GL_TRIANGLE_STRIP );
	for (i=0; i < data_index_num0; i++ )
	{
		glNormal3fv( data_normal0[ data_index_buf0[i] ] );
		glVertex3fv( data_pos0[ data_index_buf0[i] ] );
	}
	
	glEnd();
	// �P�O�̃��f���r���[�s��ɖ߂�
	glPopMatrix();
	// �t���[���o�b�t�@�̐؂�ւ�
	glutSwapBuffers();
}

//---------------------------------------------------------
// �A�b�v�f�[�g�֐��@���J��Ԃ��Ă΂��
//---------------------------------------------------------
void update()
{
	// �L�[�{�[�h�̖��L�[�������ꂽ�Ƃ��̏�����ǉ�
	if( g_KeyPageUp ) {
		g_eye[1] += 0.1f;
	}
	if( g_KeyPageDown ) {
		g_eye[1] -= 0.1f;
	}
	if( g_KeyHome ) {
		g_eye[0] += cos(g_theta-PI*0.5) * 0.15;
		g_eye[2] += sin(g_theta-PI*0.5) * 0.15;
	}
	if( g_KeyEnd ) {
		g_eye[0] += cos(g_theta+PI*0.5) * 0.15;
		g_eye[2] += sin(g_theta+PI*0.5) * 0.15;
	}

	if( g_KeyUp    == 1 ) {
		g_eye[0] += cos(g_theta) * 0.15;
		g_eye[2] += sin(g_theta) * 0.15;
	}
	if( g_KeyDown  == 1 ) {
		g_eye[0] -= cos(g_theta) * 0.15;
		g_eye[2] -= sin(g_theta) * 0.15;
	}
	if( g_KeyRight == 1 ) {
		g_theta += 0.03;
	}
	if( g_KeyLeft  == 1 ) {
		g_theta -= 0.03;
	}

	// ��ʂ��X�V(�f�B�X�v���C�֐����Ă΂��)
	glutPostRedisplay();
}

//---------------------------------------------------------
// �������֐�
//---------------------------------------------------------
void init(void)
{
	// �w�i�F�ݒ�
	glClearColor(0.0, 0.0, 1.0, 1.0);
	// �f�v�X�e�X�g(���s������e�X�g)�L��
	glEnable(GL_DEPTH_TEST);
	// ���C�e�B���O�L��
	glEnable(GL_LIGHTING);
	// ���C�g0��L��
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos      );
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient  ); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse  );
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular );

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos      );
	glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient  ); 
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse  );
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular );
}

//---------------------------------------------------------
// ���L�[���������Ƃ��Ă΂��֐�
//---------------------------------------------------------
void specialkey( int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		g_KeyLeft = 1;
		break;
	case GLUT_KEY_DOWN:
		g_KeyDown = 1;
		break;
	case GLUT_KEY_UP:
		g_KeyUp = 1;
		break;
	case GLUT_KEY_RIGHT:
		g_KeyRight = 1;
		break;
	case GLUT_KEY_PAGE_UP:
		g_KeyPageUp = 1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		g_KeyPageDown = 1;
		break;
	case GLUT_KEY_HOME:
		g_KeyHome = 1;
		break;
	case GLUT_KEY_END:
		g_KeyEnd = 1;
		break;
	}
}

//---------------------------------------------------------
// ���L�[�𗣂����Ƃ��Ă΂��֐�
//---------------------------------------------------------
void upspecialkey( int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		g_KeyLeft = 0;
		break;
	case GLUT_KEY_DOWN:
		g_KeyDown = 0;
		break;
	case GLUT_KEY_UP:
		g_KeyUp = 0;
		break;
	case GLUT_KEY_RIGHT:
		g_KeyRight = 0;
		break;
	case GLUT_KEY_PAGE_UP:
		g_KeyPageUp = 0;
		break;
	case GLUT_KEY_PAGE_DOWN:
		g_KeyPageDown = 0;
		break;
	case GLUT_KEY_HOME:
		g_KeyHome = 0;
		break;
	case GLUT_KEY_END:
		g_KeyEnd = 0;
		break;
	}
}

//---------------------------------------------------------
// Window�T�C�Y���ύX���ꂽ�Ƃ��Ă΂��֐�
// w:�E�B���h�E�̕��@h:�E�B���h�E�̍���
//---------------------------------------------------------
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0f, 100.0);
	//glOrtho( -w/200.0, w/200.0, -h/200.0, h/200.0, 1.0, 100.0 );
}

//---------------------------------------------------------
// ���������I���I�t�ݒ�
//---------------------------------------------------------
typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( int );
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;
void setVSync( int interval )
{
	const char * extensions = (const char *)glGetString( GL_EXTENSIONS );
	if( strstr( extensions, "WGL_EXT_swap_control" ) == 0 ) {
		return; // Error: WGL_EXT_swap_control extension not supported on your computer.\n");
	}
	else {
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );
	}
	if( wglSwapIntervalEXT ) {
		wglSwapIntervalEXT(interval);
	}
}

//---------------------------------------------------------
// ���C���֐�
//---------------------------------------------------------
int main(int argc, char *argv[])
{
	// OpenGL������
	glutInit(&argc, argv);
	// �f�B�X�v���C���[�h������
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// �E�B���h�E�ʒu������
	glutInitWindowPosition(100 , 50);
	// �E�B���h�E�T�C�Y������
	glutInitWindowSize( 640, 480 );
	//�E�B���h�E�쐬
	glutCreateWindow("test");
	// ���Ԋu�ŌĂяo�����֐��Z�b�g
	glutIdleFunc( update );
	// �`��֐��Z�b�g
	glutDisplayFunc(display);
	// �E�B���h�E�T�C�Y���ύX�����ƌĂяo�����֐��Z�b�g
	glutReshapeFunc(resize);
	// �L�[�{�[�h�������ꂽ�Ƃ��ɌĂяo�����֐��Z�b�g
	glutSpecialFunc(specialkey);
	// �L�[�{�[�h�𗣂����Ƃ��ɌĂяo�����֐��Z�b�g
	glutSpecialUpFunc(upspecialkey);

	setVSync(1);
	// ������
	init();
	// ���C�����[�v���s
	glutMainLoop();
	
	return 0;
}