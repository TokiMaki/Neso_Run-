#include "stdafx.h"
#include "Run_time_Framework.h"

#define UP 0
#define LEFT 3
#define DOWN 2
#define RIGHT 1
#define RADIUS 5

GLvoid CRun_time_Framework::Draw_Ball()
{
	glPushMatrix();

	glTranslatef(player.x , player.y, player.z);

	GLUquadricObj *sphere = gluNewQuadric();

	//glRotatef(moon_degree, 0, 1, 0);

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);

	// glBindTexture(GL_TEXTURE_2D, texture[1]);
	gluSphere(sphere, RADIUS, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);

	glPopMatrix();
}

GLvoid CRun_time_Framework::Player_Line_Updater() {
	switch (player.reserve_line) {
	case -1:
		if (player.x > -30) {
			player.x -= 5;
		}
		break;
	case 0:
		if (player.x > 0) {
			player.x -= 5;
		}
		if (player.x < 0) {
			player.x += 5;
		}
		break;
	case 1:
		if (player.x < 30) {
			player.x += 5;
		}
		break;
	}
	if (player.x < -15) {
		player.line = -1;
	}
	else if (player.x >= -15 && player.x <= 15) {
		player.line = 0;
	}
	else if (player.x > 15) {
		player.line = 1;
	}
}

GLvoid CRun_time_Framework::Player_Update() {
	if (!player.input_rotate) {
		player.z -= 5;
		Player_Line_Updater();
	}
	else if (main_road->road_length + player.z > (player.line * 30) && player.dir == 0) {
		player.z -= 5;
		Player_Line_Updater();
	}
	else if (main_road->road_length + player.z > -(player.line * 30) && player.dir == 1) {
		player.z -= 5;
		Player_Line_Updater();
	}

	else {
		if (player.dir == 0) {
			if (count > -90) {
				count -= 90 / 200.f * FRAMETIME;
				player.camera_rotate -= 90 / 200.f * FRAMETIME;
			}
			else if (count <= -90) {
				Create_Road();
				player.camera_rotate = 0;
				count = 0;
				player.input_rotate = false;
				player.y = 0;
				player.z = 0;
			}
		}

		if (player.dir == 1) {
			if (count < 90) {
				count += 90 / 200.f * FRAMETIME;
				player.camera_rotate += 90 / 200.f * FRAMETIME;
			}
			else if (count >= 90) {
				Create_Road();
				player.camera_rotate = 0;
				count = 0;
				player.input_rotate = false;
				player.y = 0;
				player.z = 0;
			}
		}
	}
}