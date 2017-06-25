#pragma once

#include "cocos2d.h"
USING_NS_CC;

class IController : public Node {
public:
    virtual void initListeners(Ref* target) = 0;
    virtual void removeListeners() = 0;
    virtual void registerListener(Ref* target, const char* event) = 0;
    virtual void deregisterListener(const char* event) = 0;
    virtual ~IController() {
        onExit();
    };
};
