#include "MainMenu.h"

enum options { START = 0, SPELL_PRACTICE, HIGHSCORES, SETTINGS, EXIT };

cocos2d::Scene* MainMenu::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!initMenu(cocos2d::Vec2(640, 820)))
	{
		return false;
	}

	std::vector<std::string> optionsStrings = { "Start", "Spell Practice", "Highscores", "Settings", "Exit" };
	addMenuOptions(optionsStrings, 100.0, 160.0);
	menuOptions.at(selectedItem)->select();

	this->scheduleUpdate();
	return true;
}

void MainMenu::select()
{
	switch (selectedItem)
	{
	case START:
		Settings::setPracticePattern(-1);
		cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
		break;
	case SPELL_PRACTICE:
		cocos2d::Director::getInstance()->replaceScene(SpellPracticeMenu::createScene());
		break;
	case SETTINGS:
		cocos2d::Director::getInstance()->replaceScene(SettingsMenu::createScene());
		break;
	case HIGHSCORES:
		cocos2d::Director::getInstance()->replaceScene(HighscoreScene::createScene());
		break;
	case EXIT:
		cocos2d::Director::getInstance()->end();
		break;
	}
}
