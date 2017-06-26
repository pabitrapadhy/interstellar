#pragma once

#include "cocos2d.h"
#include "IController.h"
USING_NS_CC;

enum GameObjectType {
	ASTEROID = 0,
	BULLET
};

class Asteroid;
class Bullet;
class GameObjectPool : public IController {
private:
	int poolSize;

protected:
	GameObjectPool();
	~GameObjectPool();

public:
	static GameObjectPool* getInstance();

	// variables
	std::vector<Asteroid*> asteroidPool;
	std::vector<Bullet*> bulletPool;

	// methods
	void initListeners(Ref* target);
    void removeListeners();
    void registerListener(Ref* target, const char* event);
    void deregisterListener(const char* event);
	void createGameObjectPool(GameObjectType type);
	Asteroid* getAsteroid(int index);
	Bullet* getBullet(int index);
	int getPoolSize();
	void debug();
};