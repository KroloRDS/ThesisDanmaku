#include "MainMenu.h"

enum options { START = 0, SPELL_PRACTICE, SETTINGS, EXIT };

cocos2d::Scene* MainMenu::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!initMenu(cocos2d::Vec2(640, 720)))
	{
		return false;
	}

	std::vector<std::string> optionsStrings = { "Start", "Spell Practice", "Settings", "Exit" };
	addMenuOptions(optionsStrings, "fonts/arial.ttf", 100.0, 160.0);
	menuOptions.at(selectedItem)->select();

	this->scheduleUpdate();
	return true;
}

void MainMenu::select()
{
	switch (selectedItem)
	{
	case START:
		break;
	case SPELL_PRACTICE:
		cocos2d::Director::getInstance()->replaceScene(SpellPracticeMenu::createScene());
		break;
	case SETTINGS:
		cocos2d::Director::getInstance()->replaceScene(SettingsMenu::createScene());
		break;
	case EXIT:
		cocos2d::Director::getInstance()->end();
		break;
	}
}
