#include "SettingsMenu.h"

enum options { RESOLUTION = 0, MUSIC_VOLUME, EFFECT_VOLUME, SHOW_HITBOXES, CONTROLS, BACK };

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

	std::vector<std::string> optionsStrings = { "Resolution", "Music Volume", "Effect Volume", "Show Hitboxes", "Controls", "Back" };
	addMenuOptions(optionsStrings, FONT_SIZE, MARGIN_SIZE);
	menuOptions.at(selectedItem)->select();

	optionValues[RESOLUTION] = Settings::getResolution();
	optionValues[MUSIC_VOLUME] = Settings::getMusicVolume();
	optionValues[EFFECT_VOLUME] = Settings::getEffectVolume();
	optionValues[SHOW_HITBOXES] = (int)(Settings::getHitboxOption() == cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	
	for (int i = 0; i < 4; i++)
	{
		float yOffset = origin.y - menuLeftColumn.size() * MARGIN_SIZE;
		menuLeftColumn.pushBack(MyMenuItem::createMenuItem("", FONT_NAME, FONT_SIZE));
		menuLeftColumn.back()->setPos(cocos2d::Vec2(700, yOffset));
		addChild(menuLeftColumn.back());
	}
	updateOptionValueStrings();

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = CC_CALLBACK_2(SettingsMenu::pressKey, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void SettingsMenu::pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
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
}

void SettingsMenu::updateOptionValueStrings()
{
	menuLeftColumn.at(RESOLUTION)->setText(resolutionOptionStrings.at(optionValues[RESOLUTION]));
	menuLeftColumn.at(MUSIC_VOLUME)->setText(std::to_string(optionValues[MUSIC_VOLUME]));
	menuLeftColumn.at(EFFECT_VOLUME)->setText(std::to_string(optionValues[EFFECT_VOLUME]));
	menuLeftColumn.at(SHOW_HITBOXES)->setText(hitboxOptionStrings.at(optionValues[SHOW_HITBOXES]));
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
	case SHOW_HITBOXES:
		Settings::setHitboxOption(optionValues[SHOW_HITBOXES] != 0);
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
	scrollMenuHorizontally(delta);

	if (prevSelected < menuLeftColumn.size())
	{
		menuLeftColumn.at(prevSelected)->deselect();
	}

	if (selectedItem < menuLeftColumn.size())
	{
		menuLeftColumn.at(selectedItem)->select();
	}
}

void SettingsMenu::scrollMenuHorizontally(float delta)
{
	float scrollSpeed = selectedItem == RESOLUTION || selectedItem == SHOW_HITBOXES ? 
		SLOW_MENU_SCROLL_SPEED : FAST_MENU_SCROLL_SPEED;

	int scroll = scrollMenu(delta, scrollSpeed, true);
	if (scroll != 0)
	{
		optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], scroll, MAX_OPTION_VALUES[selectedItem]);
		updateSettings();
	}
}
