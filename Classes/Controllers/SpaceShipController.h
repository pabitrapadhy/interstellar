#pragma once

#include "cocos2d.h"
#include "IController.h"

USING_NS_CC;

class SpaceShip;
class SpaceShipController : public IController {
private:
    SpaceShip* spaceship;
    
protected:
	SpaceShipController();

public:
	static SpaceShipController* getInstance();

	// methods
	void initListeners(Ref* target);
    void removeListeners();
    void registerListener(Ref* target, const char* event);
    void deregisterListener(const char* event);    
    SpaceShip* createSpaceShip(Layer* layer);
    void setSpaceShip(SpaceShip* ship);
	void debug();
};