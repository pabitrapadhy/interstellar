#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Bullet : public Ref {
private:
public:
	static Bullet* create();
	bool initialize();
	void makeShoot();
};