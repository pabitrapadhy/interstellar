#include "SpaceShipController.h"
#include "GameObjectPool.h"
#include "SpaceShip.h"

USING_NS_CC;

SpaceShipController* SpaceShipController::getInstance() {
	// singleton
	static SpaceShipController instance;
	return &instance;
}

SpaceShipController::SpaceShipController() {
	this->spaceship = nullptr;
}

// basic controller properties
void SpaceShipController::initListeners(Ref* target) {};
void SpaceShipController::removeListeners() {};
void SpaceShipController::registerListener(Ref* target, const char* event) {};
void SpaceShipController::deregisterListener(const char* event) {};

SpaceShip* SpaceShipController::createSpaceShip(Layer* layer) {
	if (!this->spaceship) {
		this->spaceship = SpaceShip::create();
		this->spaceship->initialize(layer);
		if (!this->spaceship) {
			CC_ASSERT(false);
		}
		return this->spaceship;
	} else {
		return this->spaceship;
	}
}

SpaceShip* SpaceShipController::getSpaceShip() {
	if (this->spaceship && this->spaceship->hasTexture()) return this->spaceship;
	return nullptr;
}

void SpaceShipController::setSpaceShip(SpaceShip* ship) {
	this->spaceship = ship;
}

void SpaceShipController::onCollisionShip() {
	if (this->spaceship) {
		this->spaceship->explode();
		delete this->spaceship;
		this->spaceship = nullptr;
	}
}

void SpaceShipController::debug() {
	CCLOG("pabitra: object pool debug");
}
