#pragma once
#include "Scene.h"
#include <list>
#include <random>


struct Obstacle {
	int kind;
	float y;
	float z;
};

struct Coin {
	int kind;
	float y;
	float z;
};


class Road_Tree {
private:
	std::list <Obstacle> obstacle;
public:
	float road_length = 0;
	Road_Tree* Lroad = nullptr;
	Road_Tree* Rroad = nullptr;
	void ObstaclePushBack(int kind, float y, float z) { obstacle.push_back({ kind, y, z }); }
	void ObstacleClear() { obstacle.clear(); }
	std::list <Obstacle> GetObstacleList() const { return obstacle; }
};

enum State {
	Idle,
	Jump,
	Slide
};

struct Player {
	float x = 0;
	float y = 0;
	float z = 0;

	int dir = 0;				// 왼쪽 1 오른쪽 0
	int reserve_line = 0;		// -1 왼쪽 0 가운데 1 오른쪽
	int line = 0;				// -1 왼쪽 0 가운데 1 오른쪽

	float speed = 300 / 1000.f;
	float jump_gravity = 200 / 1000.f;

	bool input_rotate = false;
	float camera_rotate = 0;
	float roll = 0;
	State reserve_state = Idle;
	State state = Idle;
	float timer = 0;
};

class CGamePlayScene : public CScene {
public:

	std::random_device rd;
	std::default_random_engine dre;

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


	// RoadFrame.cpp
	GLvoid RoadFrame(float width, float length);		// width는 수치가 2배로 들어감 ex) 60 넣으면 120의 넓이 함수안에 Push_PopMatrix() 가 붙어있지 않음
	GLvoid Draw_Road();
	GLvoid Create_Road();
	GLvoid Create_Obstacle();
	GLvoid Draw_Obstacle();
	GLvoid ObstacleFrame(int kind, float width, float length);

	// Player.cpp
	GLvoid Draw_Player();
	GLvoid Player_Update(float frametime);
	GLvoid Player_Line_Updater(float frametime);
	GLvoid Player_KeyDown_Updater(int key);
	GLvoid Player_Jump(float frametime);
	GLvoid Player_Silde(float frametime);

	GLvoid shape_draw();
	GLvoid Draw_background();
	GLvoid Draw_Feverbackground();

	bool Isin_Rect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool NextRoadcheck(int dir);

private:

	Road_Tree* main_road;
	Player player;
	float count;

	float bg_scroll;
	float bg_degree;
	float fever_highlight;

	GLfloat identity[16];
};