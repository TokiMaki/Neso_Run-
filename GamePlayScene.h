#pragma once
#include "Scene.h"

#define FRAMETIME (current_time - Prevtime)

struct Road_Tree {
	float road_length = 0;
	Road_Tree* Lroad = NULL;
	Road_Tree* Rroad = NULL;
	float temp = 0;
};

struct Player {
	float x = 0;
	float y = 0;
	float z = 0;
	int dir = 0;		// 왼쪽 1 오른쪽 0
	int reserve_line = 0;
	int line = 0;		// -1 왼쪽 0 가운데 1 오른쪽
	bool input_rotate = false;
	float camera_rotate = 0;
};

class CGamePlayScene : public CScene {
public:
	CGamePlayScene(SceneTag tag, CRun_time_Framework * pFramework);
	~CGamePlayScene();

	void BuildObjects() override;
	void Render() override;
	void Update(float frametime) override;
	void Key_Events(unsigned key) override {};
	void SpecialKey_Events(int key, int x, int y) override;
	void Mouse_Events(int button, int state, int x, int y) override;
	void PassiveMotion_Events(int x, int y) override;

	// 만든 함수
	GLvoid vari_init();

	GLvoid Draw_Ball();
	GLvoid Create_Road();


	// RoadFrame.cpp
	GLvoid RoadFrame(float width, float length);		// width는 수치가 2배로 들어감 ex) 60 넣으면 120의 넓이 함수안에 Push_PopMatrix() 가 붙어있지 않음
	GLvoid Draw_Road();

	// Player.cpp
	GLvoid Player_Update(float frametime);
	GLvoid Player_Line_Updater();

	GLvoid shape_draw();

	bool Isin_Rect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool NextRoadcheck(int dir);
private:

	Road_Tree* main_road;
	Player player;
	float count;

	GLfloat identity[16];
};