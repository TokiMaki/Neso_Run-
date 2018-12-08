#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "TitleScene.h"

TitleScene::TitleScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;
	scroll = 0;
}

TitleScene::~TitleScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}

void TitleScene::BuildObjects()
{
	MouseonBtn[0] = false;
	MouseonBtn[1] = false;
}

void TitleScene::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	gluLookAt(0, 0, 678, 0, 0, -800, 0, 1, 0);

	// 텍스처 매핑 활성화 
	glEnable(GL_TEXTURE_2D);


	glDisable(GL_DEPTH_TEST);
	// 백그라운드
	{
		glPushMatrix();

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 4));
		glBegin(GL_QUADS);
		glTexCoord2f(1 - scroll, 1 + scroll / 2.0);
		glVertex2f(400, 400);
		glTexCoord2f(0 - scroll, 1 + scroll / 2.0);
		glVertex2f(-400, 400);
		glTexCoord2f(0 - scroll, 0 + scroll / 2.0);
		glVertex2f(-400, -400);
		glTexCoord2f(1 - scroll, 0 + scroll / 2.0);
		glVertex2f(400, -400);
		glEnd();

		glPopMatrix();
	}

	glEnable(GL_BLEND);

	// 로고
	{
		glPushMatrix();
		glTranslatef(0, 150, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex2f(400, 400);
		glTexCoord2f(0, 1);
		glVertex2f(-400, 400);
		glTexCoord2f(0, 0);
		glVertex2f(-400, -400);
		glTexCoord2f(1, 0);
		glVertex2f(400, -400);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex2f(400, 400);
		glTexCoord2f(0, 1);
		glVertex2f(-400, 400);
		glTexCoord2f(0, 0);
		glVertex2f(-400, -400);
		glTexCoord2f(1, 0);
		glVertex2f(400, -400);
		glEnd();

		glPopMatrix();
	}
	// 시작 버튼
	{
		float size = 140;
		if (MouseonBtn[0] == true)
			size = 180;
		glPushMatrix();
		glTranslatef(0, -80, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 3));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0, 1);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 2));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0, 1);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glPopMatrix();
	}
	// 종료버튼
	{
		float size = 140;
		if (MouseonBtn[1] == true)
			size = 180;
		glPushMatrix();
		glTranslatef(0, -250, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 3));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0, 0);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 2));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0, 0);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glPopMatrix();
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glPopMatrix();
}

GLvoid TitleScene::Update(float frametime) {
	scroll += 0.0001*frametime;
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

void TitleScene::Mouse_Events(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (MouseonBtn[0] == true) {
			m_pFramework->play_fx(0);
			m_pFramework->MessagePass(Message::Charsel);
		}
		else if (MouseonBtn[1] == true) {
			m_pFramework->MessagePass(Message::Exit);
		}
	}
}

void TitleScene::PassiveMotion_Events(int x, int y)
{
	if (x >= 260 && x <= 540 && y >= 390 && y <= 530)
		MouseonBtn[0] = true;
	else MouseonBtn[0] = false;

	if (x >= 260 && x <= 540 && y >= 560 && y <= 700)
		MouseonBtn[1] = true;
	else MouseonBtn[1] = false;
}
