#include "GameScene.h"
#include "GameObjectPool.h"
#include "AsteroidController.h"
#include "SpaceShipController.h"
#include "BulletController.h"
#include "SceneController.h"
#include "SoundController.h"
#include "Constants.h"

using namespace ui;
USING_NS_CC;

Scene* GameScene::createScene() {
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

GameScene::GameScene() {
    this->tickAsteroid = 0.0f;
    this->tickBullet = 0.0f;
    this->parallaxBackground = nullptr;
    this->scoreLabel = nullptr;
    this->highScoreLabel = nullptr;
    this->score = 0;
    this->highScore = 0;
}

bool GameScene::init() {
    if (!Layer::init()) return false;

    this->origin = Director::getInstance()->getVisibleOrigin();
    this->visibleSize = Director::getInstance()->getVisibleSize();

    SoundController::getInstance()->play(SOUND_BGM, true);

    this->setParallaxScrollingBG();
    this->initializeHUD();
    this->addSpaceShip();
    this->scheduleUpdate();

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContact, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void GameScene::onExit() {
    // on exiting the scene, stop the asteroid shower and remove the layer from the scene
    AsteroidController::getInstance()->stopAsteroidMovement();
    this->removeFromParentAndCleanup(true);
}

void GameScene::initializeHUD() {
    // current score
    this->scoreLabel = Label::createWithTTF("0", FONT_NAME, visibleSize.height/15);
    this->scoreLabel->setAlignment(TextHAlignment::CENTER);
    this->scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + 
                                    visibleSize.height - this->scoreLabel->getContentSize().height));
    this->addChild(this->scoreLabel, 5);

    this->highScore = UserDefault::getInstance()->getIntegerForKey("HIGH_SCORE");
    std::stringstream ss;
    ss << "Best: " << this->highScore;
    std::string str = ss.str();

    this->highScoreLabel = Label::createWithTTF(str, FONT_NAME, visibleSize.height/40);
    this->highScoreLabel->setAlignment(TextHAlignment::CENTER);
    this->highScoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + 
                                    visibleSize.height - this->highScoreLabel->getContentSize().height));
    this->addChild(this->highScoreLabel, 5);
}

void GameScene::setScore(int score) {
    // setting current score
    if (this->scoreLabel) {
        this->score = score;
        std::stringstream ss;
        ss << this->score;
        std::string str = ss.str();
        this->scoreLabel->setString(str);
    }
    
    if (this->highScoreLabel && (this->score > this->highScore)) {
        // update the highscore
        this->highScore = this->score;
        std::stringstream ss;
        ss << "Best: " << this->highScore;
        std::string str = ss.str();
        this->highScoreLabel->setString(str);
        UserDefault::getInstance()->setIntegerForKey("HIGH_SCORE", score);
    }
}

void GameScene::setParallaxScrollingBG() {
    Sprite* bg1 = Sprite::create(BACKGROUND_IMG);
    Sprite* bg2 = Sprite::create(BACKGROUND_IMG);

    // creating parallax node for scrolling background
    this->parallaxBackground = CCParallaxScrollNode::create();
    this->parallaxBackground->addInfiniteScrollYWithZ(-1, Vec2(1, 1), Vec2(0, 0), bg1, bg2, nullptr);
    this->addChild(parallaxBackground, Z_ORDER::PARALLAX_LAYER);
}

void GameScene::displayAsteroid() {
    AsteroidController::getInstance()->throwAsteroid(this);
}

void GameScene::addSpaceShip() {
    SpaceShipController::getInstance()->createSpaceShip(this);
}

void GameScene::startFiring() {
    BulletController::getInstance()->shootBullets(this);
}

bool GameScene::onContact(PhysicsContact &contact) {
    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();

    auto aSprite = static_cast<Sprite*>(a->getNode());
    auto bSprite = static_cast<Sprite*>(b->getNode());

    // ship colliding with asteroid or reverse
    // ship is damaged
    if (aSprite && bSprite &&
        a->getCollisionBitmask() == COLLISION_BITMASK_SPACESHIP &&
        b->getCollisionBitmask() == COLLISION_BITMASK_ASTEROID) {
        SpaceShipController::getInstance()->onCollisionShip();
        SoundController::getInstance()->play(SOUND_EXP_SHIP);
    }
    else if (aSprite && bSprite &&
        b->getCollisionBitmask() == COLLISION_BITMASK_SPACESHIP &&
        a->getCollisionBitmask() == COLLISION_BITMASK_ASTEROID) {
        SpaceShipController::getInstance()->onCollisionShip();
        SoundController::getInstance()->play(SOUND_EXP_SHIP);
    }

    // collision of asteroid and bullet, both are damaged
    if (aSprite && bSprite && 
        a->getCollisionBitmask() == COLLISION_BITMASK_ASTEROID && 
        b->getCollisionBitmask() == COLLISION_BITMASK_BULLET) {
        AsteroidController::getInstance()->onCollisionAsteroid(a->getTag());
        BulletController::getInstance()->onCollisionBullet(b->getTag());
        SoundController::getInstance()->play(SOUND_EXP_ASTEROID);
        this->setScore(this->score + 50);
    }
    else if (aSprite && bSprite && 
        b->getCollisionBitmask() == COLLISION_BITMASK_ASTEROID && 
        a->getCollisionBitmask() == COLLISION_BITMASK_BULLET) {
        AsteroidController::getInstance()->onCollisionAsteroid(b->getTag());
        BulletController::getInstance()->onCollisionBullet(a->getTag());
        SoundController::getInstance()->play(SOUND_EXP_ASTEROID);
        this->setScore(this->score + 50);
    }
    return true;
}

void GameScene::update(float delta) {
    this->tickAsteroid += delta;
    this->tickBullet += delta;

    // update the parallax background
    parallaxBackground->updateWithVelocity(Vec2(0, -0.01f * visibleSize.height), delta);

    // making a meteor fly after some duration
    if (this->tickAsteroid > (250.0f/visibleSize.width)) {
        this->tickAsteroid = 0;
        this->displayAsteroid();
    }

    // making a meteor fly after some duration
    if (this->tickBullet > (75.0f/visibleSize.width)) {
        this->tickBullet = 0;
        this->startFiring();
    }
}
