#include "stdafx.h"
#include "Run_Time_Framework.h"
#include "GamePlayScene.h"

GLvoid CGamePlayScene::Autorun(float frametime) {
	player.item_timer.autorun_timer += frametime;

	if (NextRoadcheck(1)) {
		printf("right in\n");
		player.input_rotate = true;
		player.dir = 1;
	}

	if (NextRoadcheck(0)) {
		printf("left in\n");
		player.input_rotate = true;
		player.dir = 0;
	}

	camera_z += camera_z_dir * frametime;
	if (camera_z > 20) {
		camera_z_dir *= -1;
	}
	if (camera_z < -20) {
		camera_z_dir *= -1;
	}

	if (player.item_timer.autorun_timer > 5000) {
		m_pFramework->set_bgm(2);
		player.autorun = ItemState::None;
		player.speed = player.item_timer.not_autorun_speed;
		player.invincible = ItemState::Act;
		player.item_timer.invincible_timer = 6000;
		camera_z = 0;
	}

}

GLvoid CGamePlayScene::invincible(float frametime) {
	float gravity = ((player.speed) / 4.f * 3.f);

	player.item_timer.invincible_timer += frametime;

	if (main_road->road_length + player.z < -60) {
		player.y -= player.jump_gravity * frametime;
		player.jump_gravity += gravity / (50.f * (1 / gravity)) * frametime;;
		if (player.y <= -20) {
			player.death = true;
		}
	}
	if (player.item_timer.invincible_timer > 6000) {
		if ((player.item_timer.invincible_timer / 100) % 2 == 0)
			player.item_timer.invincible_alpha = 0.5;
		if ((player.item_timer.invincible_timer / 100) % 2 == 1)
			player.item_timer.invincible_alpha = 1;
	}

	if (player.item_timer.invincible_timer > 8000) {
		player.invincible = ItemState::None;
		player.item_timer.invincible_alpha = 0.5;
	}
}