#pragma once

class CRun_time_Framework;

class CScene
{
public:
	enum SceneTag {
		GamePlay,
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

protected:
	SceneTag m_Tag;
	CRun_time_Framework * m_pFramework;
};
