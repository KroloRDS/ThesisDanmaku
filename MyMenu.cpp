#include "MyMenu.h"

bool MyMenu::initMenu(cocos2d::Vec2 pos)
{
	if (!Layer::init())
	{
		return false;
	}

	origin = pos;
	selectedItem = 0;
	prevSelected = 0;

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			changeSelection(-1);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			changeSelection(1);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		case cocos2d::EventKeyboard::KeyCode::KEY_Z:
		case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
			select();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
		case cocos2d::EventKeyboard::KeyCode::KEY_X:
			selectBack();
			break;
		}
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void MyMenu::addMenuOption(std::string text, std::string font, float fontSize, float margin)
{
	auto pos = origin;
	pos.y -= (menuOptions.size()) * margin;
	menuOptions.push_back(MyMenuItem::createMenuItem(text, font, fontSize));
	menuOptions.back()->setPosition(pos);
	this->addChild(menuOptions.back());
}

void MyMenu::addMenuOptions(std::vector<std::string> options, std::string font, float fontSize, float margin)
{
	for (std::string str : options)
	{
		addMenuOption(str, "fonts/arial.ttf", fontSize, margin);
	}
}

void MyMenu::changeSelection(int increase)
{
	prevSelected = selectedItem;
	selectedItem += increase;
	
	if (selectedItem < 0)
	{
		selectedItem = menuOptions.size() - 1;
	}

	if (selectedItem >= menuOptions.size())
	{
		selectedItem = 0;
	}

	menuOptions.at(prevSelected)->deselect();
	menuOptions.at(selectedItem)->select();
}

void MyMenu::selectBack()
{
	if (selectedItem == menuOptions.size() - 1)
	{
		select();
	}
	else
	{
		menuOptions.at(selectedItem)->deselect();
		selectedItem = menuOptions.size() - 1;
		menuOptions.at(selectedItem)->select();
	}
}

void MyMenu::update(float delta)
{
	updateMenu(delta);
}

void MyMenu::updateMenu(float delta)
{
	for (MyMenuItem* option : menuOptions)
	{
		option->update(delta);
	}
}
