#include "stdafx.h"
#include "GamePlayScene.h"

#define MIN_ROAD 1000
#define MAX_ROAD 1200
#define LOAD_WIDTH 60

GLvoid CGamePlayScene::Create_Road() {
	Road_Tree* temp;

	std::uniform_int_distribution<> uid(MIN_ROAD, MAX_ROAD);

	int road_random_temp = 0;

	temp = new(Road_Tree);
		
	if (main_road) {
		if (player.dir == 1 && main_road->Lroad != nullptr) {
			temp->road_length = main_road->Lroad->road_length;
			for (Obstacle &i : main_road->Lroad->GetObstacleList()) {
				temp->ObstaclePushBack(i.kind, i.y, i.z);
			}
		}
			
		if (player.dir == 0 && main_road->Rroad != nullptr) {
			temp->road_length = main_road->Rroad->road_length;
			for (Obstacle &i : main_road->Rroad->GetObstacleList()) {
				temp->ObstaclePushBack(i.kind, i.y, i.z);
			}
		}
	}

	else {
		temp->road_length = uid(dre);
	}
		road_random_temp = rand() % 3;

		if (road_random_temp == 0) {

			temp->Lroad = new(Road_Tree);
			temp->Lroad->road_length = uid(dre);
			temp->Lroad->ObstacleClear();

			temp->Rroad = nullptr;

		}

		if (road_random_temp == 1) {

			temp->Lroad = nullptr;

			temp->Rroad = new(Road_Tree);
			temp->Rroad->road_length = uid(dre);
			temp->Rroad->ObstacleClear();


		}

		if (road_random_temp == 2) {

			temp->Lroad = new(Road_Tree);
			temp->Lroad->road_length = uid(dre);
			temp->Lroad->ObstacleClear();

			temp->Rroad = new(Road_Tree);
			temp->Rroad->road_length = uid(dre);
			temp->Rroad->ObstacleClear();

		}
		if (main_road) {

			if (main_road->Lroad) {
				delete(main_road->Lroad);
			}

			if (main_road->Rroad) {
				delete(main_road->Rroad);
			}

			delete(main_road);
		}

		main_road = temp;
		Create_Obstacle();
}

GLvoid CGamePlayScene::Create_Obstacle() {
	std::uniform_int_distribution<> uid(150, 250);
	std::uniform_int_distribution<> uid2(0, 3);

	float temp = 0;

	if ((main_road->GetObstacleList().size()) <= 0) {
		printf("메인비엇다");
	}
	if (main_road && main_road->GetObstacleList().size() <= 0) {
		main_road->GetObstacleList().clear();
		while(temp < main_road->road_length - 400){
			temp += uid(dre);
			main_road->ObstaclePushBack(uid2(dre), 0, temp);
		}
	}
	if (main_road->Lroad && main_road->Lroad->GetObstacleList().size() <= 0) {
		temp = 0;
		while (temp < main_road->road_length - 400) {
			temp += uid(dre);
			main_road->Lroad->ObstaclePushBack(uid2(dre), 0, temp);
		}
	}
	if (main_road->Rroad && main_road->Rroad->GetObstacleList().size() <= 0) {
		temp = 0;
		while (temp < main_road->road_length - 400) {
			temp += uid(dre);
			main_road->Rroad->ObstaclePushBack(uid2(dre), 0, temp);
		}
	}
}

GLvoid CGamePlayScene::Draw_Obstacle() {

	float temp = 0;
	if (main_road) {
		for (Obstacle &i : main_road->GetObstacleList()) {
				glPushMatrix(); {
					glColor3f(1, 0, 0);
					glTranslatef(0, 50, -i.z);
					ObstacleFrame(i.kind, 60, 2.5);
				}
				glPopMatrix();
		}
		if (main_road->Lroad) {
			for (Obstacle &i : main_road->Lroad->GetObstacleList()) {
				glPushMatrix(); {
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -main_road->road_length);
					glRotatef(90, 0, 1, 0);
					glTranslatef(0, 50, -i.z);
					ObstacleFrame(i.kind, 60, 2.5);
				}
				glPopMatrix();
			}
		}
		if (main_road->Rroad) {
			for (Obstacle &i : main_road->Rroad->GetObstacleList()) {
				glPushMatrix(); {
					glColor3f(1, 0, 0);
					glTranslatef(0, 0, -main_road->road_length);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0, 50, -i.z);
					ObstacleFrame(i.kind, 60, 2.5);
				}
				glPopMatrix();
			}
		}
	}
}

GLvoid CGamePlayScene::Draw_Road() {
	glPushMatrix();
	glTranslatef(0, -55, 0);
	Draw_Obstacle();
	glColor3f(0, 1, 0);

	RoadFrame(LOAD_WIDTH, main_road->road_length);
	RoadFrame(LOAD_WIDTH, -main_road->road_length);

	if (main_road->Lroad != nullptr) {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(90, 0, 1, 0);
		RoadFrame(LOAD_WIDTH, main_road->Lroad->road_length);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(90, 0, 1, 0);
		RoadFrame(LOAD_WIDTH, LOAD_WIDTH);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}

	if (main_road->Rroad != nullptr) {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(-90, 0, 1, 0);
		RoadFrame(LOAD_WIDTH, main_road->Rroad->road_length);
		//glutSolidCube(main_road->Rroad->road_length);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(-90, 0, 1, 0);
		RoadFrame(LOAD_WIDTH, LOAD_WIDTH);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}

	glPopMatrix();
}


GLvoid CGamePlayScene::ObstacleFrame(int kind, float width, float length) {
	switch (kind) {
	case 0:
		glBegin(GL_QUADS);
		glVertex3f(-width, 10, -length);
		glVertex3f(-width, 0, -length);
		glVertex3f(width / 4.f, 0, -length);
		glVertex3f(width / 4.f, 10, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width / 4.f, 10, -length);
		glVertex3f(width / 4.f, 0, -length);
		glVertex3f(width / 4.f, 0, length);
		glVertex3f(width / 4.f, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width / 4.f, 10, length);
		glVertex3f(width / 4.f, 0, length);
		glVertex3f(-width, 0, length);
		glVertex3f(-width, 10, length);
		glEnd();


		glBegin(GL_QUADS);
		glVertex3f(-width, 10, length);
		glVertex3f(-width, 0, length);
		glVertex3f(-width, 0, -length);
		glVertex3f(-width, 10, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width, 5, length);
		glVertex3f(-width, 5, -length);
		glVertex3f(width / 4.f, 5, -length);
		glVertex3f(width / 4.f, 5, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width, 0, -length);
		glVertex3f(-width, 0, length);
		glVertex3f(width / 4.f, 0, length);
		glVertex3f(width / 4.f, 0, -length);
		glEnd();
		break;

	case 1:
		glBegin(GL_QUADS);
		glVertex3f(width, 10, -length);
		glVertex3f(width, 0, -length);
		glVertex3f(-width / 4.f, 0, -length);
		glVertex3f(-width / 4.f, 10, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width / 4.f, 10, -length);
		glVertex3f(-width / 4.f, 0, -length);
		glVertex3f(-width / 4.f, 0, length);
		glVertex3f(-width / 4.f, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width / 4.f, 10, length);
		glVertex3f(-width / 4.f, 0, length);
		glVertex3f(width, 0, length);
		glVertex3f(width, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 10, length);
		glVertex3f(width, 0, length);
		glVertex3f(width, 0, -length);
		glVertex3f(width, 10, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 10, length);
		glVertex3f(width, 10, -length);
		glVertex3f(-width / 4.f, 10, -length);
		glVertex3f(-width / 4.f, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 0, -length);
		glVertex3f(width, 0, length);
		glVertex3f(-width / 4.f, 0, length);
		glVertex3f(-width / 4.f, 0, -length);
		glEnd();
		break;

	case 2:
		glBegin(GL_QUADS);
		glVertex3f(width, 10, -length);
		glVertex3f(width, 0, -length);
		glVertex3f(-width, 0, -length);
		glVertex3f(-width, 10, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width, 10, -length);
		glVertex3f(-width, 0, -length);
		glVertex3f(-width, 0, length);
		glVertex3f(-width, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width, 10, length);
		glVertex3f(-width, 0, length);
		glVertex3f(width, 0, length);
		glVertex3f(width, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 10, length);
		glVertex3f(width, 0, length);
		glVertex3f(width, 0, -length);
		glVertex3f(width, 10, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 10, length);
		glVertex3f(width, 10, -length);
		glVertex3f(-width, 10, -length);
		glVertex3f(-width, 10, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 0, -length);
		glVertex3f(width, 0, length);
		glVertex3f(-width, 0, length);
		glVertex3f(-width, 0, -length);
		glEnd();
		break;

	case 3:
		glBegin(GL_QUADS);
		glVertex3f(width, 50, -length);
		glVertex3f(width, 6, -length);
		glVertex3f(-width, 6, -length);
		glVertex3f(-width, 50, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width, 50, -length);
		glVertex3f(-width, 8, -length);
		glVertex3f(-width, 8, length);
		glVertex3f(-width, 50, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(-width, 50, length);
		glVertex3f(-width, 8, length);
		glVertex3f(width, 8, length);
		glVertex3f(width, 50, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 50, length);
		glVertex3f(width, 8, length);
		glVertex3f(width, 8, -length);
		glVertex3f(width, 50, -length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 50, length);
		glVertex3f(width, 8, -length);
		glVertex3f(-width, 8, -length);
		glVertex3f(-width, 50, length);
		glEnd();

		glBegin(GL_QUADS);
		glVertex3f(width, 8, -length);
		glVertex3f(width, 8, length);
		glVertex3f(-width, 8, length);
		glVertex3f(-width, 8, -length);
		glEnd();
		break;
	}
}

GLvoid CGamePlayScene::RoadFrame(float width, float length) {

	glBegin(GL_QUADS);
	glVertex3f(-width, 50, 0);
	glVertex3f(-width, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 50, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(width, 50, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 0, -length);
	glVertex3f(width, 50, -length);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(width, 50, -length);
	glVertex3f(width, 0, -length);
	glVertex3f(-width, 0, -length);
	glVertex3f(-width, 50, -length);
	glEnd();


	glBegin(GL_QUADS);
	glVertex3f(-width, 50, -length);
	glVertex3f(-width, 0, -length);
	glVertex3f(-width, 0, 0);
	glVertex3f(-width, 50, 0);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-width, 50, -length);
	glVertex3f(-width, 50, 0);
	glVertex3f(width, 50, 0);
	glVertex3f(width, 50, -length);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-width, 0, 0);
	glVertex3f(-width, 0, -length);
	glVertex3f(width, 0, -length);
	glVertex3f(width, 0, 0);
	glEnd();
}