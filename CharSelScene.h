#pragma once
#include "Scene.h"

#define FRAMETIME (current_time - Prevtime)

class CharSelScene : public CScene {
public:
	CharSelScene(SceneTag tag, CRun_time_Framework * pFramework);
	~CharSelScene();

	void BuildObjects() override;
	void Render() override;
	void Update(float frametime) override;
	void Key_Events(unsigned key) override {};
	void SpecialKey_Events(int key, int x, int y) override;
	void Mouse_Events(int button, int state, int x, int y) override;
	void PassiveMotion_Events(int x, int y) override;

	// 만든 함수
	GLvoid Draw_Character();

private:
	bool MouseonBtn[3];
	float degree;
	GLfloat identity[16];
};
