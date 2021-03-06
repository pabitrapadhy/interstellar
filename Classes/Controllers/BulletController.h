#pragma once

#include "cocos2d.h"
#include "IController.h"

USING_NS_CC;

class Bullet;
class BulletController : public IController {
private:
	int poolIndex;
	
protected:
	BulletController();
	~BulletController();

public:
	static BulletController* getInstance();

	// methods
	void initListeners(Ref* target);
    void removeListeners();
    void registerListener(Ref* target, const char* event);
    void deregisterListener(const char* event);
    Bullet* createBullet();
    void shootBullets(Layer* layer);
    void onCollisionBullet(int index);
	void debug();
};