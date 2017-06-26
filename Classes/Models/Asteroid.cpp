#include "Asteroid.h"
#include "Constants.h"

#define SPEED 0.0015f

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

Vec2 Asteroid::getPosition() {
	if (this->texture) return this->texture->getPosition();
	return Vec2(-100, 0);
}

void Asteroid::makeFly(Layer* layer, int index) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	// selecting a random asteroid type
	int asteroidType = (rand() % 14) + 1;
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
			this->body->setTag(index);
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
		layer->addChild(this->texture, 3);

	} else {
		CCLOG("pabitra: asteroid texture error");
		return;
	}
}

void Asteroid::explode() {
	if (!this->texture) return;
	auto parent = this->texture->getParent();
	if (!parent) return;

	auto explosion = ParticleSystemQuad::create(ASTEROID_EXPLOSION);
	explosion->setPosition(this->getPosition());
	explosion->setAutoRemoveOnFinish(true);
	parent->addChild(explosion, 4);

	this->reset();
	// GameScene::playEffect(AUDIO_METEOR_EXPLOSION);
}

void Asteroid::reset() {
	if (this->texture) {
		this->texture->stopAllActions();
		this->texture->setVisible(false);

		// removing from the parent layer
		this->texture->removeFromParentAndCleanup(true);
	}
}