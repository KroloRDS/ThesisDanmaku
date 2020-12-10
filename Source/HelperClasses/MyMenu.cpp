#include "MyMenu.h"

bool MyMenu::initMenu(cocos2d::Vec2 pos)
{
	if (!Layer::init())
	{
		return false;
	}

	auto keyboardListener = cocos2d::EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MyMenu::pressKey, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MyMenu::releaseKey, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	origin = pos;

	return true;
}

void MyMenu::pressKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::pressKey(keyCode);
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SELECT_SFX);
		changeSelection(meunuWarpAround(selectedItem, -1, menuOptions.size() - 1));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SELECT_SFX);
		changeSelection(meunuWarpAround(selectedItem, 1, menuOptions.size() - 1));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(CONFIRM_SFX);
		select();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
	case cocos2d::EventKeyboard::KeyCode::KEY_X:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(BACK_SFX);
		selectBack();
		break;
	}
}

void MyMenu::releaseKey(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*)
{
	KeyboardManager::releaseKey(keyCode);
}

void MyMenu::addMenuOption(std::string text, float fontSize, float margin)
{
	menuOptions.pushBack(MyMenuItem::createMenuItem(text, FONT_NAME, fontSize));
	addChild(menuOptions.back());
	float yOffset = origin.y - (menuOptions.size() - 1) * margin;
	menuOptions.back()->setPos(cocos2d::Vec2(origin.x, yOffset));
}

void MyMenu::addMenuOptions(std::vector<std::string> options, float fontSize, float margin)
{
	for (std::string str : options)
	{
		addMenuOption(str, fontSize, margin);
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
	for (Node* child : getChildren())
	{
		child->update(delta);
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SELECT_SFX);
		nextMenuScroll += scrollSpeed;
		return change;
	}
	return 0;
}
