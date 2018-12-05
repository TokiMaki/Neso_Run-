#pragma once
#include "Scene.h"

#define pi 3.141592
#define FPS_TIME 60

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

class C_Camera;

struct Road_Tree {
	float road_length;
	Road_Tree* Lroad;
	Road_Tree* Rroad;
	float temp;
};

struct Player {
	float x, y, z;
	int dir;		// 0 z--, 1 x--, 2 z++, 3 x++
	int reserve_line;
	int line;		// -1 왼쪽 0 가운데 1 오른쪽
	bool input_rotate;
	float camera_rotate;
};

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

	Road_Tree* main_road;
	Player player;
	float count;

	int mod;

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
	GLvoid vari_init();
	GLvoid Key_Update();

	GLvoid Draw_Ball();
	GLvoid Create_Road();


	// RoadFrame.cpp
	GLvoid RoadFrame(float width, float length);		// width는 수치가 2배로 들어감 ex) 60 넣으면 120의 넓이 함수안에 Push_PopMatrix() 가 붙어있지 않음
	GLvoid Draw_Road();

	// Player.cpp
	GLvoid Player_Update();
	GLvoid Player_Line_Updater();

	GLvoid background(float r, float g, float b);
	GLvoid shape_draw();

	bool Isin_Rect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool NextRoadcheck(int dir);

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

};