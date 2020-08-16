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
	nextMenuScroll = 0.0;

	keyboardManager = new KeyboardManager();

	auto eventListener = cocos2d::EventListenerKeyboard::create();
	eventListener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		keyboardManager->pressKey(keyCode);
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
		keyboardManager->releaseKey(keyCode);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
	return true;
}

void MyMenu::addMenuOption(std::string text, std::string font, float fontSize, float margin)
{
	auto yOffest = origin.y - menuOptions.size() * margin;
	menuOptions.pushBack(MyMenuItem::createMenuItem(text, font, fontSize));
	menuOptions.back()->setPosition(origin.x, yOffest);
	this->addChild(menuOptions.back());
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
	if (current == -1)
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

	if (scrollMenu(delta, DEFAULT_MENU_SCROLL_SPEED, cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW))
	{
		changeSelection(meunuWarpAround(selectedItem, -1, menuOptions.size() - 1));
		return;
	}

	if (scrollMenu(delta, DEFAULT_MENU_SCROLL_SPEED, cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW))
	{
		changeSelection(meunuWarpAround(selectedItem, 1, menuOptions.size() - 1));
	}
}

bool MyMenu::scrollMenu(float delta, float scrollSpeed, cocos2d::EventKeyboard::KeyCode directionKey)
{
	if (keyboardManager->getPressTime(directionKey) < MENU_SCROLL_CUTOFF)
	{
		return false;
	}

	for (cocos2d::EventKeyboard::KeyCode key : arrowKeys)
	{
		if (key != directionKey && keyboardManager->isPressed(key))
		{
			nextMenuScroll = MENU_SCROLL_CUTOFF;
			return false;
		}
	}

	nextMenuScroll -= delta;
	if (nextMenuScroll < 0.0)
	{
		nextMenuScroll += scrollSpeed;
		return true;
	}
	return false;
}
