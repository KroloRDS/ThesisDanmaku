#pragma once

#include "cocos2d.h"
#include "MyMenuItem.h"

class MyMenu : public cocos2d::Layer
{
public:
	void update(float) override;
	void changeSelection(int);
	void selectBack();
	virtual void select() = 0;
protected:
	std::vector<MyMenuItem*> menuOptions;
	int selectedItem;
	int prevSelected;
	cocos2d::Vec2 origin;

	bool initMenu(cocos2d::Vec2);
	void addMenuOption(std::string, std::string, float, float);
	void addMenuOptions(std::vector<std::string> options, std::string font, float fontSize, float margin);
};