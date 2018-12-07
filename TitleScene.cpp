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
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	gluLookAt(0, 0, 500, 0, 0, -500, 0, 1, 0);

	// 텍스처 매핑 활성화 
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	//glBindTexture(GL_TEXTURE_2D, titleTex[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex2f(100, 100);
	glTexCoord2f(0, 1);
	glVertex2f(-100, 100);
	glTexCoord2f(0, 0);
	glVertex2f(-100, -100);
	glTexCoord2f(1, 0);
	glVertex2f(100, -100);
	glEnd();

	glBlendFunc(GL_ONE, GL_ONE);
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex2f(100, 100);
	glTexCoord2f(0, 1);
	glVertex2f(-100, 100);
	glTexCoord2f(0, 0);
	glVertex2f(-100, -100);
	glTexCoord2f(1, 0);
	glVertex2f(100, -100);
	glEnd();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glPopMatrix();
}

GLvoid TitleScene::Update(float frametime) {
	
}

GLvoid TitleScene::SpecialKey_Events(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		m_pFramework->MessagePass(Message::GamePlay);
		break;

	case GLUT_KEY_RIGHT:

		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;
	}
}

