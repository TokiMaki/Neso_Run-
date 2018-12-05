#pragma once
#include "Scene.h"

class CGamePlayScene : public CScene {
public:
	CGamePlayScene(SceneTag tag, CRun_time_Framework * pFramework);
	~CGamePlayScene();

	void BuildObjects() override;
	void Render() override;
	void Update(GLint frame) override {};
	void Key_Events(unsigned key) override {};
private:

};