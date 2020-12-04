#include "PauseScene.h"

enum options { RESUME = 0, RESTART, BACK_TO_TITLE };

cocos2d::Scene* PauseScene::createScene(cocos2d::RenderTexture* background)
{
	auto scene = cocos2d::Scene::create();
	auto layer = PauseScene::create();
	
	scene->addChild(background);
	scene->addChild(dimEffect());
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

	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(PauseScene::restart, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate();
	return true;
}

void PauseScene::restart(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_R)
	{
		cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
	}
}

cocos2d::DrawNode* PauseScene::dimEffect()
{
	auto origin = Settings::getTranslatedCoords(GameScene::GAME_INNER_BOUNDS[0]);
	auto dest = Settings::getTranslatedCoords(GameScene::GAME_INNER_BOUNDS[2]);
	auto color = cocos2d::Color4F(0.0f, 0.0f, 0.0f, 0.6f);

	auto drawNode = cocos2d::DrawNode::create();
	drawNode->drawSolidRect(origin, dest, color);

	return drawNode;
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
