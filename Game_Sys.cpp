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
			if (i.kind != 4) {
				if (player.autorun == None && player.invincible == None)
				player.death = true;
			}
			if (i.kind == 4 && !kind4_bool) {
				player.fever_gauge += 15;
				kind4_bool = true;
				kind4_frame = 0;
			}
		}
	}
	if (player.autorun == None) {
		Kind4Effect(player.speed, frametime);
	}
	else if (player.autorun == Act) {
		Kind4Effect(player.item.not_autorun_speed, frametime);
	}

	if (main_road->road_length + player.z < -60 && player.state != ActState::Jump) {
		player.y -= player.jump_gravity * frametime;
		player.jump_gravity += gravity / (50.f * (1 / gravity)) * frametime;;
		if (player.y <= -20) {
			player.death = true;
		}
	}

}

GLvoid CGamePlayScene::Kind4Effect(float speed, float frametime) {

	if (kind4_bool) {
		if (kind4_frame == 0) {
			camera_z += speed * 3 * frametime;
			if (camera_z > 360) {
				camera_z = 0;
				kind4_frame++;
			}
		}
		if (kind4_frame == 1) {
			camera_z += speed * 2 * frametime;
			if (camera_z > 10) {
				kind4_frame++;
			}
		}
		if (kind4_frame == 2) {
			camera_z += speed * 1 * frametime;
			if (camera_z > 20) {
				kind4_frame++;
			}
		}
		if (kind4_frame == 3) {
			camera_z += speed * 0.5 * frametime;
			if (camera_z > 30) {
				kind4_frame++;
			}
		}
		if (kind4_frame == 4) {
			camera_z -= speed * 0.5 * frametime;
			if (camera_z < 0) {
				camera_z = 0;
				kind4_bool = false;
			}
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
			//printf("0 충돌함");
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
			//printf("1 충돌함");
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
			//printf("2 충돌함");
			return true;
		}
		break;
	case 3:
		if (player.state != ActState::Slide && 
			-player.z - 5 < t.z + 2.5 &&
			-player.z + 5 > t.z - 2.5) {
			//printf("3 충돌함");
			return true;
		}
		break;
	case 4:
		if (player.x - 5 < ROAD_WIDTH &&
			player.x + 5 > -ROAD_WIDTH &&
			player.y - 5 < 50 &&
			player.y + 5 > 0 &&
			-player.z - 5 < t.z + 10 &&
			-player.z + 5 > t.z - 10) {
			//printf("4 충돌함");
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
				player.fever_gauge = 150;
			}
			if (i.kind == 2) {
				player.invincible = ItemState::Act;
				player.item.invincible_timer = 0;
			}
			else {
				m_pFramework->play_fx(2 + score % 7);
				score++;

				if (score == 100)
					m_pFramework->play_voice(m_pFramework->get_charID(), 1);
				else if (score == 300)
					m_pFramework->play_voice(m_pFramework->get_charID(), 2);
				else if (score == 500)
					m_pFramework->play_voice(m_pFramework->get_charID(), 3);
				else if (score == 1000)
					m_pFramework->play_voice(m_pFramework->get_charID(), 4);
				else if (score % 500 == 0)
					m_pFramework->play_voice(m_pFramework->get_charID(), 5);
				player.fever_gauge += 1.5;
			}
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
		//printf("코인 충돌함");
		return true;
	}
	return false;
}

