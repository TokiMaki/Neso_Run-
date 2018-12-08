#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "CharSelScene.h"

CharSelScene::CharSelScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;

	m_pFramework->set_charID(Character::mari);
	MouseonBtn[0] = false;
	MouseonBtn[1] = false;
	MouseonBtn[2] = false;
	degree = 0;
	scroll = 0;
}

CharSelScene::~CharSelScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}

void CharSelScene::BuildObjects()
{
}

void CharSelScene::Render()
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
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 2));
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

	// 캐릭터 셀렉트
	{
		float size = 250;

		glPushMatrix();
		glTranslatef(0, 300, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
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
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
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
	// 왼쪽 버튼
	{
		float size = 50;
		if (MouseonBtn[0] == true)
			size = 70;
		glPushMatrix();
		glTranslatef(-350, 0, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
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
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
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
	// 오른쪽 버튼
	{
		float size = 50;
		if (MouseonBtn[1] == true)
			size = 70;
		glPushMatrix();
		glTranslatef(350, 0, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
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
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
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
	// 시작 버튼
	{
		float size = 140;
		if (MouseonBtn[2] == true)
			size = 180;
		glPushMatrix();
		glTranslatef(0, -300, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
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
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
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

	Draw_Character();

	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

GLvoid CharSelScene::Update(float frametime) {
	degree += 0.1 * frametime;
	if (degree > 360)
		degree -= 360;
	scroll += 0.0001*frametime;
}

GLvoid CharSelScene::SpecialKey_Events(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		m_pFramework->play_voice(m_pFramework->get_charID(), 0);
		break;
	case GLUT_KEY_RIGHT:
		m_pFramework->play_voice(m_pFramework->get_charID(), 1);
		break;
	case GLUT_KEY_UP:
		m_pFramework->play_voice(m_pFramework->get_charID(), 2);
		break;
	case GLUT_KEY_DOWN:
		m_pFramework->play_voice(m_pFramework->get_charID(), 3);
		break;
	case GLUT_KEY_SHIFT_R:
		m_pFramework->play_voice(m_pFramework->get_charID(), 4);
		break;
	case GLUT_KEY_F12:
		m_pFramework->play_voice(m_pFramework->get_charID(), 5);
		break;
	}
}

void CharSelScene::Mouse_Events(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (MouseonBtn[0] == true) {
			m_pFramework->play_fx(1);
			int ID = m_pFramework->get_charID() - 1;
			if (ID < 0)
				ID += 9;
			m_pFramework->set_charID(ID);
		}
		else if (MouseonBtn[1] == true) {
			m_pFramework->play_fx(1);
			int ID = m_pFramework->get_charID() + 1;
			if (ID > 8)
				ID -= 9;
			m_pFramework->set_charID(ID);
		}
		else if (MouseonBtn[2] == true) {
			m_pFramework->play_fx(0);
			m_pFramework->set_bgm(1);
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

GLvoid CharSelScene::Draw_Character()
{
	glPushMatrix();

	GLUquadricObj *sphere = gluNewQuadric();

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);

	glRotatef(degree, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_ChartextureID(m_pFramework->get_charID()));
	gluSphere(sphere, 100, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);

	glPopMatrix();
}