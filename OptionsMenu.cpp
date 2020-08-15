#include "OptionsMenu.h"
#include "MainMenu.h"

enum options { RESOLUTION = 0, MUSIC_VOLUME, EFFECT_VOLUME, CONTROLS, BACK };
enum resolutions { r640x480 = 0, r960x720, r1280x960 };

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
	std::string fontName = "fonts/arial.ttf";
	std::vector<std::string> optionsStrings = { "Resolution", "Music Volume", "Effect Volume", "Controls", "Back" };
	addMenuOptions(optionsStrings, fontName, fontSize, 80.0);
	menuOptions.at(selectedItem)->select();

	selectedResolution = 2;
	resolutionOptionStrings = { "640x480", "960x720", "1280x960" };
	resolutionOption = MyMenuItem::createMenuItem(resolutionOptionStrings.at(selectedResolution), fontName, fontSize);
	resolutionOption->setPosition(700, 680);
	this->addChild(resolutionOption);

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
	resolutionOption->update(delta);

	switch (selectedItem)
	{
	case RESOLUTION:
		resolutionOption->select();
		break;
	case MUSIC_VOLUME:
		break;
	case EFFECT_VOLUME:
		break;
	case CONTROLS:
		break;
	case BACK:
		break;
	}

	switch (prevSelected)
	{
	case RESOLUTION:
		resolutionOption->deselect();
		break;
	case MUSIC_VOLUME:
		break;
	case EFFECT_VOLUME:
		break;
	case CONTROLS:
		break;
	case BACK:
		break;
	}
}