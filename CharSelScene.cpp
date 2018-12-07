#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "CharSelScene.h"

CharSelScene::CharSelScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;
}

CharSelScene::~CharSelScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}

void CharSelScene::BuildObjects()
{
	MouseonBtn[0] = false;
	MouseonBtn[1] = false;
	MouseonBtn[2] = false;
}

void CharSelScene::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	gluLookAt(0, 0, 678, 0, 0, -800, 0, 1, 0);

	// �ؽ�ó ���� Ȱ��ȭ 
	glEnable(GL_TEXTURE_2D);


	glDisable(GL_DEPTH_TEST);
	// ��׶���
	{
		glPushMatrix();

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 0));
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

	glEnable(GL_BLEND);

	// ĳ���� ����Ʈ
	{
		float size = 250;

		glPushMatrix();
		glTranslatef(0, 300, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.75);
		glVertex2f(size, size / 4.0);
		glTexCoord2f(0, 0.75);
		glVertex2f(-size, size / 4.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, -size / 4.0);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, -size / 4.0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.75);
		glVertex2f(size, size / 4.0);
		glTexCoord2f(0, 0.75);
		glVertex2f(-size, size / 4.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, -size / 4.0);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, -size / 4.0);
		glEnd();

		glPopMatrix();
	}
	// ���� ��ư
	{
		float size = 50;
		if (MouseonBtn[0] == true)
			size = 70;
		glPushMatrix();
		glTranslatef(-350, 0, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(0.25, 1);
		glVertex2f(size, size);
		glTexCoord2f(0, 1);
		glVertex2f(-size, size);
		glTexCoord2f(0, 0.75);
		glVertex2f(-size, -size);
		glTexCoord2f(0.25, 0.75);
		glVertex2f(size, -size);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(0.25, 1);
		glVertex2f(size, size);
		glTexCoord2f(0, 1);
		glVertex2f(-size, size);
		glTexCoord2f(0, 0.75);
		glVertex2f(-size, -size);
		glTexCoord2f(0.25, 0.75);
		glVertex2f(size, -size);
		glEnd();

		glPopMatrix();
	}
	// ������ ��ư
	{
		float size = 50;
		if (MouseonBtn[1] == true)
			size = 70;
		glPushMatrix();
		glTranslatef(350, 0, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 1);
		glVertex2f(size, size);
		glTexCoord2f(0.25, 1);
		glVertex2f(-size, size);
		glTexCoord2f(0.25, 0.75);
		glVertex2f(-size, -size);
		glTexCoord2f(0.5, 0.75);
		glVertex2f(size, -size);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 1);
		glVertex2f(size, size);
		glTexCoord2f(0.25, 1);
		glVertex2f(-size, size);
		glTexCoord2f(0.25, 0.75);
		glVertex2f(-size, -size);
		glTexCoord2f(0.5, 0.75);
		glVertex2f(size, -size);
		glEnd();

		glPopMatrix();
	}
	// ���� ��ư
	{
		float size = 140;
		if (MouseonBtn[2] == true)
			size = 180;
		glPushMatrix();
		glTranslatef(0, -300, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 1));
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
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_textureID(m_Tag, 0));
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

GLvoid CharSelScene::Update(float frametime) {

}

GLvoid CharSelScene::SpecialKey_Events(int key, int x, int y) {
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

void CharSelScene::Mouse_Events(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (MouseonBtn[0] == true)
			m_pFramework->MessagePass(Message::GamePlay);
		else if (MouseonBtn[2] == true) {
			m_pFramework->MessagePass(Message::GamePlay);
		}
	}
}

void CharSelScene::PassiveMotion_Events(int x, int y)
{
	if (x >= 0 && x <= 100 && y >= 350 && y <= 450)
		MouseonBtn[0] = true;
	else MouseonBtn[0] = false;

	if (x >= 700 && x <= 800 && y >= 350 && y <= 450)
		MouseonBtn[1] = true;
	else MouseonBtn[1] = false;

	if (x >= 260 && x <= 540 && y >= 610 && y <= 750)
		MouseonBtn[2] = true;
	else MouseonBtn[2] = false;
}