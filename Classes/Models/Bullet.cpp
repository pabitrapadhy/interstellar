#include "Bullet.h"
#include "Constants.h"

#define SPEED 0.001f

USING_NS_CC;

Bullet* Bullet::create() {
	Bullet* bullet = new Bullet();
	if (!bullet) CC_ASSERT(false);
	return bullet;
}

Bullet::Bullet() {
	this->texture = nullptr;
	this->body = nullptr;
}

bool Bullet::initialize() {
	return true;
}

Vec2 Bullet::getPosition() {
	if (this->texture) return this->texture->getPosition();
	return Vec2(-100, 0);
}

void Bullet::makeShoot(Layer* layer, Vec2 pos, int index) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	// selecting a bullet type
	int bulletType = 3;
	std::stringstream ss;
	ss << BULLETBODY << bulletType << ".png";
	std::string str = ss.str().c_str();

	// assigning bullet texture
	this->texture = Sprite::createWithSpriteFrameName(str);
	if (this->texture) {
		float width = this->texture->getContentSize().width;
		float height = this->texture->getContentSize().height;

		this->texture->setScaleY(1.2f);
		this->texture->setVisible(true);
		// assigning a physics body to bullet
		this->body = PhysicsBody::createBox(this->texture->getContentSize());
		if (this->body) {
			this->body->setCollisionBitmask(COLLISION_BITMASK_BULLET);
			this->body->setContactTestBitmask(true);
			this->body->setDynamic(false);
			this->body->setRotationEnable(false);
			this->body->setGravityEnable(false);
			this->body->setTag(index);
			this->texture->setPhysicsBody(body);
		} else {
			CCLOG("pabitra: physics body error");
			return;
		}
		this->texture->setPosition(Vec2(pos.x, pos.y + height/2));

		// actions on bullet
		auto move = MoveTo::create(SPEED * visibleSize.height, Vec2(pos.x, pos.y + visibleSize.height + height));
		auto sequence = Sequence::create(move, CallFunc::create(CC_CALLBACK_0(Bullet::reset, this)), nullptr);
		this->texture->runAction(sequence);
		
		// add the bullet to a layer in scene
		layer->addChild(this->texture, 2);

	} else {
		CCLOG("pabitra: bullet texture error");
		return;
	}
}

void Bullet::explode() {
	if (!this->texture) return;
	auto parent = this->texture->getParent();
	if (!parent) return;

	auto explosion = ParticleSystemQuad::create(BULLET_COLLISION);
	explosion->setPosition(this->getPosition());
	explosion->setAutoRemoveOnFinish(true);
	parent->addChild(explosion, 4);
	// GameScene::playEffect(AUDIO_METEOR_EXPLOSION);

	this->reset();
}

void Bullet::reset() {
	if (this->texture) {
		this->texture->stopAllActions();
		this->texture->setVisible(false);
		this->texture->setScaleY(1.0f);

		// removing from the parent layer
		this->texture->removeFromParentAndCleanup(true);
	}
}