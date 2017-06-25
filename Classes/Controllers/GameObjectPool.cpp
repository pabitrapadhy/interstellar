#include "GameObjectPool.h"
#include "AsteroidController.h"
#include "BulletController.h"
#include "Constants.h"

USING_NS_CC;

GameObjectPool* GameObjectPool::getInstance() {
	// singleton
	static GameObjectPool instance;
	return &instance;
}

GameObjectPool::GameObjectPool() {
	this->poolSize = POOL_SIZE;
}

GameObjectPool::~GameObjectPool() {}

// basic controller properties
void GameObjectPool::initListeners(Ref* target) {};
void GameObjectPool::removeListeners() {};
void GameObjectPool::registerListener(Ref* target, const char* event) {};
void GameObjectPool::deregisterListener(const char* event) {};

void GameObjectPool::createGameObjectPool(GameObjectType type) {
	if ((type == GameObjectType::ASTEROID)) {
		CCLOG("pabitra: creating asteroids pool");
		for (int i = 0; i < this->poolSize; ++i) {
			Asteroid* asteroid = AsteroidController::getInstance()->createAsteroid();
			this->asteroidPool.push_back(asteroid);
		}
	} else if ((type == GameObjectType:: BULLET) && !this->bulletPool.size()) {
		CCLOG("pabitra: creating bullets pool");
		for (int i = 0; i < this->poolSize; ++i) {
			// Bullet* bullet = BulletController::getInstance()->createBullet();
			// this->bulletPool.push_back(bullet);
		}
	}
}

Asteroid* GameObjectPool::getAsteroid(int index) {
	if (this->asteroidPool.size()) {
		return this->asteroidPool.at(index);
	}
	return nullptr;
}

int GameObjectPool::getPoolSize() {
	return this->poolSize;
}

void GameObjectPool::debug() {
	CCLOG("pabitra: object pool debug");
}
