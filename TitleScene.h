#pragma once
#include "Scene.h"

#define FRAMETIME (current_time - Prevtime)

class TitleScene : public CScene {
public:
	TitleScene(SceneTag tag, CRun_time_Framework * pFramework);
	~TitleScene();

	void BuildObjects() override;
	void Render() override;
	void Update(float frametime) override;
	void Key_Events(unsigned key) override {};
	void SpecialKey_Events(int key, int x, int y) override;
	void PassiveMotion_Events(int x, int y) override;

	// 만든 함수


private:
	bool MouseonBtn[2];
	GLfloat identity[16];
};