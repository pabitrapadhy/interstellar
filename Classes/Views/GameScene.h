#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CCParallaxScrollNode.h"

using namespace ui;
USING_NS_CC;

class GameScene : public Layer {
private:
    float tickAsteroid;
    float tickBullet;
    CCParallaxScrollNode* parallaxBackground;
    Vec2 origin;
    Size visibleSize;
    int score;
    int highScore;
    Label* scoreLabel;
    Label* highScoreLabel;

public:
    GameScene();
    static Scene* createScene();
    virtual bool init() override;
    virtual void onExit() override;
    virtual void update(float delta) override;

    // functions
    void setParallaxScrollingBG();
    void initializeHUD();
    void displayAsteroid();
    void addSpaceShip();
    void startFiring();
    bool onContact(PhysicsContact &contact);
    void setScore(int score);
    
    CREATE_FUNC(GameScene);
};