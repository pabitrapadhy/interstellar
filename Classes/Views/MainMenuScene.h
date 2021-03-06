#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CCParallaxScrollNode.h"

using namespace ui;
USING_NS_CC;

class MainMenuScene : public Layer {
private:
    float tickAsteroid;
    CCParallaxScrollNode* parallaxBackground;
    Vec2 origin;
    Size visibleSize;

public:
    MainMenuScene();
    static Scene* createScene();
    virtual bool init() override;
    virtual void onExit() override;
    virtual void update(float delta) override;

    // functions
    void setParallaxScrollingBG();
    void onPlayClicked(Ref* sender, Widget::TouchEventType type);
    void displayAsteroid();
    
    CREATE_FUNC(MainMenuScene);
};