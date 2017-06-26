#include "SoundController.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace cocos2d::experimental;

SoundController* SoundController::getInstance() {
	// singleton
	static SoundController instance;
	return &instance;
}

// basic controller properties
void SoundController::initListeners(Ref* target) {};
void SoundController::removeListeners() {};
void SoundController::registerListener(Ref* target, const char* event) {};
void SoundController::deregisterListener(const char* event) {};

void SoundController::play(const std::string& fileName, bool loop) {
	AudioEngine::play2d(fileName, loop);
}

void SoundController::stopAll() {
	AudioEngine::stopAll();
}

void SoundController::debug() {
	CCLOG("pabitra: object pool debug");
}
