#pragma once
#include "Scene.h"

#define pi 3.141592
#define FPS_TIME 60.0

#define DIR_X 0x01	// 비트연산 동시키 입력
#define DIR_Y 0x02	// 비트연산 동시키 입력
#define DIR_Z 0x04	// 비트연산 동시키 입력
#define DIR__X 0x08	// 비트연산 동시키 입력
#define DIR__Y 0x10	// 비트연산 동시키 입력
#define DIR__Z 0x20	// 비트연산 동시키 입력
#define Camera_ZOOM 0x40	// 비트연산 동시키 입력
#define Camera__ZOOM 0x80	// 비트연산 동시키 입력
#define Camera_Y 0x01
#define Camera__Y 0x02
#define Camera_X 0x04
#define Camera__X 0x08
#define Camera_Z 0x10
#define Camera__Z 0x20
#define Cameramv_X 0x01
#define Cameramv_Y 0x02
#define Cameramv__X 0x04
#define Cameramv__Y 0x08

#define FRAMETIME (current_time - Prevtime)

enum Message { dummy, Title, Charsel, GamePlay, GameOver, Exit};
enum Character { chika, you, riko, hanamaru, ruby, yoshiko, dia, kanan, mari };

class C_Camera;

struct Camera {
	float x;
	float y;
};

class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	C_Camera* m_pCamera{ nullptr };
	int m_nWidth;
	int m_nHeight;

	CScene * arrScene[CScene::SceneTag::Scene_Count];
	CScene * m_pCurrScene;

	float camera_zoom = 0;
	float camera_x = 0;
	float camera_y = 0;
	float camera_z = 0;
	Camera camera;
	GLfloat Prevtime = 0;
	GLfloat current_time;
	GLint current_frame = 0;

	GLuint TitleTex[5];		//텍스처 이름
	GLuint CharSelTex[2];
	GLuint CharacterTex[10];

	GLubyte *pBytes;				// 데이터를 가리킬 포인터
	BITMAPINFO *info;				// 비트맵 헤더 저장할 변수

	float count;

	int mod;

	GLboolean GameMessage{ dummy };

	GLfloat identity[16];

	unsigned char dir = 0;	// 비트연산 동시키 입력
	unsigned char camera_view = 0;	// 비트연산 동시키 입력
	unsigned char camera_move = 0;	// 비트연산 동시키 입력

public:
	CRun_time_Framework();
	~CRun_time_Framework();

	// 필수 함수
	GLvoid Reshape(int w, int h);
	GLvoid draw();
	GLvoid KeyboardDown(unsigned char key, int x, int y);
	GLvoid KeyboardUp(unsigned char key, int x, int y);
	GLvoid SpecialKeyboardDown(int key, int x, int y);
	GLvoid Mouse(int button, int state, int x, int y);
	GLvoid PassiveMotion(int x, int y);
	GLvoid Update();
	GLvoid Init();

	using Idle = GLvoid(*)();
	using Display = GLvoid(*)();
	using Keyboard = GLvoid(*)(unsigned char, int, int);
	using SpecialKeyboard = GLvoid(*)(int, int, int);
	using MouseOp = GLvoid(*)(int, int, int, int);
	using MouseMove = GLvoid(*)(int, int);
	using Resize = GLvoid(*)(int, int);

	// Scene
	void BuildScene();
	void ChangeScene(CScene::SceneTag tag);

	// 만든 함수
	
	GLvoid Key_Update();
	GLvoid background(float r, float g, float b);
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO ** info);
	GLvoid set_TitleTexture();
	GLvoid set_CharSelTexture();
	GLvoid set_CharacterTexture();
	GLint get_textureID(CScene::SceneTag tag, int num);


private:
	Idle m_fpidle{ nullptr };
	Display m_fpRender{ nullptr };
	Keyboard m_fpKeyboardDown{ nullptr };
	Keyboard m_fpKeyboardUp{ nullptr };
	SpecialKeyboard m_fpSpecialKeyDown{ nullptr };
	Resize m_fpReshape{ nullptr };
	MouseOp m_fpMouse{ nullptr };
	MouseMove m_fpMouseMove{ nullptr };

public:
	void Registeridle(Idle func) { m_fpidle = func; }
	void RegisterRender(Display func) { m_fpRender = func; }
	void RegisterKeyboardDown(Keyboard func) { m_fpKeyboardDown = func; }
	void RegisterKeyboardUp(Keyboard func) { m_fpKeyboardUp = func; }
	void RegisterSpecialKeyboardDown(SpecialKeyboard func) { m_fpSpecialKeyDown = func; }
	void RegisterMouse(MouseOp func) { m_fpMouse = func; }
	void RegisterMouseMove(MouseMove func) { m_fpMouseMove = func; }
	void RegisterResize(Resize func) { m_fpReshape = func; }

	void MessagePass(Message msg) { GameMessage = msg; };
};