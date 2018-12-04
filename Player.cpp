#include "stdafx.h"
#include "Run_time_Framework.h"

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

GLvoid CRun_time_Framework::Player_Update() {
	switch(player.dir) {
		case UP:
			player.z--;
			break;
		case LEFT:
			player.x--;
			break;
		case DOWN:
			player.z++;
			break;
		case RIGHT:
			player.x++;
			break;
	}
}