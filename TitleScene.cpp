#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;
}

TitleScene::~TitleScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}

void TitleScene::BuildObjects()
{
}

void TitleScene::Render()
{

}

GLvoid TitleScene::Update(float frametime) {
	
}

GLvoid TitleScene::SpecialKey_Events(int key, int x, int y) {
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

