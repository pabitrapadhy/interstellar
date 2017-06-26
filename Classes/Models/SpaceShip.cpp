#include "SpaceShip.h"
#include "Constants.h"
#include "SceneController.h"

USING_NS_CC;

SpaceShip* SpaceShip::create() {
	SpaceShip* spaceship = new SpaceShip();
	if (!spaceship) CC_ASSERT(false);
	return spaceship;
}

SpaceShip::SpaceShip() {
	this->life = 5;
	this->texture = nullptr;
	this->body = nullptr;
}

bool SpaceShip::initialize(Layer* layer) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// selecting a random spaceship type
	int shipType = (rand() % 12) + 1;
	std::stringstream ss;
	ss << SPACESHIP << shipType << ".png";
	std::string str = ss.str().c_str();

	// assigning asteroid texture
	this->texture = Sprite::createWithSpriteFrameName(str);
	if (this->texture) {
		float width = this->texture->getContentSize().width;
		float height = this->texture->getContentSize().height;

		this->texture->setVisible(true);
		// assigning a physics body to the spaceship
		this->body = PhysicsBody::createBox(this->texture->getContentSize());
		if (this->body) {
			this->body->setCollisionBitmask(COLLISION_BITMASK_SPACESHIP);
			this->body->setContactTestBitmask(true);
			this->body->setDynamic(false);
			this->body->setGravityEnable(false);
			this->body->setRotationEnable(false);
			this->texture->setPhysicsBody(body);
		} else {
			CCLOG("pabitra: physics body error");
			return false;
		}

		// add the asteroid to a layer in scene
		this->texture->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.2);
		layer->addChild(this->texture, 3);

	} else {
		CCLOG("pabitra: asteroid texture error");
		return false;
	}

	// Touch listeners added to the layer to which spaceship is added
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SpaceShip::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SpaceShip::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SpaceShip::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(SpaceShip::onTouchEnded, this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layer);

	return true;
}

Vec2 SpaceShip::getPosition() {
	if (this->texture) return this->texture->getPosition();
	return Vec2(-100, 0);
}

bool SpaceShip::hasTexture() {
	(this->texture) ? true : false;
}

bool SpaceShip::onTouchBegan(Touch* touch, Event* event) {
	if (!this->texture) return false;
	this->lastTouchLoc = touch->getLocation();
	return true;
}

void SpaceShip::onTouchMoved(Touch* touch, Event* event) {
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	Vec2 touchLoc = touch->getLocation();
	Vec2 diff = touchLoc - this->lastTouchLoc;
	
	Vec2 shipLoc = this->texture->getPosition();
	Size shipSize = this->texture->getContentSize();
	Vec2 finalPos =  shipLoc + diff;

	if (finalPos.x > visibleSize.width - shipSize.width/2) {
		finalPos.x = visibleSize.width - shipSize.width/2;
	} else if (finalPos.x < shipSize.width/2) {
		finalPos.x = shipSize.width/2;
	}

	if (finalPos.y > visibleSize.height - shipSize.height/2) {
		finalPos.y = visibleSize.height - shipSize.height/2;
	} else if (finalPos.y < shipSize.height/2) {
		finalPos.y = shipSize.height/2;
	}

	this->lastTouchLoc = touchLoc;
	this->texture->setPosition(finalPos);
}

void SpaceShip::onTouchEnded(Touch* touch, Event* event) {}

void SpaceShip::explode() {
	if (!this->texture) return;
	auto parent = this->texture->getParent();
	if (!parent) return;

	auto explosion = ParticleSystemQuad::create(SPACESHIP_EXPLOSION);
	explosion->setPosition(this->getPosition());
	explosion->setAutoRemoveOnFinish(true);
	parent->addChild(explosion, 4);

	this->reset();
}

void SpaceShip::reset() {
	if (this->texture) {
		this->texture->stopAllActions();
		this->texture->setVisible(false);

		// removing from the parent layer
		this->texture->removeFromParentAndCleanup(true);
    	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		SceneController::getInstance()->changeScene(SCENE::MAIN_SCENE);
	}
}