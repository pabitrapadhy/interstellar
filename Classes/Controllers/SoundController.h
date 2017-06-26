#pragma once

#include "cocos2d.h"
#include "IController.h"

USING_NS_CC;

class SoundController : public IController {
public:
	static SoundController* getInstance();

	// methods
	void initListeners(Ref* target);
    void removeListeners();
    void registerListener(Ref* target, const char* event);
    void deregisterListener(const char* event);
    void play(const std::string& fileName, bool loop = false);
    void stopAll();
	void debug();
};