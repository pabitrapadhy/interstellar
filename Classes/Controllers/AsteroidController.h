#pragma once

#include "cocos2d.h"
#include "IController.h"

USING_NS_CC;

class Asteroid;
class AsteroidController : public IController {
private:
	int poolIndex;

protected:
	AsteroidController();

public:
	static AsteroidController* getInstance();

	// methods
	void initListeners(Ref* target);
    void removeListeners();
    void registerListener(Ref* target, const char* event);
    void deregisterListener(const char* event);
    Asteroid* createAsteroid();
    void throwAsteroid(Layer* layer);
    void stopAsteroidMovement();
    void onCollisionAsteroid(int index);
	void debug();
};