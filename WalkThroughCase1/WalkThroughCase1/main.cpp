#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

//=========================================================
// グローバル変数
//=========================================================
extern float data_pos0[][3];
extern float data_normal0[][3];
extern int   data_index_buf0[];
extern int   data_index_num0;

//---------------------------------------------------------
// 平行光源のベクトル
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
// 材質
//--------------------------------------------------------- 
float surface_ambient[]  = { 1.0, 1.0, 1.0, 1.0 };
float surface_specular[] = { 0.0, 0.0, 0.0, 1.0 };
float surface_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

//---------------------------------------------------------
// その他
//---------------------------------------------------------
float g_eye[3] = { 40.0, 1.5, 40.0 };
float g_theta = -2.4;

int g_KeyUp    = 0;		// 上矢印が押されていたら"1"
int g_KeyDown  = 0;		// 下矢印が押されていたら"1"
int g_KeyRight = 0;		// 右矢印が押されていたら"1"
int g_KeyLeft  = 0;		// 左矢印が押されていたら"1"

int g_KeyPageUp   = 0;		// 左矢印が押されていたら"1"
int g_KeyPageDown = 0;		// 左矢印が押されていたら"1"
int g_KeyHome     = 0;		// 左矢印が押されていたら"1"
int g_KeyEnd      = 0;		// 左矢印が押されていたら"1"


#define PI 3.14159265
//---------------------------------------------------------
// ディスプレイ関数（表示に関する処理を行う）
//---------------------------------------------------------
void display(void)
{
	int i;

	// 画面クリア
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

	// ビュー行列設定モード
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	gluLookAt( g_eye[0], g_eye[1], g_eye[2], g_eye[0]+cos(g_theta), g_eye[1], g_eye[2]+sin(g_theta), 0.0, 1.0, 0.0);
	
	// ライティング設定
	glEnable(GL_LIGHTING);
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos );

	light1_pos[0] = -1.0*cos(g_theta);
	light1_pos[1] = 0.0;
	light1_pos[2] = -1.0*sin(g_theta);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_pos );

	// 質感設定
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,  surface_diffuse );
	//glMaterialfv(GL_FRONT, GL_AMBIENT,  surface_ambient );
	//glMaterialfv(GL_FRONT, GL_SPECULAR, surface_specular);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE,  surface_diffuse );
	//glMaterialf(GL_FRONT, GL_SHININESS,  10.0f);

	// 現在のモデルビュー行列を保存
	glPushMatrix();
	
	// ワイヤーフレームで表示する用
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// 立方体を描画
	glBegin( GL_TRIANGLES );
	//glBegin( GL_TRIANGLE_STRIP );
	for (i=0; i < data_index_num0; i++ )
	{
		glNormal3fv( data_normal0[ data_index_buf0[i] ] );
		glVertex3fv( data_pos0[ data_index_buf0[i] ] );
	}
	
	glEnd();
	// １つ前のモデルビュー行列に戻す
	glPopMatrix();
	// フレームバッファの切り替え
	glutSwapBuffers();
}

//---------------------------------------------------------
// アップデート関数　※繰り返し呼ばれる
//---------------------------------------------------------
void update()
{
	// キーボードの矢印キーが押されたときの処理を追加
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

	// 画面を更新(ディスプレイ関数が呼ばれる)
	glutPostRedisplay();
}

//---------------------------------------------------------
// 初期化関数
//---------------------------------------------------------
void init(void)
{
	// 背景色設定
	glClearColor(0.0, 0.0, 1.0, 1.0);
	// デプステスト(奥行き判定テスト)有効
	glEnable(GL_DEPTH_TEST);
	// ライティング有効
	glEnable(GL_LIGHTING);
	// ライト0を有効
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
// 矢印キーを押したとき呼ばれる関数
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
// 矢印キーを離したとき呼ばれる関数
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
// Windowサイズが変更されたとき呼ばれる関数
// w:ウィンドウの幅　h:ウィンドウの高さ
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
// 垂直同期オンオフ設定
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
// メイン関数
//---------------------------------------------------------
int main(int argc, char *argv[])
{
	// OpenGL初期化
	glutInit(&argc, argv);
	// ディスプレイモード初期化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// ウィンドウ位置初期化
	glutInitWindowPosition(100 , 50);
	// ウィンドウサイズ初期化
	glutInitWindowSize( 640, 480 );
	//ウィンドウ作成
	glutCreateWindow("test");
	// 一定間隔で呼び出される関数セット
	glutIdleFunc( update );
	// 描画関数セット
	glutDisplayFunc(display);
	// ウィンドウサイズが変更されると呼び出される関数セット
	glutReshapeFunc(resize);
	// キーボードが押されたときに呼び出される関数セット
	glutSpecialFunc(specialkey);
	// キーボードを離したときに呼び出される関数セット
	glutSpecialUpFunc(upspecialkey);

	setVSync(1);
	// 初期化
	init();
	// メインループ実行
	glutMainLoop();
	
	return 0;
}