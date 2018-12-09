#include "stdafx.h"
#include "GamePlayScene.h"

#define MIN_ROAD 1000
#define MAX_ROAD 1200
#define LOAD_WIDTH 60

GLvoid CGamePlayScene::Create_Road() {
	Road_Tree* temp;

	std::uniform_int_distribution<> uid(MIN_ROAD, MAX_ROAD);
	std::uniform_int_distribution<> random_road_kind(0, 2);

	int road_random_temp = 0;

	temp = new(Road_Tree);
		
	if (main_road) {
		if (player.dir == 1 && main_road->Lroad != nullptr) {
			temp = main_road->Lroad;
			temp->Lroad = nullptr;
			temp->Rroad = nullptr;
		}
			
		if (player.dir == 0 && main_road->Rroad != nullptr) {
			temp = main_road->Rroad;
			temp->Lroad = nullptr;
			temp->Rroad = nullptr;
		}
	}

	else {
		temp->road_length = uid(dre);
	}
		road_random_temp = random_road_kind(dre);

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

			if (temp != main_road->Lroad) {
				delete(main_road->Lroad);
			}

			if (temp != main_road->Rroad) {
				delete(main_road->Rroad);
			}

			delete(main_road);
		}

		main_road = temp;

		Create_Obstacle();
		Create_Coin();
}

GLvoid CGamePlayScene::Draw_Road() {
	glPushMatrix();
	glTranslatef(0, -55, 0);
	//glColor3f(0, 1, 0);

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
		RoadFrame(LOAD_WIDTH, LOAD_WIDTH + LOAD_WIDTH);
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
		RoadFrame(LOAD_WIDTH, LOAD_WIDTH + LOAD_WIDTH);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}

	Draw_Coin();
	Draw_Obstacle();
	glPopMatrix();
}

GLvoid CGamePlayScene::Create_Obstacle() {
	std::uniform_int_distribution<> uid(4, 6);
	std::uniform_int_distribution<> uid2(0, 8);

	float temp = 0;

	if (main_road && main_road->GetObstacleList().empty()) {
		while (true) {
			temp += uid(dre) * 50;
			if (temp >= main_road->road_length - 100)
				break;
			main_road->ObstaclePushBack(uid2(dre) / 2, 0, temp);
			//main_road->ObstaclePushBack(0, 0, temp);
		}
	}
	if (main_road->Lroad && main_road->Lroad->GetObstacleList().empty()) {
		temp = 0;
		while (true) {
			temp += uid(dre) * 50;
			if (temp >= main_road->Lroad->road_length - 100)
				break;
			main_road->Lroad->ObstaclePushBack(uid2(dre) / 2, 0, temp);
			//main_road->Lroad->ObstaclePushBack(0, 0, temp);
		}
	}
	if (main_road->Rroad && main_road->Rroad->GetObstacleList().empty()) {
		temp = 0;
		while (true) {
			temp += uid(dre) * 50;
			if (temp >= main_road->Rroad->road_length - 100)
				break;
			main_road->Rroad->ObstaclePushBack(uid2(dre) / 2, 0, temp);
			//main_road->Rroad->ObstaclePushBack(0, 0, temp);
		}
	}
}

GLvoid CGamePlayScene::Draw_Obstacle() {
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float temp = 0;
	if (main_road) {
		for (Obstacle &i : main_road->GetObstacleList()) {
			glPushMatrix(); {
				glTranslatef(0, 50, -i.z);
				ObstacleFrame(i.kind, LOAD_WIDTH, 2.5);
			}
			glPopMatrix();
		}
		if (main_road->Lroad) {
			for (Obstacle &i : main_road->Lroad->GetObstacleList()) {
				glPushMatrix(); {
					glTranslatef(0, 0, -main_road->road_length);
					glRotatef(90, 0, 1, 0);
					glTranslatef(0, 50, -i.z);
					ObstacleFrame(i.kind, LOAD_WIDTH, 2.5);
				}
				glPopMatrix();
			}
		}
		if (main_road->Rroad) {
			for (Obstacle &i : main_road->Rroad->GetObstacleList()) {
				glPushMatrix(); {
					glTranslatef(0, 0, -main_road->road_length);
					glRotatef(-90, 0, 1, 0);
					glTranslatef(0, 50, -i.z);
					ObstacleFrame(i.kind, LOAD_WIDTH, 2.5);
				}
				glPopMatrix();
			}
		}
	}
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glColor3f(1, 1, 1);
}

GLvoid CGamePlayScene::Create_Coin() {
	std::uniform_int_distribution<> uid(-1, 1);

	float temp = 50;
	float random_temp;
	int present_line = 0;
	Coin t;

	/*
	if (main_road->GetCoinList().empty()) {
		if (main_road->Lroad) {
			if (main_road->Lroad->GetCoinList().empty()) 
			printf("왼\n");
		}
		if (main_road->Rroad) {
			if (main_road->Rroad->GetCoinList().empty())
			printf("오른\n");
		}
		printf("메인 코인리스트가 없네?\n");
	}
	*/

	if (main_road && main_road->GetCoinList().empty()) {
		while (true) {
			temp += 50;
			if (temp >= main_road->road_length - 100)
				break;
			Create_Coin_Algorism(main_road, temp, &present_line);
		}
	}
	if (main_road->Lroad && main_road->Lroad->GetCoinList().empty()) {
		temp = 50;
		while (true) {
			temp += 50;
			if (temp >= main_road->Lroad->road_length - 100)
				break;
			Create_Coin_Algorism(main_road->Lroad, temp, &present_line);
		}
	}
	if (main_road->Rroad && main_road->Rroad->GetCoinList().empty()) {
		temp = 50;
		while (true) {
			temp += 50;
			if (temp >= main_road->Rroad->road_length - 100)
				break;
			Create_Coin_Algorism(main_road->Rroad, temp, &present_line);
		}
	}
}

GLvoid CGamePlayScene::Create_Coin_Algorism(Road_Tree* t, int z, int* line) {
	std::uniform_int_distribution<> uid(-1, 1);
	std::uniform_int_distribution<> item(0, 100);
	int random_temp = item(dre);
	int coin_kind;

	// 나올 확률 부분
	switch (random_temp) {
	case 0:
	case 1:
		coin_kind = 1;
		break;
	case 2:
	case 3:
		coin_kind = 2;
		break;
	default:
		coin_kind = 0;
		break;
	}

	for (Obstacle &i : t->GetObstacleList()) {
		if (z + 50 == int(i.z)) {
			switch (i.kind) {
			case 0:
				if (*line < 1)
					*line += 1;
				//t->CoinPushBack(0, *line * 30, 0, z);
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;
			case 1:
				if (*line > -1)
					*line -= 1;
				//t->CoinPushBack(0, *line * 30, 0, z);
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;
			case 2:
				//t->CoinPushBack(0, *line * 30, 0, z);
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;
			case 3:
				//t->CoinPushBack(0, *line * 30, 0, z);
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;

			}
		}
		else if (z == int(i.z)) {
			switch (i.kind) {
			case 0:
				*line = 1;
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;
			case 1:
				*line = -1;
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;
			case 2:
				t->CoinPushBack(coin_kind, *line * 30, 30, z);
				return;
				break;
			case 3:
				t->CoinPushBack(coin_kind, *line * 30, 0, z);
				return;
				break;
			}
		}
	}
	if (t->GetCoinList().empty()) {
		//t->CoinPushBack(0, *line * 30, 0, z);
		t->CoinPushBack(coin_kind, *line * 30, 0, z);
		random_temp = uid(dre);
		if (*line + random_temp >= -1 && *line + random_temp <= 1) {
			*line += random_temp;
		}
		return;
	}
	else if (!t->GetCoinList().empty() && t->GetCoinList().back().z != z) {
		//t->CoinPushBack(0, *line * 30, 0, z);
		t->CoinPushBack(coin_kind, *line * 30, 0, z);
		random_temp = uid(dre);
		if (*line + random_temp >= -1 && *line + random_temp <= 1) {
			*line += random_temp;
		}
		return;
	}
}

GLvoid CGamePlayScene::Draw_Coin() {
	for (Coin &i : main_road->GetCoinList()) {
		glPushMatrix(); {
			set_Coin_material(i.kind);
			switch (i.kind) {
			case 0:
				glColor4f(0, 0, 1, 1);
				break;
			case 1:
				glColor4f(0, 1, 0, 1);
				break;
			case 2:
				glColor4f(1, 0, 0, 1);
				break;
			}
			glTranslatef(i.x, i.y + 55, -i.z);
			glutSolidCube(5);
		}
		glPopMatrix();
	}
	if (main_road->Lroad) {
		for (Coin &i : main_road->Lroad->GetCoinList()) {
			glPushMatrix(); {
				set_Coin_material(i.kind);
				switch (i.kind) {
				case 0:
					glColor4f(0, 0, 1, 1);
					break;
				case 1:
					glColor4f(0, 1, 0, 1);
					break;
				case 2:
					glColor4f(1, 0, 0, 1);
					break;
				}
					glTranslatef(0, 0, -main_road->road_length);
					glRotatef(90, 0, 1, 0);
					glTranslatef(i.x, i.y + 55, -i.z);
					glutSolidCube(5);
			}
			glPopMatrix();
		}
	}
	if (main_road->Rroad) {
		for (Coin &i : main_road->Rroad->GetCoinList()) {
			glPushMatrix(); {
				set_Coin_material(i.kind);
				switch (i.kind) {
				case 0:
					glColor4f(0, 0, 1, 1);
					break;
				case 1:
					glColor4f(0, 1, 0, 1);
					break;
				case 2:
					glColor4f(1, 0, 0, 1);
					break;
				}
				glTranslatef(0, 0, -main_road->road_length);
				glRotatef(-90, 0, 1, 0);
				glTranslatef(i.x, i.y + 55, -i.z);
				glutSolidCube(5);
			}
			glPopMatrix();
		}
	}
	set_default_material();
	glColor4f(1, 1, 1, 1);
}

GLvoid CGamePlayScene::set_Coin_material(int kind)
{
	switch (kind) {
	case 0:
	{
		float mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
		float mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
		float mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
		float shine = 51.2f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
	}
	break;
	case 1:
	{
		float mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
		float mat_diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
		float mat_specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
		float shine = 76.8f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
	}
		glColor4f(0, 1, 0, 1);
		break;
	case 2:
	{
		float mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
		float mat_diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
		float mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
		float shine = 76.8f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
	}
		glColor4f(1, 0, 0, 1);
		break;
	}

}



GLvoid CGamePlayScene::set_default_material()
{
	float mat_ambient[] = { 0.2f,0.2f,0.2f,1.0f };
	float mat_diffuse[] = { 0.8f,0.8f,0.8f,1.0f };
	float mat_specular[] = { 0.0f,0.0f,0.0f,1.0f };
	float shine = 0.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);

	return GLvoid();
}

GLvoid CGamePlayScene::ObstacleFrame(int kind, float width, float length) {
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(12));
	switch (kind) {
	case 0:		// 우로 피할수 있는 장애물
		glNormal3f(1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width / 4.f, 40, -length);
		glTexCoord2f(1, 0);
		glVertex3f(width / 4.f, 0, -length);
		glTexCoord2f(0, 0);
		glVertex3f(width / 4.f, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(width / 4.f, 40, length);
		glEnd();

		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 40, length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 0, -length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 40, -length);
		glEnd();

		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 40, length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 40, -length);
		glTexCoord2f(0, 0);
		glVertex3f(width / 4.f, 40, -length);
		glTexCoord2f(0, 1);
		glVertex3f(width / 4.f, 40, length);
		glEnd();

		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width / 4.f, 40, length);
		glTexCoord2f(1, 0);
		glVertex3f(width / 4.f, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 40, length);
		glEnd();
		break;

	case 1:			// 좌로 피할수 있는 장애물
		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width / 4.f, 40, -length);
		glTexCoord2f(1, 0);
		glVertex3f(-width / 4.f, 0, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width / 4.f, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(-width / 4.f, 40, length);
		glEnd();

		glNormal3f(1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 40, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 0, -length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 40, -length);
		glEnd();

		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 40, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 40, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width / 4.f, 40, -length);
		glTexCoord2f(0, 1);
		glVertex3f(-width / 4.f, 40, length);
		glEnd();

		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width / 4.f, 40, length);
		glTexCoord2f(1, 0);
		glVertex3f(-width / 4.f, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 40, length);
		glEnd();
		break;

	case 2:			//점프로 피할수 있는 장애물
		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 10, -length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 0, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 10, length);
		glEnd();

		glNormal3f(1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 10, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 0, -length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 10, -length);
		glEnd();

		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 10, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 10, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 10, -length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 10, length);
		glEnd();

		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 10, length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 10, length);
		glEnd();
		break;

	case 3:			//슬라이딩으로 피할수 있는 장애물
		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 50, -length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 10, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 10, length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 50, length);
		glEnd();

		glNormal3f(1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 50, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 10, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 10, -length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 50, -length);
		glEnd();

		/*
		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 50, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 10, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 10, -length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 50, length);
		glEnd();
		*/
		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 50, length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 10, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 10, length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 50, length);
		glEnd();
		break;

	case 4:			//슬라이딩으로 피할수 있는 장애물
		glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(13));
		glDisable(GL_LIGHTING);

		if (player.autorun == ItemState::None) {
			glColor4f(1, 1, 1, 0.3);
		}
		else if (player.autorun == ItemState::Act) {
			glColor4f(0, 1, 1, 0.3);
		}

		glNormal3f(-1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 50, -length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 0, -length);
		glTexCoord2f(0, 0);
		glVertex3f(-width, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(-width, 50, length);
		glEnd();

		glNormal3f(1, 0, 0);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(width, 50, length);
		glTexCoord2f(1, 0);
		glVertex3f(width, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 0, -length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 50, -length);
		glEnd();

		/*
		glBegin(GL_QUADS);
		glVertex3f(width, 50, length);
		glVertex3f(width, 0, -length);
		glVertex3f(-width, 0, -length);
		glVertex3f(-width, 50, length);
		glEnd();
		*/

		glNormal3f(0, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(-width, 50, length);
		glTexCoord2f(1, 0);
		glVertex3f(-width, 0, length);
		glTexCoord2f(0, 0);
		glVertex3f(width, 0, length);
		glTexCoord2f(0, 1);
		glVertex3f(width, 50, length);
		glEnd();

		glEnable(GL_LIGHTING);
		break;
	}
	set_default_material();
	glDisable(GL_TEXTURE_2D);
}

GLvoid CGamePlayScene::RoadFrame(float width, float length) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(1));
	
	GLfloat emission[] = { 143 / 255.f,195 / 255.f,31 / 255.f,1 };
	GLfloat default_emission[] = { 0,0,0,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, emission);

	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(width, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3f(width, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, -length + width);
	glTexCoord2f(1, 0);
	glVertex3f(width, 50, -length + width);
	glEnd();

	glNormal3f(-1, 0, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-width, 50, -length + width);
	glTexCoord2f(0, 1);
	glVertex3f(-width, 0, -length + width);
	glTexCoord2f(1, 1);
	glVertex3f(-width, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-width, 50, 0);
	glEnd();

	glNormal3f(0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, m_pFramework->get_IngameObjID(0));
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-width, 50, -length + width);
	glTexCoord2f(0, 1);
	glVertex3f(-width, 50, 0);
	glTexCoord2f(1, 1);
	glVertex3f(width, 50, 0);
	glTexCoord2f(1, 0);
	glVertex3f(width, 50, -length + width);
	glEnd();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, default_emission);
	glDisable(GL_TEXTURE_2D);
}