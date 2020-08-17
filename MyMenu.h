#pragma once

#include "cocos2d.h"
#include "MyMenuItem.h"
#include "KeyboardManager.h"
#include "Settings.h"

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

	float nextMenuScroll;
	
	const float SLOW_MENU_SCROLL_SPEED = 0.35;
	const float DEFAULT_MENU_SCROLL_SPEED = 0.15;
	const float FAST_MENU_SCROLL_SPEED = 0.05;
	const float MENU_SCROLL_CUTOFF = 0.5;

	void updateMenu(float);
	int scrollMenu(float, float, bool);
	int meunuWarpAround(int, int, int);
	bool initMenu(cocos2d::Vec2);
	void addMenuOption(std::string, std::string, float, float);
	void addMenuOptions(std::vector<std::string> options, std::string font, float fontSize, float margin);
};