#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "CCParallaxScrollNode.h"

USING_NS_CC;

class MainMenuScene : public Scene {
public:
    static Scene* createScene();
    virtual bool init() override;
    virtual void update(float delta) override;

    // variables
    Vec2 origin;
    Size visibleSize;
    CCParallaxScrollNode* parallaxBackground;

    // functions
    void setParallaxScrollingBG();
    void menuCloseCallback(Ref* pSender);
    
    CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
