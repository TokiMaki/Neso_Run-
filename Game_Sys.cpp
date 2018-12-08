#include "stdafx.h"
#include "GamePlayScene.h"

#define ROAD_WIDTH 60

bool CGamePlayScene::NextRoadcheck(int dir) {
	if (main_road->road_length + player.z >= 210) {
		return false;
	}
	/*
	else if (main_road->road_length + player.z < 30 && player.dir == 0) {
		return false;
	}
	*/
	else {
		if (dir == 1 && main_road->Lroad != nullptr) {
			return true;
		}
		else if (dir == 0 && main_road->Rroad != nullptr) {
			return true;
		}
	}
	return false;
}

GLvoid CGamePlayScene::Collision_Obstacle() {			// 장애물 충돌체크
	for (Obstacle &i : main_road->GetObstacleList()) {
		if (Collision_Obstacle_Cube(i)) {

		}
	}
}

bool CGamePlayScene::Collision_Obstacle_Cube(Obstacle t) {
	switch (t.kind) {
	case 0:
		if (player.x - 5 < ROAD_WIDTH / 4.f &&
			player.x + 5 > -ROAD_WIDTH &&
			player.y - 5 < 40 &&
			player.y + 5 > 0 &&
			-player.z - 5 < t.z + 2.5 &&
			-player.z + 5 > t.z - 2.5) {
			printf("0 충돌함");
			return true;
		}
		break;
	case 1:
		if (player.x - 5 < ROAD_WIDTH &&
			player.x + 5 > -ROAD_WIDTH / 4.f &&
			player.y - 5 < 40 &&
			player.y + 5 > 0 &&
			-player.z - 5 < t.z + 2.5 &&
			-player.z + 5 > t.z - 2.5) {
			printf("1 충돌함");
			return true;
		}
		break;
	case 2:
		if (player.x - 5 < ROAD_WIDTH &&
			player.x + 5 > -ROAD_WIDTH &&
			player.y - 5 < 10 &&
			player.y + 5 > 0 &&
			-player.z - 5 < t.z + 2.5 &&
			-player.z + 5 > t.z - 2.5) {
			printf("2 충돌함");
			return true;
		}
		break;
	case 3:
		if (player.state != State::Slide && 
			-player.z - 5 < t.z + 2.5 &&
			-player.z + 5 > t.z - 2.5) {
			printf("3 충돌함");
			return true;
		}
		break;
	}
	return false;
}


GLvoid CGamePlayScene::Collision_Coin() {			// 장애물 충돌체크
	for (Coin &i : main_road->GetCoinList()) {
		if (Collision_Coin_Cube(i)) {

		}
	}
}

bool CGamePlayScene::Collision_Coin_Cube(Coin t) {
	if (player.x - 5 < t.x + 5 &&
		player.x + 5 > t.x - 5 &&
		player.y - 5 < t.y + 5 &&
		player.y + 5 > t.y - 5 &&
		-player.z - 5 < t.z + 5 &&
		-player.z + 5 > t.z - 5) {
		printf("코인 충돌함");
		return true;
	}
	return false;
}

