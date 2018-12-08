#include "stdafx.h"
#include "Run_time_Framework.h"
#include "C_Camera.h"
#include "GamePlayScene.h"
#include "TitleScene.h"
#include "CharSelScene.h"


CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {
	BuildScene();
	ChangeScene(CScene::SceneTag::Title);
}

void CRun_time_Framework::BuildScene()
{
	arrScene[CScene::SceneTag::Title] = new TitleScene(CScene::SceneTag::Title, this);
	arrScene[CScene::SceneTag::CharSel] = new CharSelScene(CScene::SceneTag::CharSel, this);
	//arrScene[CScene::SceneTag::GamePlay] = new CGamePlayScene(CScene::SceneTag::GamePlay, this);
}

void CRun_time_Framework::ChangeScene(CScene::SceneTag tag)
{
	m_pCurrScene = arrScene[tag];
}

GLvoid CRun_time_Framework::draw() {
	background(1, 1, 1);

	m_pCurrScene->Render();

	glutSwapBuffers();
	return GLvoid();
}

GLvoid CRun_time_Framework::Reshape(int w, int h) {
	if (w > 0)
		m_nWidth = w;
	if (h > 0)
		m_nHeight = h;
	glLoadIdentity();
	glViewport(0, 0, m_nWidth, m_nHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, m_nWidth / m_nHeight, 1.0, 1000.0);

	Vector3D vRotate = m_pCamera->GetCameraRotate();
	Vector3D vEye = m_pCamera->GetCameraPos();
	Vector3D vLook = m_pCamera->GetCameraLook();
	Vector3D vUp = m_pCamera->GetCameraUp();
	gluLookAt(vEye.x, vEye.y, vEye.z, vLook.x, vLook.y, vLook.z, vUp.x, vUp.y, vUp.z);
	// gluLookAt(rotatex, rotatey, rotatez, vLook.x, vLook.y, vLook.z, vUp.x, vUp.y, vUp.z);
	glRotatef(vRotate.x, 1.f, 0.f, 0.f);
	glRotatef(vRotate.y, 0.f, 1.f, 0.f);
	glRotatef(vRotate.z, 0.f, 0.f, 1.f);

	//glTranslatef(0, 0, -100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
	return GLvoid();
}

GLvoid CRun_time_Framework::KeyboardDown(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		//m_pCamera->CameraRotate(0);
		dir |= DIR_X;
		break;
	case 'X':
		//m_pCamera->CameraRotate(1);
		dir |= DIR__X;
		break;
	case 'y':
		dir |= DIR_Y;
		break;
	case 'Y':
		dir |= DIR__Y;
		break;
	case 'z':
		dir |= DIR_Z;
		break;
	case 'Z':
		dir |= DIR__Z;
		break;
	case 't':
		dir |= Camera_ZOOM;
		break;
	case 'T':
		dir |= Camera__ZOOM;
		break;
	case 'w':
		break;
	case 'a':
		break;
	case 's':
		break;
	case 'd':
		break;
	case 'i':
		memset(identity, 0, sizeof(identity));
		identity[0] = identity[5] = identity[10] = identity[15] = 1;		// 행렬 초기화
		camera_zoom = 100;
		camera_x = 0;
		camera_y = 0;
		camera_z = 0;
		camera.x = 0;
		camera.y = 0;
		break;
	case '+':
		camera_view |= Camera_Y;
		break;
	case '-':
		camera_view |= Camera__Y;
		break;
	case '1':
		mod = 0;
		break;
	case '2':
		mod = 1;
		break;
	case '7':
		camera_view |= Camera_X;
		break;
	case '8':
		camera_view |= Camera__X;
		break;
	case '6':
		camera_view |= Camera_Z;
		break;
	case '9':
		camera_view |= Camera__Z;
		break;
	}
	Reshape(m_nWidth, m_nHeight);
}

GLvoid CRun_time_Framework::KeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		dir -= DIR_X;
		break;
	case 'X':
		dir -= DIR__X;
		break;
	case 'y':
		dir -= DIR_Y;
		break;
	case 'Y':
		dir -= DIR__Y;
		break;
	case 'z':
		dir -= DIR_Z;
		break;
	case 'Z':
		dir -= DIR__Z;
		break;
	case 't':
		dir -= Camera_ZOOM;
		break;
	case 'T':
		dir -= Camera__ZOOM;
		break;
	case 'w':
		//camera_move -= Cameramv_Y;
		break;
	case 'a':
		//camera_move -= Cameramv_X;
		break;
	case 's':
		//camera_move -= Cameramv__Y;
		break;
	case 'd':
		//camera_move -= Cameramv__X;
		break;
	case '+':
		camera_view -= Camera_Y;
		break;
	case '-':
		camera_view -= Camera__Y;
		break;
	case '7':
		camera_view -= Camera_X;
		break;
	case '8':
		camera_view -= Camera__X;
		break;
	case '6':
		camera_view -= Camera_Z;
		break;
	case '9':
		camera_view -= Camera__Z;
		break;

	}
	Reshape(m_nWidth, m_nHeight);
}

GLvoid CRun_time_Framework::SpecialKeyboardDown(int key, int x, int y) {
	m_pCurrScene->SpecialKey_Events(key, x, y);
}

GLvoid CRun_time_Framework::Mouse(int button, int state, int x, int y) {
	m_pCurrScene->Mouse_Events(button, state, x, y);
	return GLvoid();
}

GLvoid CRun_time_Framework::PassiveMotion(int x, int y)
{
	m_pCurrScene->PassiveMotion_Events(x, y);
	return GLvoid();
}

GLvoid CRun_time_Framework::Init() {
	m_pCamera = new C_Camera();
	m_pCamera->CameraReset();

	srand(time(nullptr));
	myself = this;
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정
	glutCreateWindow("25"); // 윈도우 생성 (윈도우 이름)

	glutDisplayFunc(m_fpRender); // 출력 함수의 지정
	glutReshapeFunc(m_fpReshape);
	glutKeyboardFunc(m_fpKeyboardDown);
	glutKeyboardUpFunc(m_fpKeyboardUp);
	glutSpecialFunc(m_fpSpecialKeyDown);
	glutMouseFunc(m_fpMouse);
	glutPassiveMotionFunc(m_fpMouseMove);
	glutIdleFunc(m_fpidle);

	set_TitleTexture();
	set_CharSelTexture();
	set_CharacterTexture();
	set_IngameObjTexture();
}

GLvoid CRun_time_Framework::Update() {
	current_time = glutGet(GLUT_ELAPSED_TIME);
	current_frame++;

	switch (GameMessage)
	{
	case Charsel:
		GameMessage = dummy;
		ChangeScene(CScene::CharSel);
		break;
	case GamePlay:
		GameMessage = dummy;
		arrScene[CScene::SceneTag::GamePlay] = new CGamePlayScene(CScene::SceneTag::GamePlay, this);
		ChangeScene(CScene::GamePlay);
		break;
	case Exit:
		glutLeaveMainLoop();
		break;
	}

	if (FRAMETIME > 1000.0 / FPS_TIME) {
		m_pCurrScene->Update(FRAMETIME);

		Prevtime = current_time;
		current_frame = 0;
		Reshape(m_nWidth, m_nHeight);
	}
}

CRun_time_Framework::~CRun_time_Framework() {

}