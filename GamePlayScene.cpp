#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "GamePlayScene.h"

CGamePlayScene::CGamePlayScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;

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
	//Pixmap
	glPixelZoom(1.0, 1.0);
	glDrawPixels(800, 800, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pFramework->get_Pixmap());
	
	glEnable(GL_DEPTH_TEST);
	
	shape_draw();

	glDisable(GL_DEPTH_TEST);

}

GLvoid CGamePlayScene::Update(float frametime) {
	Player_Update(frametime);
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

