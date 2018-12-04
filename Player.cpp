#include "stdafx.h"
#include "Run_time_Framework.h"

#define UP 0
#define LEFT 3
#define DOWN 2
#define RIGHT 1

GLvoid CRun_time_Framework::Player_Update() {
	player.z -= 5;
}