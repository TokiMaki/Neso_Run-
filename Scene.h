#pragma once

class CRun_time_Framework;

class CScene
{
public:
	enum SceneTag {
		Title,
		CharSel,
		GamePlay,
		Result,
		Scene_Count
	};

	CScene();
	CScene(SceneTag tag, CRun_time_Framework *const pFramework);
	virtual ~CScene();

	virtual void BuildObjects() = 0;
	virtual void Update(float frametime) = 0;
	virtual void Render() = 0;
	virtual void Key_Events(unsigned key) = 0;
	virtual void SpecialKey_Events(int key, int x, int y) = 0;
	virtual void Mouse_Events(int button, int state, int x, int y) = 0;
	virtual void PassiveMotion_Events(int x, int y) = 0;

protected:
	SceneTag m_Tag;
	CRun_time_Framework * m_pFramework;
};
