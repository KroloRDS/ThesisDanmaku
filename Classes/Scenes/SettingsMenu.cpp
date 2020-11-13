#include "SettingsMenu.h"

enum options { RESOLUTION = 0, VOLUME, FULLSCREEN, SHOW_HITBOXES, BACK };

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

	std::vector<std::string> optionsStrings = { "Resolution", "Volume", "Fullscreen", "Show Hitboxes", "Back" };
	addMenuOptions(optionsStrings, FONT_SIZE, MARGIN_SIZE);
	menuOptions.at(selectedItem)->select();

	optionValues[RESOLUTION] = Settings::getResolution();
	optionValues[VOLUME] = Settings::getVolume();
	optionValues[FULLSCREEN] = 1 * Settings::isFullscren();
	optionValues[SHOW_HITBOXES] = Settings::getHitboxOption();
	
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
	menuLeftColumn.at(VOLUME)->setText(std::to_string(optionValues[VOLUME]));
	menuLeftColumn.at(FULLSCREEN)->setText(fullscreenOptionStrings.at(optionValues[FULLSCREEN]));
	menuLeftColumn.at(SHOW_HITBOXES)->setText(hitboxOptionStrings.at(optionValues[SHOW_HITBOXES]));
}

void SettingsMenu::updateSettings()
{
	switch (selectedItem)
	{
	case RESOLUTION:
		setResolution();
		break;
	case VOLUME:
		Settings::setVolume(optionValues[VOLUME]);
		break;
	case FULLSCREEN:
		Settings::setFullscreen(optionValues[FULLSCREEN] == 1);
		optionValues[RESOLUTION] = 1;
		setResolution();
		break;
	case SHOW_HITBOXES:
		Settings::setHitboxOption(optionValues[SHOW_HITBOXES]);
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
	if (selectedItem == BACK)
	{
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
	float scrollSpeed = 
		selectedItem == VOLUME ? FAST_MENU_SCROLL_SPEED : SLOW_MENU_SCROLL_SPEED;

	int scroll = scrollMenu(delta, scrollSpeed, true);
	if (scroll != 0)
	{
		optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], scroll, MAX_OPTION_VALUES[selectedItem]);
		updateSettings();
	}
}
