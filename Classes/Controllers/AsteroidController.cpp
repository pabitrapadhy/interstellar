#include "AsteroidController.h"
#include "GameObjectPool.h"
#include "Asteroid.h"

USING_NS_CC;

AsteroidController* AsteroidController::getInstance() {
	// singleton
	static AsteroidController instance;
	return &instance;
}

AsteroidController::AsteroidController() {
	this->poolIndex = 0;
}

// basic controller properties
void AsteroidController::initListeners(Ref* target) {};
void AsteroidController::removeListeners() {};
void AsteroidController::registerListener(Ref* target, const char* event) {};
void AsteroidController::deregisterListener(const char* event) {};

Asteroid* AsteroidController::createAsteroid() {
	Asteroid* asteroid = Asteroid::create();
	if (!asteroid) {
		CC_ASSERT(false);
	}
	return asteroid;
}

void AsteroidController::throwAsteroid(Layer* layer) {
	int poolSize = GameObjectPool::getInstance()->getPoolSize();
	Asteroid* obj = GameObjectPool::getInstance()->getAsteroid(this->poolIndex);
	if (obj) obj->makeFly(layer);

	// handle pool index rotation
	this->poolIndex++;
    if (this->poolIndex == poolSize) this->poolIndex = 0;
}

void AsteroidController::stopAsteroidMovement() {

}

void AsteroidController::debug() {
	CCLOG("pabitra: object pool debug");
}
