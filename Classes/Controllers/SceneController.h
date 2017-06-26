#pragma once

#include "cocos2d.h"
#include "IController.h"
#include "Constants.h"

USING_NS_CC;

class SceneController : public IController {
protected:
	SceneController();

public:
	static SceneController* getInstance();

	// methods
	void initListeners(Ref* target);
    void removeListeners();
    void registerListener(Ref* target, const char* event);
    void deregisterListener(const char* event);
    void changeScene(SCENE type);
    void quitGame();
	void debug();
};