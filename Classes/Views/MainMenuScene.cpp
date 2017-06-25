#include "MainMenuScene.h"
#include "GameObjectPool.h"
#include "AsteroidController.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"

using namespace ui;
USING_NS_CC;

Scene* MainMenuScene::createScene() {
    auto scene = Scene::createWithPhysics();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

MainMenuScene::MainMenuScene() {
    this->tick = 0.0f;
    this->parallaxBackground = nullptr;
}

bool MainMenuScene::init() {
    if (!Layer::init()) return false;
    
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();

    // game banner
    auto gamebanner = Sprite::create(GAME_BANNER_IMG);
    gamebanner->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.66);
    this->addChild(gamebanner, Z_ORDER::BG_LAYER);

    // play btn
    auto playBtn = Button::create("button_normal.png", "button_pressed.png", "button_normal.png");
    playBtn->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3));
    playBtn->setTitleText("START");
    playBtn->setTitleColor(Color3B::BLACK);
    playBtn->setTitleFontSize(25);
    playBtn->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onPlayClicked, this));
    this->addChild(playBtn, Z_ORDER::BUTTONS);

    this->setParallaxScrollingBG();
    this->scheduleUpdate();
    return true;
}

void MainMenuScene::onExit() {
    // on exiting the scene, stop the asteroid shower and remove the layer from the scene
    AsteroidController::getInstance()->stopAsteroidMovement();
    this->removeFromParentAndCleanup(true);
}

void MainMenuScene::setParallaxScrollingBG() {
    Sprite* bg1 = Sprite::create(BACKGROUND_IMG);
    Sprite* bg2 = Sprite::create(BACKGROUND_IMG);

    // creating parallax node for scrolling background
    this->parallaxBackground = CCParallaxScrollNode::create();
    this->parallaxBackground->addInfiniteScrollYWithZ(-1, Vec2(1, 1), Vec2(0, 0), bg1, bg2, nullptr);
    this->addChild(parallaxBackground, Z_ORDER::PARALLAX_LAYER);
}

void MainMenuScene::onPlayClicked(Ref* sender, Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        // change to gamescene
    }
}

void MainMenuScene::displayAsteroid() {
    AsteroidController::getInstance()->throwAsteroid(this);
}

void MainMenuScene::update(float delta) {
    this->tick += delta;

    // update the parallax background
    parallaxBackground->updateWithVelocity(Vec2(0, -0.01f * visibleSize.height), delta);

    // making a meteor fly after some duration
    if (this->tick > (250.0f/visibleSize.width)) {
        tick = 0;
        displayAsteroid();
    }
}
