#include "stdafx.h"
#include "GamePlayScene.h"
#include "Run_Time_Framework.h"

#define UP 0
#define LEFT 3
#define DOWN 2
#define RIGHT 1
#define RADIUS 5

#define ROTATE_PER_SEC 90 / (1000.f / 5.f)

GLvoid CGamePlayScene::Draw_Ball()
{
	glPushMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(player.x , player.y, player.z);

	GLUquadricObj *sphere = gluNewQuadric();

	glRotatef(player.camera_rotate + 90, 0, 1, 0);
	glRotatef(player.z, 0, 0, 1);

	glEnable(GL_TEXTURE_2D);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);

	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_ChartextureID(m_pFramework->get_charID()));
	gluSphere(sphere, RADIUS, 20, 20);
	glEndList();
	gluDeleteQuadric(sphere);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

GLvoid CGamePlayScene::Player_Line_Updater() {
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

GLvoid CGamePlayScene::Player_Update(float frametime) {

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
				count -= ROTATE_PER_SEC * frametime;
				player.camera_rotate -= ROTATE_PER_SEC * frametime;
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
				count += ROTATE_PER_SEC * frametime;
				player.camera_rotate += ROTATE_PER_SEC * frametime;
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

GLvoid CGamePlayScene::Player_KeyDown_Updater(int key) {
	switch (key) {
	case GLUT_KEY_LEFT:
		printf("left\n");
		if (NextRoadcheck(1)) {
			printf("left in\n");
			player.input_rotate = true;
			player.dir = 1;
		}
		else if (!player.input_rotate) {
			if (player.reserve_line > -1)
				player.reserve_line -= 1;
		}
		break;

	case GLUT_KEY_RIGHT:
		printf("right\n");
		if (NextRoadcheck(0)) {
			printf("right in\n");
			player.input_rotate = true;
			player.dir = 0;
		}
		else if (!player.input_rotate) {
			if (player.reserve_line < 1)
				player.reserve_line += 1;
		}
		break;

	case GLUT_KEY_UP:
		if (player.reserve_state == State::Idle && player.y <= 0) {
			player.reserve_state = State::Jump;
		}
		break;

	case GLUT_KEY_DOWN:
		break;
	}
}

GLvoid CGamePlayScene::Player_Jump(float frametime) {
	if (player.reserve_state = State::Jump) {

		if (player.y < 30) {
			player.y += player.jump_gravite * frametime;
			if (player.y > 15) {
				player.state = State::Jump;
			}
		}

		if (player.y >= 30) {
			player.reserve_state = State::Idle;
		}

	}

	if (player.reserve_state = State::Idle) {
		if (player.y > 0) {
			player.y -= player.jump_gravite * frametime;
			if (player.y < 15) {
				player.state = State::Idle;
			}
			if (player.y < 0) {
				player.y = 0;
			}
		}

	}
}