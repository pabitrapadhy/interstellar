#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Bullet : public Ref {
private:
	Sprite* texture;
	PhysicsBody* body;

public:
	Bullet();

	static Bullet* create();
	bool initialize();
	Vec2 getPosition();
	void makeShoot(Layer* layer, Vec2 pos, int index);
	void explode();
	void reset();
};