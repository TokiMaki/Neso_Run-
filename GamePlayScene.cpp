#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "GamePlayScene.h"

CGamePlayScene::CGamePlayScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;
}

CGamePlayScene::~CGamePlayScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}

void CGamePlayScene::BuildObjects()
{
}

void CGamePlayScene::Render()
{
}
