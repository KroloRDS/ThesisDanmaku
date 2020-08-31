#include "MyMenu.h"

bool MyMenu::initMenu(cocos2d::Vec2 pos)
{
	if (!Layer::init())
	{
		return false;
	}

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		KeyboardManager::pressKey(keyCode);
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			changeSelection(meunuWarpAround(selectedItem, -1, menuOptions.size() - 1));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			changeSelection(meunuWarpAround(selectedItem, 1, menuOptions.size() - 1));
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
	eventListener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		KeyboardManager::releaseKey(keyCode);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	origin = pos;

	return true;
}

void MyMenu::addMenuOption(std::string text, std::string font, float fontSize, float margin)
{
	menuOptions.pushBack(MyMenuItem::createMenuItem(text, font, fontSize));
	addChild(menuOptions.back());
	float yOffset = origin.y - (menuOptions.size() - 1) * margin;
	menuOptions.back()->setPos(cocos2d::Vec2(origin.x, yOffset));
}

void MyMenu::addMenuOptions(std::vector<std::string> options, std::string font, float fontSize, float margin)
{
	for (std::string str : options)
	{
		addMenuOption(str, "fonts/arial.ttf", fontSize, margin);
	}
}

int MyMenu::meunuWarpAround(int current, int increase, int max)
{
	current += increase;
	if (current > max)
	{
		return 0;
	}
	else if (current == -1)
	{
		return max;
	}
	return current;
}

void MyMenu::changeSelection(int newSelected)
{
	prevSelected = selectedItem;
	selectedItem = newSelected;
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

	int scroll = scrollMenu(delta, DEFAULT_MENU_SCROLL_SPEED, false);
	if (scroll != 0)
	{
		int newSelected = meunuWarpAround(selectedItem, scroll, menuOptions.size() - 1);
		changeSelection(newSelected);
	}
}

int MyMenu::scrollMenu(float delta, float scrollSpeed, bool horizontal)
{
	std::vector<cocos2d::EventKeyboard::KeyCode> pressedList = KeyboardManager::getPressedArrows();

	if (pressedList.empty())
	{
		return 0;
	}
	if (pressedList.size() > 1)
	{
		nextMenuScroll = scrollSpeed;
		return 0;
	}

	cocos2d::EventKeyboard::KeyCode pressed = pressedList.at(0);	
	if (horizontal != (pressed == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW || pressed == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		return 0;
	}
	if (KeyboardManager::getPressTime(pressed) < MENU_SCROLL_CUTOFF)
	{
		return 0;
	}

	int change = 1;
	if (pressed == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW || pressed == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		change = -1;
	}

	nextMenuScroll -= delta;
	if (nextMenuScroll < 0.0f)
	{
		nextMenuScroll += scrollSpeed;
		return change;
	}
	return 0;
}
