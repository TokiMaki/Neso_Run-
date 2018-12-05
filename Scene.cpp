#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
}

CScene::CScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;
}


CScene::~CScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}
