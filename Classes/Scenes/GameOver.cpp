#include "GameOver.h"

enum options { RETRY = 0, MAIN_MENU, EXIT };

cocos2d::Scene* GameOver::createScene(std::string str)
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameOver::create();
	layer->setText(str);
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if (!initMenu(cocos2d::Vec2(640, 400)))
	{
		return false;
	}

	gameOverText = MyMenuItem::createMenuItem("", "fonts/arial.ttf", 100.0);
	gameOverText->setPos(cocos2d::Vec2(640, 600));
	gameOverText->select();
	addChild(gameOverText);

	std::vector<std::string> optionsStrings = { "Retry", "Main Menu", "Exit" };
	addMenuOptions(optionsStrings, "fonts/arial.ttf", 60.0, 100.0);
	menuOptions.at(selectedItem)->select();

	scheduleUpdate();
	return true;
}

void GameOver::select()
{
	switch (selectedItem)
	{
	case RETRY:
		cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case MAIN_MENU:
		cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
		break;
	case EXIT:
		cocos2d::Director::getInstance()->end();
		break;
	}
}

void GameOver::setText(std::string str)
{
	gameOverText->setText(str);
}
