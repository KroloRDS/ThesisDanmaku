#include "SettingsMenu.h"

enum options { RESOLUTION = 0, MUSIC_VOLUME, EFFECT_VOLUME, CONTROLS, BACK };

cocos2d::Scene* SettingsMenu::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = SettingsMenu::create();
	scene->addChild(layer);
	return scene;
}

bool SettingsMenu::init()
{
	if (!initMenu(cocos2d::Vec2(340, 680)))
	{
		return false;
	}

	float fontSize = 45.0;
	float marginSize = 80.0;

	std::string fontName = "fonts/arial.ttf";
	std::vector<std::string> optionsStrings = { "Resolution", "Music Volume", "Effect Volume", "Controls", "Back" };
	addMenuOptions(optionsStrings, fontName, fontSize, marginSize);
	menuOptions.at(selectedItem)->select();

	optionValues[RESOLUTION] = Settings::getResolution();
	optionValues[MUSIC_VOLUME] = Settings::getMusicVolume();
	optionValues[EFFECT_VOLUME] = Settings::getEffectVolume();
	
	for (int i = 0; i < 3; i++)
	{
		int yOffset = origin.y - menuLeftColumn.size() * marginSize;
		menuLeftColumn.pushBack(MyMenuItem::createMenuItem("", fontName, fontSize));
		menuLeftColumn.back()->setPos(cocos2d::Vec2(700, yOffset));
		addChild(menuLeftColumn.back());
	}
	updateOptionValueStrings();

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], -1, MAX_OPTION_VALUES[selectedItem]);
			updateSettings();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], 1, MAX_OPTION_VALUES[selectedItem]);
			updateSettings();
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void SettingsMenu::updateOptionValueStrings()
{
	menuLeftColumn.at(RESOLUTION)->setText(resolutionOptionStrings.at(optionValues[RESOLUTION]));
	menuLeftColumn.at(MUSIC_VOLUME)->setText(std::to_string(optionValues[MUSIC_VOLUME]));
	menuLeftColumn.at(EFFECT_VOLUME)->setText(std::to_string(optionValues[EFFECT_VOLUME]));
}

void SettingsMenu::updateSettings()
{
	switch (selectedItem)
	{
	case RESOLUTION:
		setResolution();
		break;
	case MUSIC_VOLUME:
		Settings::setMusicVolume(optionValues[MUSIC_VOLUME]);
		break;
	case EFFECT_VOLUME:
		Settings::setEffectVolume(optionValues[EFFECT_VOLUME]);
		break;
	}

	updateOptionValueStrings();
}

void SettingsMenu::setResolution()
{
	Settings::setResolution(optionValues[RESOLUTION]);
	for (MyMenuItem* menuItem : menuOptions)
	{
		menuItem->setScale(Settings::getScale());
		menuItem->setPos(menuItem->getPos());
	}
	for (MyMenuItem* menuItem : menuLeftColumn)
	{
		menuItem->setScale(Settings::getScale());
		menuItem->setPos(menuItem->getPos());
	}
}

void SettingsMenu::select()
{
	switch (selectedItem)
	{
	case CONTROLS:
		break;
	case BACK:
		cocos2d::Director::getInstance()->replaceScene(MainMenu::createScene());
	}
}

void SettingsMenu::update(float delta)
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

	scrollMenuHorizontally(delta);
}

void SettingsMenu::scrollMenuHorizontally(float delta)
{
	float scrollSpeed = FAST_MENU_SCROLL_SPEED;
	if (selectedItem == RESOLUTION)
	{
		scrollSpeed = SLOW_MENU_SCROLL_SPEED;
	}

	int scroll = scrollMenu(delta, scrollSpeed, true);
	if (scroll != 0)
	{
		optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], scroll, MAX_OPTION_VALUES[selectedItem]);
		updateSettings();
	}
}
