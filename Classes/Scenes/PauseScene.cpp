#include "PauseScene.h"

enum options { RESUME = 0, RESTART, BACK_TO_TITLE };

cocos2d::Scene* PauseScene::createScene(cocos2d::RenderTexture* background)
{
	auto scene = cocos2d::Scene::create();
	auto layer = PauseScene::create();
	
	scene->addChild(background);
	scene->addChild(layer);
	
	return scene;
}

bool PauseScene::init()
{
	if (!initMenu(cocos2d::Vec2(440, 480)))
	{
		return false;
	}

	std::vector<std::string> optionsStrings = { "Resume", "Restart", "Go Back to Title" };
	addMenuOptions(optionsStrings, 50.0, 100.0);
	menuOptions.at(selectedItem)->select();

	this->scheduleUpdate();
	return true;
}

void PauseScene::select()
{
	cocos2d::Director::getInstance()->popScene();

	switch (selectedItem)
	{
	case RESTART:
		cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case BACK_TO_TITLE:
		cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
		break;
	}
}
