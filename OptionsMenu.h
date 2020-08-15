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
	std::vector<std::string> resolutionOptionStrings;
	MyMenuItem* resolutionOption;
};