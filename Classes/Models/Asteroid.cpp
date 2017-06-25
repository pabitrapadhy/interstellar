#include "Asteroid.h"
#include "Constants.h"

#define SPEED 0.002f

USING_NS_CC;

Asteroid* Asteroid::create() {
	Asteroid* asteroid = new Asteroid();
	if (!asteroid) CC_ASSERT(false);
	return asteroid;
}

Asteroid::Asteroid() {
	this->texture = nullptr;
	this->body = nullptr;
}

bool Asteroid::initialize() {
	return true;
}

void Asteroid::makeFly(Layer* layer) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// selecting a random asteroid type
	int asteroidType = (rand() % 8) + 1;
	std::stringstream ss;
	ss << SPACEBODY << asteroidType << ".png";
	std::string str = ss.str().c_str();

	// assigning asteroid texture
	this->texture = Sprite::createWithSpriteFrameName(str);
	if (this->texture) {
		float width = this->texture->getContentSize().width;
		float height = this->texture->getContentSize().height;

		this->texture->setVisible(true);
		// assigning a physics body to asteroid
		this->body = PhysicsBody::createCircle(width/2);
		if (this->body) {
			this->body->setCollisionBitmask(COLLISION_BITMASK_ASTEROID);
			this->body->setContactTestBitmask(true);
			this->body->setDynamic(false);
			this->texture->setPhysicsBody(body);
		} else {
			CCLOG("pabitra: physics body error");
			return;
		}
		// finding the source and destination of the asteroid
		auto initialPosX = (rand() % static_cast<int>(visibleSize.width));
		auto finalPosX = (rand() % static_cast<int>(visibleSize.width));
		this->texture->setPosition(Vec2(origin.x + initialPosX, origin.y + visibleSize.height + height));

		// actions on asteroid
		auto move = MoveTo::create(SPEED * visibleSize.height, Vec2(origin.x + finalPosX, origin.y -height));
		auto rotate = RepeatForever::create(RotateBy::create(SPEED * visibleSize.height, 360));
		auto sequence = Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Asteroid::reset, this)), nullptr);
		auto spawn = Spawn::create(rotate, move, nullptr);
		this->texture->runAction(spawn);
		
		// add the asteroid to a layer in scene
		layer->addChild(this->texture, 2);

	} else {
		CCLOG("pabitra: asteroid texture error");
		return;
	}
}

void Asteroid::reset() {
	if (this->texture) {
		this->texture->stopAllActions();
		this->texture->setVisible(false);

		// removing from the parent layer
		this->texture->removeFromParentAndCleanup(true);
	}
}