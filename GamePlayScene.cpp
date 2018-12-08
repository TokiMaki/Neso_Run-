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
	dre.seed(rd());
	vari_init();
}

void CGamePlayScene::Render()
{
	glEnable(GL_DEPTH_TEST);

	if (player.autorun_state == AutorunState::None)
		Draw_background();
	else if (player.autorun_state == AutorunState::Autorun)
		Draw_Feverbackground();
	
	Shape_draw();
	Draw_UI();

	glDisable(GL_DEPTH_TEST);
}

GLvoid CGamePlayScene::Update(float frametime) {
	if (Start_Timer(frametime)) {
		Player_Update(frametime);
	}
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
		m_pFramework->play_fx(11);
		break;
	case GLUT_KEY_RIGHT:
		m_pFramework->play_fx(11);
		break;
	case GLUT_KEY_UP:
		m_pFramework->play_fx(9);
		break;
	case GLUT_KEY_DOWN:
		m_pFramework->play_fx(12);
		break;
	}
}

void CGamePlayScene::Mouse_Events(int button, int state, int x, int y)
{
}

void CGamePlayScene::PassiveMotion_Events(int x, int y)
{
}

