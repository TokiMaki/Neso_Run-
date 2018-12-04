#include "stdafx.h"
#include "Run_time_Framework.h"

#define MIN_ROAD 1200
#define MAX_ROAD 1000

GLvoid CRun_time_Framework::Create_Road() {
	Road_Tree* temp;
	srand(time(NULL));
	int road_random_temp = 0;
	temp = main_road;
	temp = (Road_Tree*)malloc(sizeof(Road_Tree));

		temp->road_length = (rand() % MAX_ROAD) + MIN_ROAD;
		road_random_temp = rand() % 2;
		road_random_temp = 1;

		if (road_random_temp == 0) {
			temp->Lroad = (Road_Tree*)malloc(sizeof(Road_Tree));
			temp->Lroad->road_length = (rand() % MAX_ROAD) + MIN_ROAD;
			temp->Rroad = NULL;
		}

		if (road_random_temp == 1) {
			temp->Rroad = (Road_Tree*)malloc(sizeof(Road_Tree));
			temp->Lroad = NULL;
			temp->Rroad->road_length = (rand() % MAX_ROAD) + MIN_ROAD;
		}

		if (road_random_temp == 2) {

			temp->Lroad = (Road_Tree*)malloc(sizeof(Road_Tree));
			temp->Lroad->road_length = (rand() % MAX_ROAD) + MIN_ROAD;

			temp->Rroad = (Road_Tree*)malloc(sizeof(Road_Tree));
			temp->Rroad->road_length = (rand() % MAX_ROAD) + MIN_ROAD;

		}

		if (main_road != NULL) {
			if (main_road->Lroad != NULL) {
				delete(main_road->Lroad);
			}
			if (main_road->Rroad != NULL) {
				delete(main_road->Rroad);
			}
			delete(main_road);
		}

		main_road = temp;

}

GLvoid CRun_time_Framework::Draw_Road() {
	glPushMatrix();
	glTranslatef(0, -75, 0);
	glColor3f(0, 1, 0);

	RoadFrame(120, main_road->road_length);
	RoadFrame(120, -main_road->road_length);

	if (main_road->Lroad != NULL) {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(-90, 0, 1, 0);
		RoadFrame(120, main_road->Lroad->road_length);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(-90, 0, 1, 0);
		RoadFrame(120, 120);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}

	if (main_road->Rroad != NULL) {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(90, 0, 1, 0);
		RoadFrame(120, main_road->Rroad->road_length);
		//glutSolidCube(main_road->Rroad->road_length);
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(0, 0, -main_road->road_length);
		glRotatef(90, 0, 1, 0);
		RoadFrame(120, 120);
		//glutSolidCube(main_road->Lroad->road_length);
		glPopMatrix();
	}

	glPopMatrix();
}

GLvoid CRun_time_Framework::RoadFrame(float width, float length) {

	glBegin(GL_QUADS);
	glVertex3f(-width, 50, 0);
	glVertex3f(-width, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 50, 0);
	glEnd();	glBegin(GL_QUADS);
	glVertex3f(width, 50, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 0, -length);
	glVertex3f(width, 50, -length);
	glEnd();	glBegin(GL_QUADS);
	glVertex3f(width, 50, -length);
	glVertex3f(width, 0, -length);
	glVertex3f(-width, 0, -length);
	glVertex3f(-width, 50, -length);
	glEnd();	glBegin(GL_QUADS);
	glVertex3f(-width, 50, -length);
	glVertex3f(-width, 0, -length);
	glVertex3f(-width, 0, 0);
	glVertex3f(-width, 50, 0);
	glEnd();	glBegin(GL_QUADS);
	glVertex3f(-width, 50, -length);
	glVertex3f(-width, 50, 0);
	glVertex3f(width, 50, 0);
	glVertex3f(width, 50, -length);
	glEnd();	glBegin(GL_QUADS);
	glVertex3f(-width, 0, 0);
	glVertex3f(-width, 0, -length);
	glVertex3f(width, 0, -length);
	glVertex3f(width, 0, 0);
	glEnd();
}