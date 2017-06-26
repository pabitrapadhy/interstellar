#include "SceneController.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

SceneController* SceneController::getInstance() {
	// singleton
	static SceneController instance;
	return &instance;
}

SceneController::SceneController() {}

// basic controller properties
void SceneController::initListeners(Ref* target) {};
void SceneController::removeListeners() {};
void SceneController::registerListener(Ref* target, const char* event) {};
void SceneController::deregisterListener(const char* event) {};

void SceneController::changeScene(SCENE type) {
	if (type == SCENE::MAIN_SCENE) {
		Scene* scene = MainMenuScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
	} else if (type == SCENE::GAME_SCENE) {
		Scene* scene = GameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B::BLACK));
	}
}

void SceneController::quitGame() {
	Director::getInstance()->end();
}

void SceneController::debug() {
	CCLOG("pabitra: object pool debug");
}
