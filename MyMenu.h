#pragma once

#include "cocos2d.h"
#include "MyMenuItem.h"
#include "KeyboardManager.h"

class MyMenu : public cocos2d::Layer
{
public:
	void update(float) override;
	void changeSelection(int);
	void selectBack();
	virtual void select() = 0;
protected:
	cocos2d::Vector<MyMenuItem*> menuOptions;
	int selectedItem;
	int prevSelected;
	cocos2d::Vec2 origin;

	KeyboardManager* keyboardManager = nullptr;
	float nextMenuScroll;
	const float menuScrollInterval = 0.15;
	const float menuScrollCutoff = 0.5;
	const std::vector<cocos2d::EventKeyboard::KeyCode> arrowKeys =
	{
		cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW,
		cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW
	};

	void updateMenu(float);
	bool scrollMenu(float, cocos2d::EventKeyboard::KeyCode);
	int meunuWarpAround(int, int, int);
	bool initMenu(cocos2d::Vec2);
	void addMenuOption(std::string, std::string, float, float);
	void addMenuOptions(std::vector<std::string> options, std::string font, float fontSize, float margin);
};