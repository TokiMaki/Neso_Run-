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

	if (player.item_timer.autorun_timer > 3000) {
		player.autorun_state = AutorunState::None;
	}

}