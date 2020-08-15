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

	void updateMenu(float delta);
	bool initMenu(cocos2d::Vec2);
	void addMenuOption(std::string, std::string, float, float);
	void addMenuOptions(std::vector<std::string> options, std::string font, float fontSize, float margin);
	void changeScene(cocos2d::Scene*);
};