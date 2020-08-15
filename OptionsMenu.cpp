#include "OptionsMenu.h"
#include "MainMenu.h"

enum options { RESOLUTION = 0, MUSIC_VOLUME, EFFECT_VOLUME, CONTROLS, BACK };
enum resolutions { R640x480 = 0, R960x720, R1280x960 };

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

	float fontSize = 45.0;
	float marginSize = 80.0;

	//left menu column
	std::string fontName = "fonts/arial.ttf";
	std::vector<std::string> optionsStrings = { "Resolution", "Music Volume", "Effect Volume", "Controls", "Back" };
	addMenuOptions(optionsStrings, fontName, fontSize, marginSize);
	menuOptions.at(selectedItem)->select();

	//right menu column
	musicVolume = 100;
	soundVolume = 100;
	selectedResolution = R1280x960;
	resolutionOptionStrings = { "640x480", "960x720", "1280x960" };
	std::vector<std::string> initialOptionValues = { resolutionOptionStrings.at(selectedResolution), std::to_string(musicVolume), std::to_string(soundVolume) };
	
	for (std::string initVal : initialOptionValues)
	{
		auto yOffset = origin.y - menuLeftColumn.size() * marginSize;
		menuLeftColumn.pushBack(MyMenuItem::createMenuItem(initVal, fontName, fontSize));
		menuLeftColumn.back()->setPosition(700, yOffset);
		this->addChild(menuLeftColumn.back());
	}

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

void OptionsMenu::update(float delta)
{
	updateMenu(delta);
	for (MyMenuItem* option : menuLeftColumn)
	{
		option->update(delta);
	}

	if (prevSelected < menuLeftColumn.size())
	{
		menuLeftColumn.at(prevSelected)->deselect();
	}

	if (selectedItem < menuLeftColumn.size())
	{
		menuLeftColumn.at(selectedItem)->select();
	}
}