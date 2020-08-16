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
	optionValues[RESOLUTION] = R1280x960;
	optionValues[MUSIC_VOLUME] = MAX_OPTION_VALUES[MUSIC_VOLUME];
	optionValues[EFFECT_VOLUME] = MAX_OPTION_VALUES[EFFECT_VOLUME];
	resolutionOptionStrings = { "640x480", "960x720", "1280x960" };
	updateOptionValueStrings();
	
	for (int i = 0; i < 3; i++)
	{
		auto yOffset = origin.y - menuLeftColumn.size() * marginSize;
		menuLeftColumn.pushBack(MyMenuItem::createMenuItem(optionValueStrings[i], fontName, fontSize));
		menuLeftColumn.back()->setPosition(700, yOffset);
		this->addChild(menuLeftColumn.back());
	}

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], -1, MAX_OPTION_VALUES[selectedItem]);
			updateOptionValueStrings();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], 1, MAX_OPTION_VALUES[selectedItem]);
			updateOptionValueStrings();
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	return true;
}

void OptionsMenu::updateOptionValueStrings()
{
	optionValueStrings[RESOLUTION] = resolutionOptionStrings.at(optionValues[RESOLUTION]);
	optionValueStrings[MUSIC_VOLUME] = std::to_string(optionValues[MUSIC_VOLUME]);
	optionValueStrings[EFFECT_VOLUME] = std::to_string(optionValues[EFFECT_VOLUME]);
	for (int i = 0; i < menuLeftColumn.size(); i++)
	{
		menuLeftColumn.at(i)->setText(optionValueStrings[i]);
	}
}

void OptionsMenu::select()
{
	switch (selectedItem)
	{
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

	scrollMenuHorizontally(delta);
}

void OptionsMenu::scrollMenuHorizontally(float delta)
{
	float scrollSpeed = FAST_MENU_SCROLL_SPEED;
	if (selectedItem == RESOLUTION)
	{
		scrollSpeed = SLOW_MENU_SCROLL_SPEED;
	}

	if (scrollMenu(delta, scrollSpeed, cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], -1, MAX_OPTION_VALUES[selectedItem]);
		updateOptionValueStrings();
		return;
	}

	if (scrollMenu(delta, scrollSpeed, cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		optionValues[selectedItem] = meunuWarpAround(optionValues[selectedItem], 1, MAX_OPTION_VALUES[selectedItem]);
		updateOptionValueStrings();
		return;
	}
}