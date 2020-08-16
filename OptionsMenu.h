#pragma once

#include "MyMenu.h"

class OptionsMenu : public MyMenu
{
public:
	void update(float) override;
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	void select();
	CREATE_FUNC(OptionsMenu);
private:
	int selectedResolution;
	int musicVolume;
	int effectVolume;
	
	std::vector<std::string> resolutionOptionStrings;
	cocos2d::Vector<MyMenuItem*> menuLeftColumn;
	std::string optionValueStrings[3];
	int optionValues[3];
	const int MAX_OPTION_VALUES[3] = { 2, 100, 100 };

	void updateOptionValueStrings();
	void scrollMenuHorizontally(float delta);
};