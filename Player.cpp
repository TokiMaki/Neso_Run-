#include "stdafx.h"
#include "GamePlayScene.h"
#include "Run_Time_Framework.h"

#define UP 0
#define LEFT 3
#define DOWN 2
#define RIGHT 1
#define RADIUS 5

#define ROTATE_PER_SEC 90 / (1000.f / 5.f)

GLvoid CGamePlayScene::Draw_Player()
{
	glPushMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(player.x , player.y, player.z);

	GLUquadricObj *sphere = gluNewQuadric();

	if (player.state == State::Slide) {
		glTranslatef(0, -5 * 0.3, 0);
		glScalef(1, 0.7, 1);
	}

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

GLvoid CGamePlayScene::Player_Line_Updater(float frametime) {
	switch (player.reserve_line) {
	case -1:
		if (player.x > -30) {
			player.x -= player.speed * frametime;
		}
		if (player.x <= -30) {
			player.x = -30;
		}
		break;
	case 0:
		if (player.x > 0) {
			player.x -= player.speed * frametime;
		}
		if (player.x < 0) {
			player.x += player.speed * frametime;
		}
		break;
	case 1:
		if (player.x < 30) {
			player.x += player.speed * frametime;
			if (player.x >= 30) {
				player.x = 30;
			}
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
		player.z -= player.speed * frametime;
		Player_Line_Updater(frametime);
		Player_Jump(frametime);
		Player_Silde(frametime);
	}
	else if (main_road->road_length + player.z > (player.line * 30) && player.dir == 0) {
		player.z -= player.speed * frametime;
		Player_Line_Updater(frametime);
		Player_Jump(frametime);
		Player_Silde(frametime);
	}
	else if (main_road->road_length + player.z > -(player.line * 30) && player.dir == 1) {
		player.z -= player.speed * frametime;
		Player_Line_Updater(frametime);
		Player_Jump(frametime);
		Player_Silde(frametime);
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
				player.z = -(player.line * 30);
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
				player.z = (player.line * 30);
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
		if ((player.reserve_state == State::Slide || player.reserve_state == State::Idle) && player.y <= 0) {
			printf("%f", player.jump_gravity);
			player.reserve_state = State::Jump;
		}
		break;

	case GLUT_KEY_DOWN:
		if ((player.reserve_state == State::Slide || player.reserve_state == State::Idle) && player.y <= 0) {
			printf("Slide");
			player.reserve_state = State::Slide;
		}
		break;
	}
}

GLvoid CGamePlayScene::Player_Jump(float frametime) {
	if (player.reserve_state == State::Jump) {

		if (player.y < 30) {
			player.y += player.jump_gravity * frametime;
			player.jump_gravity -= ((player.speed) / 300.f) * frametime;
			if (player.jump_gravity < (player.speed / 4.f * 3.f) / 2.f) {
				player.state = State::Jump;
			}
		}

		if (player.y >= 30 || player.jump_gravity < 0) {
			player.reserve_state = State::Idle;
		}

	}

	if (player.reserve_state == State::Idle) {
		if (player.y > 0) {
			player.y -= player.jump_gravity * frametime;
			player.jump_gravity += ((player.speed) / 300.f) * frametime;
			if (player.jump_gravity > (player.speed / 4.f * 3.f) / 2.f) {
				player.state = State::Jump;
			}
			if (player.y <= 0) {
				player.y = 0;
				player.jump_gravity = player.speed / 4.f * 3.f;
			}
		}
	}

}

GLvoid CGamePlayScene::Player_Silde(float frametime) {

	if (player.reserve_state == State::Slide) {
		if (player.timer < 500.f) {
			player.state = Slide;
			player.timer += frametime;
		}
		if (player.timer >= 500.f) {
			player.reserve_state = State::Idle;
			player.state = State::Idle;
			player.timer = 0;
		}
	}

	if (player.reserve_state == State::Idle) {
		player.timer = 0;
	}
}