#include "OptionsMenu.h"
#include "MainMenu.h"

enum options { RESOLUTION = 0, MUSIC_VOLUME, EFFECT_VOLUME, CONTROLS, BACK };

cocos2d::Scene* OptionsMenu::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = OptionsMenu::create();
	scene->addChild(layer);
	return scene;
}

bool OptionsMenu::init()
{
	if (!initMenu(cocos2d::Vec2(340, 680)))
	{
		return false;
	}

	std::vector<std::string> optionsStrings = { "Resolution", "Music Volume", "Effect Volume", "Controls", "Back" };
	addMenuOptions(optionsStrings, "fonts/arial.ttf", 45.0, 80.0);
	menuOptions.at(selectedItem)->select();

	this->scheduleUpdate();
	return true;
}

void OptionsMenu::select()
{
	switch (selectedItem)
	{
	case RESOLUTION:
		break;
	case MUSIC_VOLUME:
		break;
	case EFFECT_VOLUME:
		break;
	case CONTROLS:
		break;
	case BACK:
		cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
	}
}