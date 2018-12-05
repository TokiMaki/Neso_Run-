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
	virtual void Update(GLint frame) = 0;
	virtual void Render() = 0;
	virtual void Key_Events(unsigned key) = 0;

protected:
	SceneTag m_Tag;
	CRun_time_Framework * m_pFramework;
};
