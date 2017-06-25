#pragma once

#include <iostream>
#include <string>

using namespace std;

// object pool size
static const int POOL_SIZE = 30;

// collision bitmasks
static const int COLLISION_BITMASK_ASTEROID = 1;
static const int COLLISION_BITMASK_BULLET = 2;
static const int COLLISION_BITMASK_SHIP = 3;

// image names
static const std::string SPACEBODY = "meteor";
static const std::string BACKGROUND_IMG = "background.png";
static const std::string GAME_BANNER_IMG = "gamename.png";

// layer orders
enum Z_ORDER {
	PARALLAX_LAYER = 0,
	BG_LAYER = 1,
	HUD_LAYER = 4,
	BUTTONS = 5
};
