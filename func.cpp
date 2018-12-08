#include "stdafx.h"
#include "Run_time_Framework.h"
#include "GamePlayScene.h"

#define pi 3.141592

GLvoid CRun_time_Framework::Key_Update() {

	if (dir & DIR_X) {		// 비트 연산은 &가 단 하나!
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 1.f, 0.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR_Y) {
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR_Z) {
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 0.f, 0.f, 1.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}
	if (dir & DIR__X) {
		glPushMatrix();
		{
			glRotatef(-0.5f * (current_time - Prevtime), 1.f, 0.f, 0.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR__Y) {
		glPushMatrix();
		{
			glRotatef(-0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR__Z) {
		glPushMatrix();
		{
			glRotatef(-0.5f * (current_time - Prevtime), 0.f, 0.f, 1.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & Camera_ZOOM) {
		camera_zoom += 5;
	}

	if (dir & Camera__ZOOM) {
		camera_zoom -= 5;
	}

	if (camera_view & Camera_X) {
		camera_x += 5;
	}
	if (camera_view & Camera__X) {
		camera_x -= 5;
	}

	if (camera_view & Camera_Y) {
		camera_y += 5;
	}

	if (camera_view & Camera__Y) {
		camera_y -= 5;
	}

	if (camera_view & Camera_Z) {
		camera_z += 5;
	}

	if (camera_view & Camera__Z) {
		camera_z -= 5;
	}

	if (camera_move & Cameramv_X) {
		camera.x += 5;
	}
	if (camera_move & Cameramv__X) {
		camera.x -= 5;
	}
	if (camera_move & Cameramv_Y) {
		camera.y += 5;
	}
	if (camera_move & Cameramv__Y) {
		camera.y -= 5;
	}

}

GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CGamePlayScene::vari_init() {

	memset(identity, 0, sizeof(identity));
	identity[0] = identity[5] = identity[10] = identity[15] = 1;		// 행렬 초기화

	main_road = nullptr;


	player.x = 0;
	player.y = 0;
	player.z = 0;

	player.dir = 0;				// 왼쪽 1 오른쪽 0
	player.reserve_line = 0;		// -1 왼쪽 0 가운데 1 오른쪽
	player.line = 0;				// -1 왼쪽 0 가운데 1 오른쪽

	player.speed = 150 / 1000.f;
	player.jump_gravity = 100 / 1000.f;

	player.input_rotate = false;
	player.camera_rotate = 0;
	player.roll = 0;
	player.reserve_state = Idle;
	player.state = Idle;
	player.timer = 0;
	player.death = false;

	death_timer = 1;


	bg_scroll = 0;
	bg_degree = 0;
	fever_highlight = 0;

	Create_Road();
}

GLvoid CGamePlayScene::Shape_draw() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	/*
	if (mod == 0) {
		gluLookAt(camera.x, camera.y, camera_zoom, 0, 0, -100, sin(camera_z / 180 * pi), cos(camera_z / 180 * pi), 0.0);
		glMultMatrixf(identity);
	}
	*/
	// 원래시점
	gluLookAt(player.x + sin(pi / 180 * (player.camera_rotate)) * 50, 20, player.z + cos(pi / 180 * (player.camera_rotate)) * 50, player.x, 20, player.z, 0, 1, 0);
	// 탑뷰시점
	//gluLookAt(player.x, 200, player.z, player.x, 0, player.z, 0, 0, -1);


	glPushMatrix();
	Draw_Player();
	glPopMatrix();

	glPushMatrix();

	Draw_Road();
	glPopMatrix();


	glPopMatrix();

}

GLvoid CGamePlayScene::Draw_background()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	// 하늘
	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(4));
	glBegin(GL_QUADS);
	glTexCoord2f(1 + bg_scroll, 1);
	glVertex3f(400, 400, -500);
	glTexCoord2f(1 + bg_scroll, 0);
	glVertex3f(400, -400, -500);
	glTexCoord2f(0 + bg_scroll, 0);
	glVertex3f(-400, -400, -500);
	glTexCoord2f(0 + bg_scroll, 1);
	glVertex3f(-400, 400, -500);
	glEnd();

	glEnable(GL_BLEND);
	// 뒤에 돌아가는 바람개비
	{
		float size = 50;
		glPushMatrix();
		glTranslatef(-240, 70, 0);

		glPushMatrix();
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(6));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(5));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 25, 0);
		glRotatef(bg_degree, 0, 0, 1);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(6));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(5));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();
		glPopMatrix();

		glPopMatrix();

		glPushMatrix();
		glTranslatef(240, 70, 0);

		glPushMatrix();
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(6));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(5));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(1, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 25, 0);
		glRotatef(-bg_degree, 0, 0, 1);

		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(6));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(5));
		glBegin(GL_QUADS);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(size, size, -500);
		glTexCoord2f(0.5, 0);
		glVertex3f(size, -size, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-size, -size, -500);
		glTexCoord2f(0, 0.5);
		glVertex3f(-size, size, -500);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}

	// 기초 배경
	{
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(3));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(400, 400, -500);
		glTexCoord2f(1, 0);
		glVertex3f(400, -400, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-400, -400, -500);
		glTexCoord2f(0, 1);
		glVertex3f(-400, 400, -500);
		glEnd();

		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(2));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(400, 400, -500);
		glTexCoord2f(1, 0);
		glVertex3f(400, -400, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-400, -400, -500);
		glTexCoord2f(0, 1);
		glVertex3f(-400, 400, -500);
		glEnd();
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

GLvoid CGamePlayScene::Draw_Feverbackground()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);

	// 하늘
	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(9));
	glBegin(GL_QUADS);
	glTexCoord2f(1 + bg_scroll, 1);
	glVertex3f(400, 400, -500);
	glTexCoord2f(1 + bg_scroll, 0);
	glVertex3f(400, -400, -500);
	glTexCoord2f(0 + bg_scroll, 0);
	glVertex3f(-400, -400, -500);
	glTexCoord2f(0 + bg_scroll, 1);
	glVertex3f(-400, 400, -500);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	// 별궤적
	{
		int rad = 170;
		glLineWidth(2);
		glPushMatrix();
		glRotatef(bg_degree, 0, 0, 1);
		// 루비
		glColor4f(0.98, 0.46, 0.89, 0.5);
		glBegin(GL_LINES);
		for (int i = 0; i < 120; ++i) {
			glVertex3f(rad * cos(i / 180.0*pi), rad * sin(i / 180.0*pi), -499);
			glVertex3f(rad * cos((i + 1) / 180.0*pi), rad * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 요시코
		glColor4f(0.54, 0.54, 0.54, 0.5);
		glBegin(GL_LINES);
		for (int i = -40; i < 80; ++i) {
			glVertex3f((rad + 10) * cos(i / 180.0*pi), (rad + 10) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 10) * cos((i + 1) / 180.0*pi), (rad + 10) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 하나마루
		glColor4f(0.90, 0.84, 0.09, 0.5);
		glBegin(GL_LINES);
		for (int i = -80; i < 40; ++i) {
			glVertex3f((rad + 20) * cos(i / 180.0*pi), (rad + 20) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 20) * cos((i + 1) / 180.0*pi), (rad + 20) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 요우
		glColor4f(0.29, 0.73, 0.98, 0.5);
		glBegin(GL_LINES);
		for (int i = -120; i < 0; ++i) {
			glVertex3f((rad + 30) * cos(i / 180.0*pi), (rad + 30) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 30) * cos((i + 1) / 180.0*pi), (rad + 30) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 치카
		glColor4f(0.94, 0.64, 0.04, 0.5);
		glBegin(GL_LINES);
		for (int i = -160; i < -40; ++i) {
			glVertex3f((rad + 40) * cos(i / 180.0*pi), (rad + 40) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 40) * cos((i + 1) / 180.0*pi), (rad + 40) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 리코
		glColor4f(0.91, 0.66, 0.91, 0.5);
		glBegin(GL_LINES);
		for (int i = -200; i < -80; ++i) {
			glVertex3f((rad + 50) * cos(i / 180.0*pi), (rad + 50) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 50) * cos((i + 1) / 180.0*pi), (rad + 50) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 다이아
		glColor4f(0.95, 0.23, 0.3, 0.5);
		glBegin(GL_LINES);
		for (int i = -240; i < -120; ++i) {
			glVertex3f((rad + 60) * cos(i / 180.0*pi), (rad + 60) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 60) * cos((i + 1) / 180.0*pi), (rad + 60) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 카난
		glColor4f(0.07, 0.91, 0.68, 0.5);
		glBegin(GL_LINES);
		for (int i = -280; i < -160; ++i) {
			glVertex3f((rad + 70) * cos(i / 180.0*pi), (rad + 70) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 70) * cos((i + 1) / 180.0*pi), (rad + 70) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		// 마리
		glColor4f(0.68, 0.35, 0.92, 0.5);
		glBegin(GL_LINES);
		for (int i = -320; i < -200; ++i) {
			glVertex3f((rad + 80) * cos(i / 180.0*pi), (rad + 80) * sin(i / 180.0*pi), -499);
			glVertex3f((rad + 80) * cos((i + 1) / 180.0*pi), (rad + 80) * sin((i + 1) / 180.0*pi), -499);
		}
		glEnd();
		glPopMatrix();
		glLineWidth(1);
	}
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	// 기초 배경
	{
		glColor4f(1, 1, 1, 1.0);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(8));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(400, 400, -500);
		glTexCoord2f(1, 0);
		glVertex3f(400, -400, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-400, -400, -500);
		glTexCoord2f(0, 1);
		glVertex3f(-400, 400, -500);
		glEnd();

		
		glColor4f(1, 1, 1, 1.0);
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(7));
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(400, 400, -500);
		glTexCoord2f(1, 0);
		glVertex3f(400, -400, -500);
		glTexCoord2f(0, 0);
		glVertex3f(-400, -400, -500);
		glTexCoord2f(0, 1);
		glVertex3f(-400, 400, -500);
		glEnd();
		
	}
	glDisable(GL_TEXTURE_2D);

	// 하이라이트
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0, 1, 1, 0.3 - 0.3*(fever_highlight / 50));
		glBegin(GL_POLYGON);
		glVertex3f(-75, 0, -499);
		glVertex3f(-60, 0, -499);
		glVertex3f(15 - 400 * cos(fever_highlight / 180.0*pi), 600 * sin(fever_highlight / 180.0*pi), -499);
		glVertex3f(-15 - 400 * cos(fever_highlight / 180.0*pi), 600 * sin(fever_highlight / 180.0*pi), -499);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(-90, -20, -499);
		glVertex3f(-75, -20, -499);
		glVertex3f(15 - 400 * cos((fever_highlight + 15) / 180.0*pi), 600 * sin((fever_highlight + 15) / 180.0*pi), -499);
		glVertex3f(-15 - 400 * cos((fever_highlight + 15) / 180.0*pi), 600 * sin((fever_highlight + 15) / 180.0*pi), -499);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(-105, -30, -499);
		glVertex3f(-90, -30, -499);
		glVertex3f(15 - 400 * cos((fever_highlight + 30) / 180.0*pi), 600 * sin((fever_highlight + 30) / 180.0*pi), -499);
		glVertex3f(-15 - 400 * cos((fever_highlight + 30) / 180.0*pi), 600 * sin((fever_highlight + 30) / 180.0*pi), -499);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(-75 + 120, 0, -499);
		glVertex3f(-60 + 120, 0, -499);
		glVertex3f(15 + 400 * cos(fever_highlight / 180.0*pi), 600 * sin(fever_highlight / 180.0*pi), -499);
		glVertex3f(-15 + 400 * cos(fever_highlight / 180.0*pi), 600 * sin(fever_highlight / 180.0*pi), -499);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(-90 + 150, -20, -499);
		glVertex3f(-75 + 150, -20, -499);
		glVertex3f(15 + 400 * cos((fever_highlight + 15) / 180.0*pi), 600 * sin((fever_highlight + 15) / 180.0*pi), -499);
		glVertex3f(-15 + 400 * cos((fever_highlight + 15) / 180.0*pi), 600 * sin((fever_highlight + 15) / 180.0*pi), -499);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(-105 + 180, -30, -499);
		glVertex3f(-90 + 180, -30, -499);
		glVertex3f(15 + 400 * cos((fever_highlight + 30) / 180.0*pi), 600 * sin((fever_highlight + 30) / 180.0*pi), -499);
		glVertex3f(-15 + 400 * cos((fever_highlight + 30) / 180.0*pi), 600 * sin((fever_highlight + 30) / 180.0*pi), -499);
		glEnd();
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

bool CGamePlayScene::Isin_Rect(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2)
{
	if (x1 < w2 && y1 < h2 && x2 > w1 && y2 > h1)
	{
		return true;
	}

	return false;
}

GLvoid CRun_time_Framework::set_charID(int id) {
	now_character = id;
}

GLint CRun_time_Framework::get_charID() {
	return now_character;
}


