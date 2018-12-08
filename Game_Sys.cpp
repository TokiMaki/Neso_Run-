#include "stdafx.h"
#include "GamePlayScene.h"

#define ROAD_WIDTH 60

bool CGamePlayScene::NextRoadcheck(int dir) {
	if (main_road->road_length + player.z >= 180) {
		return false;
	}
	else if (main_road->road_length + player.z < -45) {
		return false;
	}
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

GLvoid CGamePlayScene::Collision_Obstacle(float frametime) {			// 장애물 충돌체크
	float gravity = ((player.speed) / 4.f * 3.f);

	for (Obstacle &i : main_road->GetObstacleList()) {
		if (Collision_Obstacle_Cube(i)) {
			player.death = true;
		}
	}
	if (main_road->road_length + player.z < -60) {
		player.y -= player.jump_gravity * frametime;
		player.jump_gravity += gravity / (50.f * (1 / gravity)) * frametime;;
		if (player.y <= -20) {
			player.death = true;
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
		if (player.state != ActState::Slide && 
			-player.z - 5 < t.z + 2.5 &&
			-player.z + 5 > t.z - 2.5) {
			printf("3 충돌함");
			return true;
		}
		break;
	}
	return false;
}


GLvoid CGamePlayScene::Collision_Coin() {			// 아이템 & 코인 충돌체크
	for (Coin &i : main_road->GetCoinList()) {
		if (Collision_Coin_Cube(i)) {
			if (i.kind == 1) {
				if (player.autorun == ItemState::None) {
					player.item_timer.not_autorun_speed = player.speed;
					player.speed = 800 / 1000.f;
					m_pFramework->set_bgm(3);
					
				}
				player.autorun = ItemState::Act;
				player.item_timer.autorun_timer = 0;
			}
			if (i.kind == 2) {
				player.invincible = ItemState::Act;
				player.item_timer.invincible_timer = 0;
			}
			score++;
			main_road->CoinRemove(i);
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

