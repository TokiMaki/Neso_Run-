#include "stdafx.h"
#include "Run_time_Framework.h"

#define pi 3.141592


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::vari_init() {

	memset(identity, 0, sizeof(identity));
	identity[0] = identity[5] = identity[10] = identity[15] = 1;		// 행렬 초기화

	camera_zoom = 100;

	camera.x = 0;
	camera.y = 0;

	camera_view = 0;
	camera_move = 0;

	main_road = NULL;

	mod = 0;		// 카메라 모드를 바꾸는 것
	player.dir = 0;
	Create_Road();


}

GLvoid CRun_time_Framework::shape_draw() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if (mod == 0) {
		gluLookAt(camera.x, camera.y, camera_zoom, 0, 0, -100, sin(camera_z / 180 * pi), cos(camera_z / 180 * pi), 0.0);
		glMultMatrixf(identity);
	}
	if (mod == 1)
		gluLookAt(player.x + sin(pi / 180 * (player.camera_rotate)) * 100, player.y + 50, player.z + cos(pi / 180 * (player.camera_rotate)) * 100, 0, player.y, player.z, 0, 1, 0);


	glPushMatrix();
	glColor3f(1, 0, 0);
	Draw_Ball();
	glPopMatrix();

	glPushMatrix();

	glColor3f(0.5, 0.5, 0.5);
	Draw_Road();
	glPopMatrix();


	glPopMatrix();

}

GLvoid CRun_time_Framework::Draw_Ball()
{
	glPushMatrix();

	glTranslatef(player.x, player.y, player.z);

	GLUquadricObj *sphere = gluNewQuadric();

	//glRotatef(moon_degree, 0, 1, 0);

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);

	// glBindTexture(GL_TEXTURE_2D, texture[1]);
	gluSphere(sphere, 25, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);

	glPopMatrix();
}


bool CRun_time_Framework::Isin_Rect(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2)
{
	if (x1 < w2 && y1 < h2 && x2 > w1 && y2 > h1)
	{
		return true;
	}

	return false;
}

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