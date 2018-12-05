#include "stdafx.h"
#include "Run_time_Framework.h"

bool CRun_time_Framework::NextRoadcheck(int dir) {
	if (main_road->road_length + player.z >= 120) {
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