#pragma once

#include "cocos2d.h"

USING_NS_CC;

class SpaceShip : public Ref {
private:
	int life;
	Sprite* texture;
	PhysicsBody* body;
public:
	SpaceShip();

	// variables
	Vec2 lastTouchLoc;

	// touch functions
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	static SpaceShip* create();
	bool initialize(Layer* layer);
	void reset();
};