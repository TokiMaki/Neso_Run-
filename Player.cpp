#include "stdafx.h"
#include "GamePlayScene.h"
#include "Run_Time_Framework.h"

#define UP 0
#define LEFT 3
#define DOWN 2
#define RIGHT 1
#define RADIUS 5

#define ROTATE_PER_SEC 90 / (1000.f / 5.f)

#define PI 3.141592

GLvoid CGamePlayScene::Draw_Player()
{
	glPushMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(player.x, player.y, player.z);

	GLUquadricObj *sphere = gluNewQuadric();

	if (player.state == ActState::Slide) {
		glTranslatef(0, -5 * 0.3, 0);
		glScalef(1, 0.7, 1);
	}

	if (!player.death) {
		glMultMatrixf(identity);
		glEnable(GL_TEXTURE_2D);
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, GL_TRUE);

		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_ChartextureID(m_pFramework->get_charID()));
		gluSphere(sphere, RADIUS, 20, 20);
		glEndList();
		gluDeleteQuadric(sphere);
		glDisable(GL_TEXTURE_2D);
	}
	if (player.death) {
		Player_Death_Paticle();
	}

	glPopMatrix();
}

GLvoid CGamePlayScene::Player_Line_Updater(float frametime) {
	switch (player.reserve_line) {
	case -1:
		if (player.x > -30) {
			player.x -= player.speed / 2.f * frametime;
			glPushMatrix();
			{
				glRotatef(player.speed * frametime, 0.f, 0.f, 1.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		if (player.x <= -30) {
			player.x += player.speed / 2.f * frametime;
			glPushMatrix();
			{
				glRotatef(-player.speed * frametime, 0.f, 0.f, 1.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		break;
	case 0:
		if (player.x > 0) {
			player.x -= player.speed / 2.f * frametime;
			glPushMatrix();
			{
				glRotatef(player.speed * frametime, 0.f, 0.f, 1.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		if (player.x < 0) {
			player.x += player.speed / 2.f * frametime;
			glPushMatrix();
			{
				glRotatef(-player.speed * frametime, 0.f, 0.f, 1.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		break;
	case 1:
		if (player.x < 30) {
			player.x += player.speed / 2.f * frametime;
			glPushMatrix();
			{
				glRotatef(-player.speed * frametime, 0.f, 0.f, 1.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		if (player.x >= 30) {
			player.x -= player.speed / 2.f * frametime;
			glPushMatrix();
			{
				glRotatef(player.speed * frametime, 0.f, 0.f, 1.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
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
	if (!player.death) {

		if (player.autorun_state != AutorunState::Autorun) {
			Collision_Obstacle(frametime);
		}

		if (player.autorun_state == AutorunState::Autorun) {
			Autorun(frametime);
		}

		Collision_Coin();
		if (!player.input_rotate) {
			player.z -= player.speed * frametime;
			if (main_road->road_length + player.z < 0) {
				printf("%f\n", main_road->road_length + player.z);
			}

			if (player.state == ActState::Idle) {
				player.roll -= player.speed * 2 * frametime;
				glPushMatrix();
				{
					glRotatef(-player.speed * 2 * frametime, 1.f, 0.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
					glMultMatrixf(identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, identity);
				}
				glPopMatrix();
			}

			Player_Line_Updater(frametime);
			Player_Jump(frametime);
			Player_Silde(frametime);
		}
		else if (main_road->road_length + player.z > 30) {
			player.z -= player.speed * frametime;

			if (player.state == ActState::Idle) {
				player.roll -= player.speed * 2 * frametime;
				glPushMatrix();
				{
					glRotatef(-player.speed * 2 * frametime, 1.f, 0.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
					glMultMatrixf(identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, identity);
				}
				glPopMatrix();
			}

			Player_Line_Updater(frametime);
			Player_Jump(frametime);
			Player_Silde(frametime);
		}

		else {
			if (player.dir == 0) {
				if (count > -90) {
					count -= ROTATE_PER_SEC * frametime;
					player.camera_rotate -= ROTATE_PER_SEC * frametime;
					glPushMatrix();
					{
						glRotatef(-ROTATE_PER_SEC * frametime, 0.f, 1.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
						glMultMatrixf(identity);
						glGetFloatv(GL_MODELVIEW_MATRIX, identity);
					}
					glPopMatrix();
				}
				else if (count <= -90) {
					player.camera_rotate = 0;
					count = 0;

					//memset(identity, 0, sizeof(identity));
					//identity[0] = identity[5] = identity[10] = identity[15] = 1;		// 행렬 초기화
					glPushMatrix();
					{
						glRotatef(90, 0.f, 1.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
						glMultMatrixf(identity);
						glGetFloatv(GL_MODELVIEW_MATRIX, identity);
					}
					glPopMatrix();

					player.input_rotate = false;

					player.x = (main_road->road_length + player.z);
					printf("%f\n", main_road->road_length + player.z);
					player.reserve_line = 1;
					if (main_road->road_length + player.z < 20) {
						player.reserve_line = 0;
					}
					if (main_road->road_length + player.z < -20) {
						player.reserve_line = -1;
					}

					player.z = -(player.line * 30);
					Create_Road();
				}
			}

			if (player.dir == 1) {
				if (count < 90) {
					count += ROTATE_PER_SEC * frametime;
					player.camera_rotate += ROTATE_PER_SEC * frametime;
					glPushMatrix();
					{
						glRotatef(ROTATE_PER_SEC * frametime, 0.f, 1.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
						glMultMatrixf(identity);
						glGetFloatv(GL_MODELVIEW_MATRIX, identity);
					}
					glPopMatrix();
				}
				else if (count >= 90) {
					player.camera_rotate = 0;
					count = 0;


					//memset(identity, 0, sizeof(identity));
					//identity[0] = identity[5] = identity[10] = identity[15] = 1;		// 행렬 초기화

					glPushMatrix();
					{
						glRotatef(-90, 0.f, 1.f, 0.f);		// 저렇게 만들면 프레임에 따라 속도가 변하지않음
						glMultMatrixf(identity);
						glGetFloatv(GL_MODELVIEW_MATRIX, identity);
					}
					glPopMatrix();

					player.input_rotate = false;

					player.x = -(main_road->road_length + player.z);
					printf("%f\n", main_road->road_length + player.z);
					player.reserve_line = -1;

					if (main_road->road_length + player.z < 20) {
						player.reserve_line = 0;
					}
					if (main_road->road_length + player.z < -20) {
						player.reserve_line = 1;
					}
					player.z = (player.line * 30);
					Create_Road();
				}
			}
		}
	}
	else if (player.death) {
		Player_Death_Paticle_Update(frametime);
	}
}

GLvoid CGamePlayScene::Player_KeyDown_Updater(int key) {
	switch (key) {
	case GLUT_KEY_LEFT:
		//printf("left\n");
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
		//printf("right\n");
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
		if ((player.reserve_state == ActState::Slide || player.reserve_state == ActState::Idle) && player.y <= 0) {
			//printf("%f", player.jump_gravity);
			player.jump_gravity = ((player.speed) / 4.f * 3.f);
			player.reserve_state = ActState::Jump;
		}
		break;

	case GLUT_KEY_DOWN:
		if ((player.reserve_state == ActState::Slide || player.reserve_state == ActState::Idle) && player.y <= 0) {
			//printf("Slide");
			player.reserve_state = ActState::Slide;
		}
		break;
	}
}

GLvoid CGamePlayScene::Player_Jump(float frametime) {
	float gravity = ((player.speed) / 4.f * 3.f);

	if (player.reserve_state == ActState::Jump) {


		if (player.y < 100) {
			player.y += player.jump_gravity * frametime;
			player.jump_gravity -= gravity / (50.f * (1 / gravity)) * frametime;
			if (player.jump_gravity < gravity / 2.f) {
				player.state = ActState::Jump;
			}
		}

		if (player.y >= 100 || player.jump_gravity < 0) {
			player.reserve_state = ActState::Idle;
		}

	}
	if (player.reserve_state == ActState::Idle) {
		if (player.y > 0) {
			player.y -= player.jump_gravity * frametime;
			player.jump_gravity += gravity / (50.f * (1 / gravity)) * frametime;
			if (player.jump_gravity > gravity / 2.f) {
				player.state = ActState::Idle;
			}
			if (player.y <= 0) {
				player.y = 0;
				player.jump_gravity = 0;
			}
		}
	}

}

GLvoid CGamePlayScene::Player_Silde(float frametime) {

	if (player.reserve_state == ActState::Slide) {
		if (player.timer < 500.f) {
			player.state = Slide;
			player.timer += frametime;
		}
		if (player.timer >= 500.f) {
			player.reserve_state = ActState::Idle;
			player.state = ActState::Idle;
			player.timer = 0;
		}
	}

	if (player.reserve_state == ActState::Idle) {
		player.timer = 0;
	}
}

GLvoid CGamePlayScene::Player_Death_Paticle() {
	glPushMatrix(); {
		glScalef(death_timer, death_timer, death_timer);
		glColor3f(0, 1, 0);
		for (float i = 0; i < 20; ++i) {
			for (float j = 0; j < 5; ++j) {
				glPushMatrix(); {
					glRotatef((180 / 5.f) * j, 0, 0, 1);
					glTranslatef(sin(PI / 180 * (360 / 20.f) * i) * 5, 0, cos(PI / 180 * (360 / 20.f) * i) * 5);
					glutSolidCube(2.5 / death_timer);
					glPopMatrix();
				}
			}
		}
	}
	glPopMatrix();
}

GLvoid CGamePlayScene::Player_Death_Paticle_Update(float frametime) {
	if (death_timer <= 50) {
		death_timer += 1 / 100.f * frametime;
	}
	else if (death_timer > 50) {
		m_pFramework->set_bgm(4);
		m_pFramework->MessagePass(Message::GameOver);
	}
}