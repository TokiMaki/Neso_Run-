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
	int dir = 0;		// 0 z--, 1 x--, 2 z++, 3 x++
	int reserve_line = 0;
	int line;		// -1 ���� 0 ��� 1 ������
	bool input_rotate;
	float camera_rotate;
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

	// ���� �Լ�
	GLvoid vari_init();

	GLvoid Draw_Ball();
	GLvoid Create_Road();


	// RoadFrame.cpp
	GLvoid RoadFrame(float width, float length);		// width�� ��ġ�� 2��� �� ex) 60 ������ 120�� ���� �Լ��ȿ� Push_PopMatrix() �� �پ����� ����
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

	int mod;

	GLfloat identity[16];
};