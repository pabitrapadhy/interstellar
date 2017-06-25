#include "BulletController.h"
#include "Bullet.h"

USING_NS_CC;

BulletController* BulletController::getInstance() {
	// singleton
	static BulletController instance;
	return &instance;
}

BulletController::BulletController() {}
BulletController::~BulletController() {}

// basic controller properties
void BulletController::initListeners(Ref* target) {};
void BulletController::removeListeners() {};
void BulletController::registerListener(Ref* target, const char* event) {};
void BulletController::deregisterListener(const char* event) {};

// Bullet* BulletController::createBullet() {
// 	Bullet* bullet = Bullet::create();
// 	if (!bullet) {
// 		CC_ASSERT(false);
// 	}
// 	return bullet;
// }

void BulletController::debug() {
	CCLOG("pabitra: object pool debug");
}
