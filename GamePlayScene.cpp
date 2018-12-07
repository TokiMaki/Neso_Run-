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
	glEnable(GL_DEPTH_TEST);
	
	shape_draw();

	glDisable(GL_DEPTH_TEST);

}

GLvoid CGamePlayScene::Update(float frametime) {
	Player_Update(frametime);
}

GLvoid CGamePlayScene::SpecialKey_Events(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		printf("left\n");
		if (NextRoadcheck(1)) {
			printf("left in\n");
			player.input_rotate = true;
			player.dir = 1;
		}
		else if (!player.input_rotate) {
			if (player.reserve_line > -1)
				player.reserve_line -= 1;
		}
		break;

	case GLUT_KEY_RIGHT:
		printf("right\n");
		if (NextRoadcheck(0)) {
			printf("right in\n");
			player.input_rotate = true;
			player.dir = 0;
		}
		else if (!player.input_rotate) {
			if (player.reserve_line < 1)
				player.reserve_line += 1;
		}
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

