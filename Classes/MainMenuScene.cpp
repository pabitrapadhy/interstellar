#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "Constants.h"

USING_NS_CC;

Scene* MainMenuScene::createScene() {
    auto scene = Scene::createWithPhysics();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init() {
    if (!Scene::init()) return false;
    
    origin = Director::getInstance()->getVisibleOrigin();
    visibleSize = Director::getInstance()->getVisibleSize();

    this->setParallaxScrollingBG();
    this->scheduleUpdate();
    return true;
}

void MainMenuScene::setParallaxScrollingBG() {
    Sprite* bg1 = Sprite::create("background.png");
    Sprite* bg2 = Sprite::create("background.png");

    // creating parallax node for scrolling background
    this->parallaxBackground = CCParallaxScrollNode::create();
    this->parallaxBackground->addInfiniteScrollYWithZ(-1, Vec2(1, 1), Vec2(0, 0), bg1, bg2, nullptr);
    this->addChild(parallaxBackground);
}

void MainMenuScene::update(float delta) {
    parallaxBackground->updateWithVelocity(Vec2(0, -0.01f * visibleSize.height), delta);
}
