#pragma once
#include "Scene.h"

#define FRAMETIME (current_time - Prevtime)

class ResultScene : public CScene {
public:
	ResultScene(SceneTag tag, CRun_time_Framework * pFramework);
	~ResultScene();

	void BuildObjects() override;
	void Render() override;
	void Update(float frametime) override;
	void Key_Events(unsigned key) override {};
	void SpecialKey_Events(int key, int x, int y) override;
	void Mouse_Events(int button, int state, int x, int y) override;
	void PassiveMotion_Events(int x, int y) override;

	// ���� �Լ�
	GLvoid Draw_Character();

private:
	bool MouseonBtn;
	int score;
	float degree;
	float scroll;
	GLfloat identity[16];
};