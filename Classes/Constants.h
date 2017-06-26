#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"

using namespace std;

// object pool size
static const int POOL_SIZE = 30;

// collision bitmasks
static const int COLLISION_BITMASK_ASTEROID = 1;
static const int COLLISION_BITMASK_BULLET = 2;
static const int COLLISION_BITMASK_SPACESHIP = 3;

// image names
static const std::string SPACEBODY = "meteor";
static const std::string SPACESHIP = "ship";
static const std::string BULLETBODY = "laser";
static const std::string BACKGROUND_IMG = "background.png";
static const std::string GAME_BANNER_IMG = "gamename.png";

static const std::string SPACESHIP_COLLISION = "Particles/shipCollision.plist";
static const std::string SPACESHIP_EXPLOSION = "Particles/shipExplosion.plist";
static const std::string BULLET_COLLISION = "Particles/bulletCollision.plist";
static const std::string ASTEROID_EXPLOSION = "Particles/meteorExplosion.plist";

static const std::string FONT_NAME = "fonts/spacefont.ttf";

// sound names
static const std::string SOUND_BGM = "Audio/bgm.mp3";
static const std::string SOUND_EXP_ASTEROID = "Audio/explosion_asteroid.mp3";
static const std::string SOUND_EXP_SHIP = "Audio/explosion_ship.mp3";

// layer orders
enum Z_ORDER {
	PARALLAX_LAYER = 0,
	BG_LAYER = 1,
	HUD_LAYER = 4,
	BUTTONS = 5
};

// game scenes
enum SCENE {
	MAIN_SCENE = 0,
	GAME_SCENE
};
