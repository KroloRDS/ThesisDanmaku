#pragma once

#include "MainMenu.h"
#include "Menu/MyMenu.h"
#include "HelperClasses/Settings.h"

class SettingsMenu : public MyMenu
{
public:
	void update(float);
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(SettingsMenu);
private:
	int optionValues[4] = { 2, 100, 100, 1 };
	cocos2d::Vector<MyMenuItem*> menuLeftColumn = {};
	
	const float FONT_SIZE = 45.0f;
	const float MARGIN_SIZE = 80.0f;
	const int MAX_OPTION_VALUES[4] = { 2, 100, 100, 1 };
	const std::vector<std::string> resolutionOptionStrings = { "640x480", "960x720", "1280x960" };
	const std::vector<std::string> hitboxOptionStrings = { "None", "All" };

	void pressKey(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
	void updateOptionValueStrings();
	void updateSettings();
	void setResolution();
	void scrollMenuHorizontally(float delta);
};
