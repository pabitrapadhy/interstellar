#include "MainMenuScene.h"
#include "GameObjectPool.h"
#include "AsteroidController.h"
#include "SpaceShipController.h"
#include "BulletController.h"
#include "SceneController.h"
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
    this->tickAsteroid = 0.0f;
    this->parallaxBackground = nullptr;
}

bool MainMenuScene::init() {
    if (!Layer::init()) return false;

    this->origin = Director::getInstance()->getVisibleOrigin();
    this->visibleSize = Director::getInstance()->getVisibleSize();

    // game banner
    auto gamebanner = Sprite::create(GAME_BANNER_IMG);
    gamebanner->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.66);
    this->addChild(gamebanner, Z_ORDER::BG_LAYER);

    // start button
    auto button = Button::create("button_normal.png", "button_pressed.png", "button_normal.png");
    button->setTitleText("START");
    button->setTitleFontSize(30);
    button->setTitleColor(Color3B::BLACK);
    button->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::onPlayClicked, this));
    button->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/3));
    this->addChild(button, Z_ORDER::BUTTONS);

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
        Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
        SceneController::getInstance()->changeScene(SCENE::GAME_SCENE);
    }
}

void MainMenuScene::displayAsteroid() {
    AsteroidController::getInstance()->throwAsteroid(this);
}

void MainMenuScene::update(float delta) {
    this->tickAsteroid += delta;

    // update the parallax background
    parallaxBackground->updateWithVelocity(Vec2(0, -0.01f * visibleSize.height), delta);

    // making a meteor fly after some duration
    if (this->tickAsteroid > (300.0f/visibleSize.width)) {
        this->tickAsteroid = 0;
        this->displayAsteroid();
    }
}
