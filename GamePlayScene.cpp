#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "GamePlayScene.h"

CGamePlayScene::CGamePlayScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;

	dre.seed(rd());
	vari_init();
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
	glEnable(GL_DEPTH_TEST);

	Draw_background();
	Draw_Feverbackground();
	
	Shape_draw();

	glDisable(GL_DEPTH_TEST);
}

GLvoid CGamePlayScene::Update(float frametime) {
	Player_Update(frametime);
	bg_scroll += 0.00001*frametime;
	bg_degree += 0.05*frametime;
	if (bg_degree > 360)
		bg_degree -= 360;
	fever_highlight += 0.025*frametime;
	if (fever_highlight > 50)
		fever_highlight -= 50;
}

GLvoid CGamePlayScene::SpecialKey_Events(int key, int x, int y) {
	Player_KeyDown_Updater(key);
	switch (key) {
	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;
	}
}

void CGamePlayScene::Mouse_Events(int button, int state, int x, int y)
{
}

void CGamePlayScene::PassiveMotion_Events(int x, int y)
{
}

