#pragma once

#include "MyMenu.h"
#include "MainMenu.h"
#include "Settings.h"

class SettingsMenu : public MyMenu
{
public:
	void update(float);
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(SettingsMenu);
private:
	cocos2d::Vector<MyMenuItem*> menuLeftColumn = {};
	int optionValues[3] = { 2, 100, 100 };
	const int MAX_OPTION_VALUES[3] = { 2, 100, 100 };
	const std::vector<std::string> resolutionOptionStrings = { "640x480", "960x720", "1280x960" };

	void updateOptionValueStrings();
	void updateSettings();
	void setResolution();
	void scrollMenuHorizontally(float delta);
};
