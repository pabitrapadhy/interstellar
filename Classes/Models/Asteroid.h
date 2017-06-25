#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Asteroid : public Ref {
private:
	Sprite* texture;
	PhysicsBody* body;
public:
	Asteroid();

	static Asteroid* create();
	bool initialize();
	void makeFly(Layer* layer);
	void reset();
};