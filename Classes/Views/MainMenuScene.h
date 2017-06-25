#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CCParallaxScrollNode.h"

using namespace ui;
USING_NS_CC;

class MainMenuScene : public Layer {
private:
    float tick;
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
    void addSpaceShip();
    
    CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
