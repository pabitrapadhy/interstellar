#include "BulletController.h"
#include "GameObjectPool.h"
#include "SpaceShipController.h"
#include "SpaceShip.h"
#include "Bullet.h"

USING_NS_CC;

BulletController* BulletController::getInstance() {
	// singleton
	static BulletController instance;
	return &instance;
}

BulletController::BulletController() {
	this->poolIndex = 0;
}

BulletController::~BulletController() {}

// basic controller properties
void BulletController::initListeners(Ref* target) {};
void BulletController::removeListeners() {};
void BulletController::registerListener(Ref* target, const char* event) {};
void BulletController::deregisterListener(const char* event) {};

Bullet* BulletController::createBullet() {
	Bullet* bullet = Bullet::create();
	if (!bullet) {
		CC_ASSERT(false);
	}
	return bullet;
}

void BulletController::shootBullets(Layer* layer) {
	int poolSize = GameObjectPool::getInstance()->getPoolSize();
	Bullet* obj = GameObjectPool::getInstance()->getBullet(this->poolIndex);
	SpaceShip* ship = SpaceShipController::getInstance()->getSpaceShip();
	if (!ship) return;
	Vec2 pos = ship->getPosition();
	if (obj) obj->makeShoot(layer, pos, this->poolIndex);

	// handle pool index rotation
	this->poolIndex++;
    if (this->poolIndex == poolSize) this->poolIndex = 0;
}

void BulletController::onCollisionBullet(int index) {
	Bullet* obj = GameObjectPool::getInstance()->getBullet(index);
	if (obj) obj->explode();
}

void BulletController::debug() {
	CCLOG("pabitra: object pool debug");
}
