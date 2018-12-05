#include "stdafx.h"
#include "GamePlayScene.h"

bool CGamePlayScene::NextRoadcheck(int dir) {
	if (main_road->road_length + player.z >= 240) {
		return false;
	}
	else if (main_road->road_length + player.z <= 0) {
		return false;
	}
	else {
		if (dir == 1 && main_road->Lroad != NULL) {
			return true;
		}
		else if (dir == 0 && main_road->Rroad != NULL) {
			return true;
		}
	}
	return false;
}