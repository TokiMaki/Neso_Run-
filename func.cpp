#include "stdafx.h"
#include "Run_time_Framework.h"
#include "GamePlayScene.h"

#define pi 3.141592

GLvoid CRun_time_Framework::Key_Update() {

	if (dir & DIR_X) {		// ��Ʈ ������ &�� �� �ϳ�!
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 1.f, 0.f, 0.f);		// ������ ����� �����ӿ� ���� �ӵ��� ����������
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
	glClearColor(r, g, b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
}

GLvoid CGamePlayScene::vari_init() {

	memset(identity, 0, sizeof(identity));
	identity[0] = identity[5] = identity[10] = identity[15] = 1;		// ��� �ʱ�ȭ

	main_road = nullptr;
	count = 0;

	Create_Road();
}

GLvoid CGamePlayScene::shape_draw() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	/*
	if (mod == 0) {
		gluLookAt(camera.x, camera.y, camera_zoom, 0, 0, -100, sin(camera_z / 180 * pi), cos(camera_z / 180 * pi), 0.0);
		glMultMatrixf(identity);
	}
	*/
	gluLookAt(player.x + sin(pi / 180 * (player.camera_rotate)) * 50, 20, player.z + cos(pi / 180 * (player.camera_rotate)) * 50, player.x, 20, player.z, 0, 1, 0);
	//gluLookAt(player.x, 200, player.z, player.x, 0, player.z, 0, 0, -1);


	glPushMatrix();
	Draw_Player();
	glPopMatrix();

	glPushMatrix();

	Draw_Road();
	glPopMatrix();


	glPopMatrix();

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