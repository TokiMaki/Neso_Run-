#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "ResultScene.h"

ResultScene::ResultScene(SceneTag tag, CRun_time_Framework * pFramework)
{
	m_Tag = tag;
	m_pFramework = pFramework;

	m_pFramework->set_charID(Character::mari);
	MouseonBtn = false;
	degree = 0;
	scroll = 0;
	score = 123456789;
}

ResultScene::~ResultScene()
{
	if (m_pFramework != nullptr)
		delete m_pFramework;
}

void ResultScene::BuildObjects()
{
}

void ResultScene::Render()
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

	// 리절트
	{
		float size = 250;

		glPushMatrix();
		glTranslatef(0, 300, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.75);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0.5, 0.75);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0.5, 0.5);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.75);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0.5, 0.75);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0.5, 0.5);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0.5);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glPopMatrix();
	}
	// 스코어
	{
		float size = 125;

		glPushMatrix();
		glTranslatef(0, 100, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0.5, 1);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0.5, 0.75);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0.75);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0.5, 1);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0.5, 0.75);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(1, 0.75);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glPopMatrix();
	}
	// 점수
	{
		float size = 50;
		int print_score = m_pFramework->return_score();
		// 십만개부턴 난 몰라요
		if (print_score > 99999)
			print_score = 99999;

		// 일의자리
		{
			int num = print_score % 10;
			glPushMatrix();

			if (print_score > 9999)
				glTranslatef(145, 0, 0);
			else if (print_score > 999)
				glTranslatef(105, 0, 0);
			else if (print_score > 99)
				glTranslatef(70, 0, 0);
			else if (print_score > 9)
				glTranslatef(35, 0, 0);
			else
				glTranslatef(0, 0, 0);

			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glBlendFunc(GL_ONE, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glPopMatrix();
		}
		// 십의 자리
		if (print_score > 9)
		{
			int num = (print_score / 10) % 10;
			glPushMatrix();

			if (print_score > 9999)
				glTranslatef(75, 0, 0);
			else if (print_score > 999)
				glTranslatef(35, 0, 0);
			else if (print_score > 99)
				glTranslatef(0, 0, 0);
			else
				glTranslatef(-35, 0, 0);

			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glBlendFunc(GL_ONE, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glPopMatrix();
		}
		// 백의 자리
		if (print_score > 99)
		{
			int num = (print_score / 100) % 100;
			glPushMatrix();
			if (print_score > 9999)
				glTranslatef(0, 0, 0);
			else if (print_score > 999)
				glTranslatef(-35, 0, 0);
			else
				glTranslatef(-70, 0, 0);

			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glBlendFunc(GL_ONE, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glPopMatrix();
		}
		// 천의 자리
		if (print_score > 999)
		{
			int num = (print_score / 1000) % 1000;
			glPushMatrix();

			if (print_score > 9999)
				glTranslatef(-75, 0, 0);
			else
				glTranslatef(-105, 0, 0);

			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glBlendFunc(GL_ONE, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glPopMatrix();
		}
		// 만의 자리
		if (print_score > 9999)
		{
			int num = (print_score / 10000) % 10000;
			glPushMatrix();

			glTranslatef(-145, 0, 0);

			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size * 1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glBlendFunc(GL_ONE, GL_ONE);
			glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
			glBegin(GL_QUADS);
			glTexCoord2f(0.1 + 0.1*num, 0.125);
			glVertex2f(size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0.125);
			glVertex2f(-size, size*1.25);
			glTexCoord2f(0 + 0.1*num, 0);
			glVertex2f(-size, -size * 1.25);
			glTexCoord2f(0.1 + 0.1*num, 0);
			glVertex2f(size, -size * 1.25);
			glEnd();

			glPopMatrix();
		}
	}

	// 시작 버튼
	{
		float size = 140;
		if (MouseonBtn == true)
			size = 180;
		glPushMatrix();
		glTranslatef(0, -300, 0);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 1));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0.5);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0, 0.25);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(0.5, 0.25);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_UItextureID(m_Tag, 0));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0.5);
		glVertex2f(size, size / 2.0);
		glTexCoord2f(0, 0.5);
		glVertex2f(-size, size / 2.0);
		glTexCoord2f(0, 0.25);
		glVertex2f(-size, -size / 2.0);
		glTexCoord2f(0.5, 0.25);
		glVertex2f(size, -size / 2.0);
		glEnd();

		glPopMatrix();
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	//Draw_Character();

	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

GLvoid ResultScene::Update(float frametime) {
	degree += 0.1 * frametime;
	if (degree > 360)
		degree -= 360;
	scroll += 0.0001*frametime;
}

GLvoid ResultScene::SpecialKey_Events(int key, int x, int y) {
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

void ResultScene::Mouse_Events(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (MouseonBtn == true) {
			m_pFramework->play_fx(0);
			m_pFramework->set_bgm(0);
			m_pFramework->MessagePass(Message::Title);
		}
	}
}

void ResultScene::PassiveMotion_Events(int x, int y)
{
	if (x >= 260 && x <= 540 && y >= 610 && y <= 750)
		MouseonBtn = true;
	else MouseonBtn = false;
}

GLvoid ResultScene::Draw_Character()
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